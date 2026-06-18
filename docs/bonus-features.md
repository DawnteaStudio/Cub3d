# Bonus Features 구현 해설

## 목적

bonus 구현은 mandatory 구조를 유지하면서 sprite, door, cursor 등 상호작용 요소를 확장한다. 별도 `parse_bonus/`, `exec_bonus/`, `cub3d_bonus.h`를 사용해 mandatory와 bonus 빌드 산출물이 섞이지 않게 한다.

## Source Map

- `include/cub3d_bonus.h`: bonus state와 prototype.
- `parse_bonus/`: bonus map/config parsing.
- `exec_bonus/sprite_bonus.c`: sprite rendering.
- `exec_bonus/door_bonus.c`: door interaction.
- `exec_bonus/cursor_bonus.c`: cursor handling.
- `exec_bonus/*`: mandatory runtime의 bonus variant.

## 구현 방식

Makefile은 `WITH_BONUS=1`일 때 bonus source list를 object로 선택한다. 같은 executable 이름 `cub3D`를 만들지만, mandatory object와 bonus object를 동시에 링크하지 않는다. 이 방식은 subject의 mandatory/bonus 평가 흐름에 맞춰 build target을 분리한다.

bonus parser는 mandatory parser와 같은 책임을 가지면서 추가 map 요소와 texture를 해석한다. runtime도 mandatory의 raycasting/rendering 흐름을 유지하되 sprite/door/cursor 처리를 frame update나 rendering 단계에 추가한다.

## 왜 별도 디렉터리인지

bonus는 mandatory와 요구사항이 다르고, map character와 runtime state도 늘어난다. 같은 파일 안에 조건문으로 섞으면 mandatory 흐름의 단순성이 깨진다. 별도 source tree를 두면 mandatory 구현은 그대로 유지되고, bonus 빌드는 확장된 구현만 선택한다.

## Code-level Implementation Reading

`Makefile`은 `PARSE`/`EXEC` 목록을 먼저 만들고, bonus에서는 `$(addsuffix _bonus, $(PARSE))`와 `$(addsuffix _bonus, $(EXEC))`로 같은 이름 체계의 확장 구현을 선택한다. `WITH_BONUS`가 켜지면 `OBJ_SWITCH = $(BOBJS)`가 되고, 링크 후 `REMOVE = $(OBJS) $(DEPS)`로 mandatory object를 지운다. 그래서 하나의 `cub3D` binary 이름을 유지하면서도 mandatory와 bonus object가 섞이지 않는다. 이 구조는 subject 평가에서 `make`와 `make bonus`를 분리해야 하는 요구와 맞물린다.

`include/cub3d_bonus.h`는 bonus state를 `t_play` 안에 통합한다. mandatory의 `t_map`, `t_ray`, `t_wall`, `t_player`를 유지하면서 `t_mini mini`, `t_door door`, `t_cursor cursor`를 추가한다. 즉 bonus 기능이 rendering loop 바깥의 별도 시스템이 아니라, raycasting 결과와 map 상태를 공유하는 확장으로 동작한다. door를 `t_ray.is_door`에 저장하는 것도 같은 설계다. wall hit 계산 결과가 texture 선택 단계까지 이어져야 하므로, DDA 중 어떤 cell에 부딪혔는지를 ray state에 남긴다.

`exec_bonus/sprite_bonus.c`의 `check_sprite()`는 ray가 만난 cell을 `1`, `D`, `d`로 나누어 처리한다. `1`은 일반 벽, `D`는 열린 door texture, `d`는 닫힌 door texture로 구분하고 각각 `FALSE`, `TRUE`, `CLOSE`를 `play->ray.is_door`에 넣는다. 문을 별도 collision object로 만들지 않고 map character로 표현했기 때문에 DDA는 기존 wall 탐색 루프를 그대로 사용한다. `calc_sprite_ray()`는 mandatory의 ray hit 계산과 같은 방식으로 `size_x/size_y`를 비교해 grid를 전진하고, `check_sprite()`가 hit를 선언할 때 멈춘다. 이 코드가 door/sprite까지 벽과 같은 투영 공식으로 처리할 수 있게 만든다.

`change_sprite()`는 `static int i`를 frame counter로 사용하고, 10 frame 단위로 `portal1.xpm`부터 `portal9.xpm`까지 교체한다. sprite 애니메이션을 별도 timer나 thread로 분리하지 않은 이유는 MLX loop가 이미 frame 단위로 호출되기 때문이다. frame counter를 rendering 흐름 안에 두면 animation state와 rendering state가 같은 tick에서 갱신되어 texture 교체 타이밍이 단순해진다.

`exec_bonus/door_bonus.c`의 `click_door()`는 player 좌표를 정수 grid로 내린 뒤 `play->ray.dir_x/dir_y`의 주 방향을 보고 바로 앞 cell만 토글한다. `fabs(other_axis) < 0.5` 조건을 둔 이유는 대각선으로 바라볼 때 옆 cell이 잘못 열리는 것을 막기 위해서다. 실제 토글은 `change_door()`가 `D <-> d` 문자 변환만 수행한다. door 상태를 map 자체에 저장했기 때문에 collision, ray hit, minimap이 같은 source of truth를 읽는다.

`exec_bonus/cursor_bonus.c`의 `change_cursor1()`은 `v_1.xpm`부터 `v_36.xpm` 계열을 `i / 10`으로 선택한다. `get_cursor_sprite()`가 기존 `play->cursor.image`를 `mlx_destroy_image()`로 해제한 뒤 새 image를 로드하는 것은 MLX image 객체가 누적되지 않게 하기 위한 처리다. cursor animation 역시 sprite처럼 loop counter 기반으로 구현되어, input/render loop와 같은 시간 축에서 갱신된다.
