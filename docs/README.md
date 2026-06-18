# cub3D Implementation Docs

이 문서는 `cub3D` 소스코드를 모듈 단위로 읽기 위한 구현 해설입니다.

## 문서 목록

- [Parsing](./parsing.md)
- [Map Validation](./map-validation.md)
- [Raycasting and Rendering](./raycasting-rendering.md)
- [Input and Game Loop](./input-and-game-loop.md)
- [Bonus Features](./bonus-features.md)

## 읽는 순서

1. `parse/main.c`에서 실행 진입 흐름을 확인합니다.
2. `include/cub3d.h`의 `t_play`, `t_map`, `t_ray`, `t_wall` 구조를 먼저 읽습니다.
3. parsing 문서를 통해 `.cub` 파일이 runtime state로 정규화되는 과정을 봅니다.
4. raycasting/rendering 문서에서 map state가 화면 column으로 변환되는 과정을 읽습니다.
