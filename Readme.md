<div align="center">

<!--here should be a logo, lol, but i have no ppl to draw it-->

# nanogame

</div>
Yet-another-platformer-game-engine. But this one has no .NET, Lua, or weird behaviour (WIP) 

<div align="center">

![Build](https://img.shields.io/badge/Build-passing_locally-blue?style=for-the-badge)
![version](https://img.shields.io/badge/Version-0.1-wakarimasen?style=for-the-badge)
[![Codacy grade](https://img.shields.io/codacy/grade/80bebb6e7ecf4f5fa100b3c6d0f2571f?style=for-the-badge)](https://app.codacy.com/gh/hayatotk/nanogame/dashboard)

</div>

A minimal game engine for 2D platformers, written in C++ (mostly cpp17, but it depends on the platform).  
Designed with modular backends (`*_uni` / `*_native`) for cross-platform builds.

# Build

Clone repo and run:

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
```

# Running

Go back to repo root:

```
cd ..
```

Run the produced binary (name is auto-generated as  
`$NAME-$VERSION_$COMMIT-$STATUS-$PLATFORM`):

```
./build/nanogame-0.1_abcd123-dirty-release-linux
```

Note:  
Currently, level files (`level0.txt`, …) and font (`test.ttf`) are expected  
at the root of the repo. This will change in the future (proper asset format and pipeline TODO).

# Dependencies

for PC/Linux (currently the only platform)

- SDL2  
- SDL2_ttf  
- C++17 stdlib

Linux (Arch/Ubuntu):

```
sudo pacman -Sy sdl2 sdl2_ttf
# or (more if you are an old one who uses Debian-based distros)
sudo apt install libsdl2-dev libsdl2-ttf-dev
```

Windows:  
Use MSYS2 or vcpkg to install SDL2 + SDL2_ttf.

# Project structure

```
src/core/             # game logic (platform-agnostic)
  Player.cpp/.hpp
  Level.cpp/.hpp
  GameScene.cpp/.hpp
  Splash.cpp/.hpp
  InputState.hpp
  IRenderer.hpp
  Scene.hpp

src/platform/         # backends
  sdl_uni/            # SDL universal backend (Input, Renderer, SplashRender, PlayerRender)
  win32_uni/          # (planned) Win32 universal backend
  mobiledarwin_uni/   # (planned) iOS universal backend
  andk_uni/           # (planned) Android universal backend
  samwise_native/     # (planned) PSP native backend
  revolution_native/  # (planned) Wii native backend
  scarlett_native/    # (planned) UWP (Xbox) native backend
  orbis_native/       # (planned) PS4 homebrew semi-native backend
  ..............      # TBD in future

assets/               # sprites, fonts, levels
config.ini
level0.txt ...
```

# OSS used

- SDL2
- SDL2_ttf
- libc++ / libstdc++
- Font: Northrup (test.ttf)

# Contributors

- [hayatotk](https://github.com/hayatotk "rawr, that’s me" )
- maybe YOU?