# Input and Game Loop 구현 해설

## 목적

input/game loop 모듈은 keyboard event를 player movement와 rotation으로 바꾸고, 매 frame마다 game state를 rendering한다. MiniLibX의 event hook 구조에 맞춰 press/release 상태를 저장한다.

## Source Map

- `exec/key.c`: key state 처리.
- `exec/key_event.c`: key press/release/exit event hook.
- `exec/key_move.c`: 이동과 회전 계산.
- `exec/logic.c`: loop hook에서 state update와 render 호출.
- `exec/init.c`: hook 등록과 game start.

## 핵심 자료구조

`t_key`는 `w`, `a`, `s`, `d`, `left`, `right` 상태를 정수 flag로 저장한다. key event가 들어올 때 즉시 이동하지 않고 flag를 바꾼다. loop는 flag를 읽어 현재 frame에서 어떤 movement를 적용할지 결정한다.

`t_player`는 위치, step 방향, 크기, 이동 속도, 회전 속도를 가진다. 이동 함수는 player 좌표를 직접 갱신하고, ray direction과 camera plane은 회전 함수에서 함께 갱신된다.

## 구현 방식

키보드 입력은 event-driven이고 rendering은 loop-driven이다. 이 둘을 직접 연결하면 key repeat나 event timing에 따라 이동 속도가 흔들릴 수 있다. 그래서 구현은 key press/release를 상태 flag로 저장하고, loop에서 일정한 방식으로 이동을 적용한다.

충돌 처리는 다음 위치가 wall인지 확인한 뒤 좌표를 갱신한다. x/y 이동을 나눠 검사하면 벽 모서리에서 한 축 이동은 허용하고 다른 축 이동은 막는 방식으로 움직임을 처리할 수 있다.

## 흐름

1. `init_game()`이 window와 image를 만들고 hook을 등록한다.
2. key press event는 `t_key` flag를 `TRUE`로 만든다.
3. key release event는 flag를 `FALSE`로 되돌린다.
4. loop hook은 현재 flag를 읽어 이동/회전을 적용한다.
5. 갱신된 player/ray 상태로 frame을 다시 렌더링한다.
6. ESC 또는 window close event는 resource cleanup 후 종료한다.

## 왜 이 구조인지

event는 입력 상태만 바꾸고, loop가 실제 simulation을 처리한다. 이 구조는 input handling과 game update를 분리해 frame 단위 움직임을 안정적으로 만든다.

## Code-level Implementation Reading

`move_w()`는 x축 이동과 y축 이동을 따로 검사한다. 다음 x 위치가 wall이 아니면 x만 갱신하고, 다음 y 위치가 wall이 아니면 y만 갱신한다. 이 구현은 대각선이나 벽 모서리에서 한 축 이동만 가능한 상황을 자연스럽게 처리한다.

```c
if (play->map.field[(int)play->player.y]
[(int)(play->player.x + (play->ray.dir_x * speed) + hit)] == '0')
	play->player.x += play->ray.dir_x * speed;
...
if (play->map.field[(int)(play->player.y +
(play->ray.dir_y * speed) + hit)][(int)play->player.x] == '0')
	play->player.y += play->ray.dir_y * speed;
```

`hit = 0.001` 보정은 진행 방향으로 아주 작은 여유를 더해 벽 경계에 붙었을 때 floating point 좌표가 cell 경계에 걸리는 문제를 줄인다. 이 값은 collision check가 `int` cast로 map cell을 고르는 구조이기 때문에 들어간다.

`move_a()`와 `move_d()`는 `ray.dir`이 아니라 `ray.plane`을 사용한다. camera plane은 player가 바라보는 방향에 수직인 벡터이므로, strafe 이동은 direction vector가 아니라 plane vector를 따라 움직인다.
