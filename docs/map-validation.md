# Map Validation 구현 해설

## 목적

map validation은 `.cub` grid가 game world로 사용할 수 있는 폐쇄 공간인지 검증한다. 실행 단계의 collision과 raycasting은 map 외부 접근을 정상 상태로 다루지 않으므로, 시작 전에 map의 구조적 오류를 제거한다.

## Source Map

- `parse/check_map.c`: map 문자, 외곽, 시작 위치 검증.
- `parse/map_utils.c`: `t_map.field` 생성과 map helper.
- `parse/bfs.c`: 연결 요소와 space 탐색.
- `parse/queue.c`: BFS queue 구현.
- `parse/search.c`: BFS 탐색 상태 초기화/해제.

## 핵심 자료구조

`t_queue`와 `t_node`는 BFS를 위한 단순 linked queue다. map validation은 재귀 DFS 대신 queue 기반 BFS를 사용한다. 이 구조는 map 크기에 따라 call stack을 소모하지 않고 탐색 상태를 heap/list로 관리한다.

`t_search`는 탐색 방향 배열, 현재 좌표, outside flag, queue pointer를 묶는다. BFS 중 필요한 임시 상태를 구조체로 묶어 함수 인자를 줄인다.

## 구현 방식

map은 먼저 문자 단위로 검사된다. 허용 문자는 wall, empty space, player direction 등 subject가 정의한 문자다. player 시작 위치는 `start_y`, `start_x`, `direction`으로 저장된다.

그 다음 map이 외부와 연결되는지 확인한다. BFS는 특정 위치에서 연결된 영역을 따라가며, map 경계나 space 처리 규칙을 통해 외부 노출 여부를 판단한다. 열린 공간이 외부와 연결되면 raycasting 중 map 밖 접근이 가능해지므로 invalid map으로 처리한다.

## 왜 BFS를 사용하는지

폐쇄 여부는 한 칸의 local 조건만으로 결정되지 않는다. 내부 빈칸이 여러 칸을 거쳐 외부 공백과 연결될 수 있기 때문이다. BFS는 map의 연결성을 직접 검사하므로, 벽 문자 주변만 확인하는 방식보다 구조적 오류를 더 정확히 잡는다.

## 실패 케이스

- map file extension이 잘못됨
- texture/color 정보가 누락되거나 중복됨
- map에 허용되지 않은 문자가 있음
- player 시작 위치가 없거나 여러 개임
- map이 벽으로 닫혀 있지 않음
- map size가 구현 제한을 벗어남

## Code-level Implementation Reading

`is_valid_map()`은 `visited` 2차원 배열을 먼저 만들고 모든 좌표를 순회한다. 이미 방문했거나 wall인 칸은 `find_target()`에서 즉시 반환한다. 이 구조는 map 전체를 훑되, 연결된 영역 검사는 한 번만 수행하게 만든다.

```c
if (c == '1' || visited[y][x])
	return ;
```

`find_target()`은 문자에 따라 탐색 함수를 분리한다. `0`과 player 방향 문자는 playable component로 보고 `find_component()`를 호출한다. space는 별도 `find_space()`로 보낸다. 이 분리는 빈 공간과 map 외부 공백을 같은 문자처럼 다루지 않기 위한 구조다.

```c
if (c == '0' || (c == 'N' || c == 'S' || c == 'W' || c == 'E'))
	find_component(m, y, x, visited);
else if (c == ' ')
	find_space(m, y, x, visited);
else
	print_error(ERROR_INVALID_MAP);
```

`check_front_space()`는 각 row의 앞쪽 space를 건너뛴 뒤 row 전체가 space이면 invalid map으로 종료한다. 이 코드는 map row가 실질적인 cell 없이 indentation만 가진 경우를 renderer에 넘기지 않는다.

마지막의 `if (m->start_x == -1)` 검사는 player 시작 위치가 실제로 발견됐는지 확인한다. player 위치는 map validation 중 채워지는 runtime 필수 상태이므로, 이 값이 초기값이면 실행 단계로 넘어갈 수 없다.
