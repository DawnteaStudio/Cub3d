# Raycasting and Rendering 구현 해설

## 목적

raycasting/rendering 모듈은 2D grid map과 player 방향을 1인칭 3D 화면으로 변환한다. 화면의 각 x좌표마다 ray를 쏘고, 벽과 충돌한 거리와 방향을 계산한 뒤 texture column을 그린다.

## Source Map

- `exec/ray.c`: ray 방향, DDA stepping, wall hit 계산.
- `exec/render.c`: screen buffer와 wall texture rendering.
- `exec/init.c`: MiniLibX, image, texture 초기화.
- `exec/logic.c`: frame update와 rendering loop.
- `exec/free.c`: image/map/resource cleanup.
- `include/cub3d.h`: `t_ray`, `t_wall`, `t_image`, `t_player`.

## 핵심 자료구조

`t_ray`는 player direction과 camera plane, ray direction, delta distance, side distance를 저장한다. 이 값들은 한 frame 안에서 각 screen column마다 갱신된다.

`t_wall`은 ray가 벽에 닿은 뒤 rendering에 필요한 값을 담는다. wall distance, draw start/end, texture x/y, texture step이 포함된다. ray 계산과 pixel drawing 사이의 중간 결과를 구조체로 고정해 rendering 함수가 같은 값을 공유한다.

## 구현 방식

렌더링은 frame buffer를 먼저 채우고 MiniLibX image를 window에 출력하는 방식이다. 직접 window에 pixel을 하나씩 그리는 대신 image buffer를 사용하므로, 한 frame의 결과를 메모리에서 완성한 뒤 화면에 반영한다.

각 column에서 ray는 player position에서 시작한다. DDA 방식으로 map grid 경계를 따라 이동하며 wall cell을 찾는다. wall에 닿으면 perpendicular distance를 계산해 벽 높이를 정하고, 어떤 방향의 벽에 닿았는지에 따라 texture를 선택한다.

## 렌더링 단계

1. floor/ceiling color로 background를 채운다.
2. screen x좌표마다 camera x 값을 계산한다.
3. ray direction과 delta distance를 만든다.
4. map cell을 따라 DDA를 진행한다.
5. wall hit side와 distance를 결정한다.
6. wall height와 texture coordinate를 계산한다.
7. image buffer에 texture pixel을 복사한다.
8. 완성된 image를 window에 출력한다.

## 왜 이 구조인지

ray 계산과 wall drawing은 서로 다른 책임이다. `t_ray`는 충돌을 찾기 위한 수학 상태를 들고, `t_wall`은 화면에 그릴 벽 조각의 상태를 든다. 이 분리 덕분에 DDA 계산을 수정해도 texture drawing 코드는 같은 인터페이스를 사용할 수 있다.

## Code-level Implementation Reading

`ray_setting()`은 화면 x좌표를 camera plane의 좌표로 바꾸기 위해 `camera_x = 2 * x / win_w - 1`을 사용한다. 이 값은 화면 왼쪽을 -1, 중앙을 0, 오른쪽을 1로 정규화한다. 이후 `dir + plane * camera_x`로 column별 ray direction을 만든다.

```c
camera_x = 2 * x / (double)play->win_w - 1;
play->ray.ray_x = play->ray.dir_x + play->ray.plane_x * camera_x;
play->ray.ray_y = play->ray.dir_y + play->ray.plane_y * camera_x;
```

`calc_ray_hit()`은 `size_x`와 `size_y` 중 더 작은 쪽으로 한 grid씩 이동한다. 이 DDA 구조는 ray가 다음 x grid line에 먼저 닿는지, y grid line에 먼저 닿는지를 비교하며 map cell을 전진한다. 벽을 만나면 loop를 끝내고, 충돌한 축에 따라 wall distance 공식을 다르게 적용한다.

```c
if (play->ray.size_x < play->ray.size_y)
{
	play->ray.size_x += play->ray.delta_x;
	play->map.start_x += play->player.step_x;
	play->wall.collision_wall = WALL_X;
}
else
{
	play->ray.size_y += play->ray.delta_y;
	play->map.start_y += play->player.step_y;
	play->wall.collision_wall = WALL_Y;
}
```

`calc_hit_point_texture()`는 충돌 위치의 fractional part를 `wall_x`로 만들고 `texture_x`를 계산한다. ray 방향에 따라 texture x좌표를 뒤집는 분기가 들어간다. 이 분기가 없으면 같은 벽 texture가 방향에 따라 좌우 반전되어 보인다.

`render_background()`는 RGB 배열을 bit shift로 packed color로 변환한다. parsing 단계에서 RGB를 `int[3]`으로 보관한 이유가 여기서 드러난다. renderer는 문자열 파싱 없이 바로 `r << 16 | g << 8 | b`를 수행한다.
