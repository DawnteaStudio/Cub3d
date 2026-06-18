# Parsing 구현 해설

## 목적

parsing 모듈은 `.cub` 파일의 raw text를 game runtime이 사용할 수 있는 `t_play`와 `t_map` 상태로 바꾼다. renderer는 texture path, floor/ceiling color, map grid, player 시작 좌표가 유효하다고 가정하므로, parsing 단계에서 입력 불확실성을 제거한다.

## Source Map

- `parse/main.c`: program entry point.
- `parse/read.c`: map file을 읽어 문자열 배열로 만든다.
- `parse/check_file.c`: 파일명, fd, 입력 개수를 검증한다.
- `parse/check_info.c`: texture/color/map 정보를 검증하는 상위 단계.
- `parse/extract_data.c`: texture path와 RGB 값을 `t_play`/`t_map`에 저장한다.
- `parse/play.c`: `t_play` 초기값과 height 설정.
- `parse/print_error.c`: error code별 종료 처리.

## 핵심 자료구조

`t_play`는 parsing과 execution이 공유하는 최상위 context다. `origin`에는 파일 원본 문자열 배열이 들어가고, `map`에는 검증과 정규화가 끝난 grid, player 시작 좌표, floor/ceiling color가 저장된다.

`t_map`은 parsing 결과 중 map과 직접 관련된 상태를 묶는다. `field`, `start_y`, `start_x`, `direction`, `ceiling`, `floor`, map size를 한 구조체에 둔다. 이 구조는 renderer가 parsing source line을 다시 해석하지 않고 정규화된 map state만 읽게 만든다.

## 구현 흐름

`parse/main.c`의 `main()`은 다음 순서로 동작한다.

1. `argc != 2`이면 `ERROR_STANDARD_INPUT`으로 종료한다.
2. `initial_play(&play)`로 `t_play`의 기본값을 설정한다.
3. `read_map(&(play.height), argv[1])`로 파일 전체를 읽어 `play.origin`에 저장한다.
4. 읽은 내용이 비어 있으면 `ERROR_INVALID_FILE`로 종료한다.
5. `set_height(&play)`로 map data 위치를 계산할 준비를 한다.
6. `is_valid_info(&play)`에서 texture/color/map validation을 수행한다.
7. 모든 검증이 끝나면 `init_game(&play)`로 실행 단계에 진입한다.

## 구현 방식

parsing은 파일 전체를 먼저 읽고 나중에 의미 단위로 분리한다. 이 구조는 texture/color 정보가 map grid보다 앞에 있어야 하는 subject 형식에 맞다. `origin`을 보존하면 에러 검사 중 같은 입력을 여러 번 참조할 수 있고, map field를 만들 때 원본 line을 다시 읽을 수 있다.

texture path는 `t_image.path`에 저장되고, color는 `int[3]` 배열로 RGB channel을 분리한다. renderer는 color parsing을 반복하지 않고 이미 정수로 변환된 값을 사용한다.

## 에러 처리

error type은 `t_error_type` enum으로 고정되어 있다. 각 validation 함수는 잘못된 조건을 발견하면 `print_error()`로 즉시 종료한다. 이 방식은 invalid state가 renderer까지 전달되지 않게 한다.

## Code-level Implementation Reading

`check_character()`는 한 line의 첫 의미 문자가 alphabet인지 digit인지로 parsing phase를 나눈다. alphabet이면 texture/color identifier로 처리하고, digit이면 map grid가 시작된 것으로 처리한다. 이 분기는 `.cub` 파일에서 header 정보와 map body를 서로 다른 규칙으로 해석해야 하기 때문에 존재한다.

```c
if (ft_isalpha(p->origin[*idx][width]))
	...
else if (ft_isdigit(p->origin[*idx][width]))
{
	check_sequence(p);
	p->check_parsing = TRUE;
	make_field(p, *idx);
	is_valid_map(idx, &(p->map));
}
```

map grid에 들어가기 직전에 `check_sequence()`를 호출하는 구조는 renderer가 필요한 texture 4개와 floor/ceiling color가 모두 준비된 뒤에만 map validation으로 넘어가게 만든다. map을 먼저 만들고 나중에 header 누락을 확인하는 방식이 아니라, 실행에 필요한 전역 정보가 완성된 순간에만 map body를 받아들인다.

`extract_path()`는 이미 같은 방향 texture가 들어 있으면 바로 `ERROR_INVALID_INFO`를 낸다. 이후 path 길이와 `.xpm` suffix를 확인한다. 이 구현은 texture path를 단순 문자열로 저장하기 전에 중복 identifier와 format 오류를 제거한다.

```c
if (p->images[image_type].path != NULL)
	print_error(ERROR_INVALID_INFO);
...
if (ft_strcmp(&tmp[path_len - 4], ".xpm") != 0)
	print_error(ERROR_INVALID_INFO);
```

`extract_color()`는 `arr[0] != -1`을 중복 color 선언의 marker로 사용한다. `initial_play()`에서 color 배열을 `-1`로 초기화하기 때문에, 첫 번째 channel 값이 채워진 뒤에는 같은 identifier를 다시 받을 수 없다. 이 방식은 별도 boolean field를 만들지 않고 color 배열 자체를 parsing state로 사용한다.
