*This project has been created as part of the 42 curriculum by ridoming, bsaldana.*

# cub3D

## Description

cub3D is a first-person view of a maze, in the spirit of Wolfenstein 3D. The program reads a map.cub file, builds a 2D grid of walls, and draws a 3D view by casting one ray per screen column.

The goal is to parse a `.cub` scene, place the player, and render textured walls with a coloured floor and ceiling. Movement is checked against the grid so the player cannot walk through walls. Looking around rotates the view without moving the player.

The window is 1024×768. Each frame walks every column from the player’s position until the ray hits a wall, measures how far that wall is, and draws a vertical stripe whose height depends on that distance. Near walls fill more of the screen. Far walls are short.

## Instructions

### Requirements

The MiniLibX library shipped in `mlx/` and the libft in `includes/libft` are built by the Makefile. On Linux you also need a C compiler, `make`, and the X11 libraries MiniLibX links against (`libX11`, `libXext`, `libbsd`).

### Compilation

The project compiles with `make`.

```bash
make
```

### Execution

Run it with `./cub3D` followed by the path to a `.cub` file.

```bash
./cub3D maps/map.cub
```

### Controls

- `W` / `S` move forward and backward.
- `A` / `D` strafe left and right.
- `←` / `→` turn left and right.
- `ESC` quits.

Closing the window also quits. Keys can be held; the view is redrawn only when the player moves or turns.

### Scene file

A `.cub` file lists the four wall textures and the floor and ceiling colours, then the map. Texture paths are relative to the directory from which you launch the program.

```text
NO ./textures/Brick/Brick01.xpm
SO ./textures/Stone/Stone01.xpm
WE ./textures/Tiles/Tiles05.xpm
EA ./textures/Wood/Wood02.xpm

F 20,120,100
C 50,150,40

111111
100001
10N001
111111
```

- `NO`, `SO`, `WE` and `EA` are paths to XPM wall textures.
- `F` and `C` are the floor and ceiling colours, as `R,G,B` values from 0 to 255.
- The map uses `1` for a wall, `0` for empty space, and a single `N`, `S`, `E` or `W` for the player’s starting cell and facing. The map must be closed by walls.

## Resources

- [Raycasting](https://lodev.org/cgtutor/raycasting.html), Lode Vandevenne. Reference for the camera plane, the DDA grid walk, the perpendicular wall distance, and texture mapping used in `src/render/`.
- [MiniLibX](https://github.com/42Paris/minilibx-linux). The windowing and image API used to open the window, load XPM files, and draw pixels. A copy lives in `mlx/`.
- Wolfenstein 3D (id Software, 1992, http://users.atw.hu/wolf3d/). The game whose column-based raycaster this project reproduces in simplified form.

### Use of AI

AI was used as a tutor while learning the renderer, not as a substitute for the implementation. It resolved the questions we had about implementing the DDA algorithm and translating vector mathematics into code. Those explanations follow the Lode Vandevenne article linked above.
