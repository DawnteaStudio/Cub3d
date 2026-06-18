# cub3D

> 42 Seoul 팀 프로젝트로 구현한 Wolfenstein 3D 스타일의 raycasting 그래픽 엔진입니다. `.cub` 설정 파일을 파싱하고, MiniLibX로 1인칭 시점의 맵 탐색 화면을 렌더링합니다.

## Overview

`cub3D`는 C와 MiniLibX를 사용해 2D 맵 데이터를 3D처럼 보이는 화면으로 변환하는 프로젝트입니다.
맵 파일에서 벽 텍스처, 바닥/천장 색상, 플레이어 시작 위치를 읽고, raycasting으로 각 화면 column마다 벽과의 거리를 계산해 렌더링합니다.

이 저장소는 mandatory 구현과 bonus 구현을 함께 포함합니다.

## Features

- `.cub` 파일 입력 검증
- 벽 텍스처 경로와 바닥/천장 RGB 정보 파싱
- 맵 폐쇄 여부와 플레이어 시작 위치 검증
- BFS 기반 맵 유효성 검사
- MiniLibX window/image buffer 기반 렌더링
- `W`, `A`, `S`, `D` 이동과 방향키 회전
- raycasting 기반 벽 충돌 및 거리 계산
- bonus 빌드에서 sprite, door, cursor 관련 기능 확장

## Architecture

```text
.
├── parse/          # mandatory map/config parsing and validation
├── exec/           # mandatory game init, input, raycasting, rendering
├── parse_bonus/    # bonus parser
├── exec_bonus/     # bonus runtime features
├── include/        # shared structs, constants, function prototypes
├── libft/          # project-local libft and get_next_line
├── minilibx/       # MiniLibX dependency
├── map/            # sample .cub maps
└── textures/       # xpm wall, sprite, and bonus textures
```

핵심 상태는 `t_play` 구조체에 모입니다. 이 구조체가 MiniLibX 핸들, window, map, player, ray, wall, key state, texture image를 함께 들고 있으며 parser와 renderer가 같은 실행 컨텍스트를 공유합니다.

## Build

macOS의 MiniLibX framework 링크를 전제로 합니다.

```bash
make
```

bonus 기능을 포함해 빌드하려면:

```bash
make bonus
```

정리 명령:

```bash
make clean
make fclean
make re
```

## Usage

```bash
./cub3D map/test_map1.cub
```

bonus map 예시:

```bash
make bonus
./cub3D map/test_map2_bonus.cub
```

프로그램은 인자를 정확히 하나만 받습니다. 입력이 없거나 잘못된 파일이면 에러를 출력하고 종료합니다.

## `.cub` Map Format

맵 파일은 texture/color 정보와 map grid로 구성됩니다.

- `NO`, `SO`, `WE`, `EA`: 방향별 벽 텍스처
- `F`: floor RGB color
- `C`: ceiling RGB color
- `1`: wall
- `0`: empty space
- `N`, `S`, `W`, `E`: player start position and direction

맵은 외부로 열려 있으면 안 되며, 플레이어 시작 위치는 하나여야 합니다.

## Implementation Notes

- `parse/main.c`는 인자 수를 확인한 뒤 `read_map`, `is_valid_info`, `init_game` 순서로 실행을 시작합니다.
- `parse/check_file.c`, `parse/check_info.c`, `parse/check_map.c`가 파일명, texture/color 정보, map 구조를 나눠 검증합니다.
- `parse/bfs.c`와 queue 유틸리티는 map이 외부 공간과 연결되는지 검사하는 데 사용됩니다.
- `exec/ray.c`와 `exec/render.c`가 ray 방향, 벽 거리, texture 좌표를 계산해 화면 버퍼에 그립니다.
- `exec/key*.c`는 press/release state를 유지해 이동과 회전을 부드럽게 처리합니다.

## Team

- `sewopark`
- `erho`

42 프로젝트 특성상 과제 요구사항을 만족하는 학습용 구현이며, 범용 게임 엔진이나 production renderer를 목표로 한 코드는 아닙니다.
