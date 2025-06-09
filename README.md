# Cube

This project is a small 3D cube simulation built with C++ and [SFML](https://www.sfml-dev.org/). It renders a cube whose faces can be rotated using the keyboard.

## Building

1. Install SFML (version 2.5 or newer).
2. Generate the build files with CMake:
   ```bash
   cmake -S so-cube -B build
   ```
3. Build the executable:
   ```bash
   cmake --build build
   ```
4. Run the program:
   ```bash
   ./build/so_cube
   ```

## Controls

- **Arrow keys** &ndash; move the cube on the X and Y axes.
- **`=` / `-`** &ndash; move the cube along the Z axis.
- **`1`/`2`** &ndash; rotate around the X axis.
- **`3`/`4`** &ndash; rotate around the Y axis.
- **`5`/`6`** &ndash; rotate around the Z axis.
- **`F` / `G`** &ndash; rotate the front face.
- **`B` / `N`** &ndash; rotate the back face.
- **`U` / `I`** &ndash; rotate the top face.
- **`D` / `S`** &ndash; rotate the bottom face.
- **`R` / `T`** &ndash; rotate the right face.
- **`L` / `K`** &ndash; rotate the left face.

