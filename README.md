# 🖼️ Arch Multimedia Library

[![Build Status](https://img.shields.io/badge/build-passing-brightgreen?style=flat-square)](https://github.com/archibald-carrion/Arch-multimedia-library/actions)

<!-- add more shield about passing linters and sanitizer -->

> A lightweight, low-level C multimedia library using **X11 + OpenGL** for creating windows and drawing on Linux (perfect for WSL2 and retro game dev vibes 🎮🧪).


## ✨ Features

- Minimal dependencies (no SDL, SFML or GLFW)
- Window creation & OpenGL context management via X11 & GLX
- Drawing 2D shapes like rectangles and lines

### TODO
- [ ] Add more primitives (circles, polygons, etc.) to the arch_multimedia_library_graphic
- [ ] Add input handling (keyboard, mouse, etc.)
- [ ] Add sound support
- [ ] Add image loading support for textures
- [ ] Check for memory leaks and undefined behavior
- [ ] Check for linter errors
- [ ] Add more examples
- [ ] Add makefile
- [ ] Add Cmake to the project


---

## 📦 Installation

### ✅ Compiling using command line
1. Clone the repository:
```bash
git clone https://github.com/archibald-carrion/Arch-multimedia-library.git
```
2. Navigate into the directory:
```bash
cd Arch-multimedia-library
```
3. Compile the application:
```bash
gcc ./tests/static_example.c ./include/*.h ./src/*.c -o cool_app -lX11 -lGL
```
4. Run the application:
```bash
./cool_app
```

### ✅ Compiling using CMake
TODO


### ✅ Compiling using Makefile
TODO

## 🧱 Project Structure
```txt
# Arch-multimedia-library
├── README.md
└── arch_multimedia_library
    ├── cool_app
    ├── examples
    ├── include
    │   ├── arch_multimedia_library.h
    │   └── arch_multimedia_library_graphic.h
    ├── src
    │   ├── arch_multimedia_library.c
    │   ├── arch_multimedia_library_graphic.c
    │   └── utils.c
    └── tests
        └── static_example.c
```