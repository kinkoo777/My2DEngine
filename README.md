# My2DEngine

```
engine/        the engine (static library, shared by all games)
  core/          Window, Time
  events/        Event system
  input/         InputManager, KeyCodes, MouseButton
  math/          Vector2
  renderer/      Shader, Renderer, Texture, Camera, buffers
  geometry/      Geometry, Quad
  scene/         GameObject, Scene, Transform, CameraFollow
  shaders/       basic.vert / basic.frag (copied to every game)
games/         one folder = one game
  Snake/
  _Template/     starter code for new games (not built itself)
vendor/        third-party code (glad, stb_image)
```

Engine includes are written from the `engine/` root:
`#include "renderer/Renderer.h"`, `#include "input/InputManager.h"`, ...

## Build & run

```sh
cmake -S . -B build
cmake --build build --target run_Snake      # build + run
```

The executable ends up in `build/bin/<Game>/` with its `assets/` next to it.
To start it by hand: `cd build/bin/Snake && ./Snake`.

## Windows

Install Visual Studio 2022 with the **Desktop development with C++** workload
and [vcpkg](https://github.com/microsoft/vcpkg). Set `VCPKG_ROOT` to the vcpkg
directory, then configure and build from a Developer PowerShell:

```powershell
cmake --preset windows-vcpkg
cmake --build --preset windows-debug --target run_Snake
```

The Windows executable is written to `build/windows/bin/Snake/Debug/`.

## New game

```sh
cp -R games/_Template games/MyGame
cmake -S . -B build
cmake --build build --target run_MyGame
```

- Put images/sounds in `games/MyGame/assets/` and load them as `"assets/file.png"`.
- Any `.cpp` you add to the game folder is compiled automatically (re-run the cmake configure step after adding files).
