gcc ./tests/main.c ./include/arch_multimedia_library.h ./src/arch_multimedia_library.c -o cool_app -lX11 -lGL

```txt
.
├── README.md
└── arch_multimedia_library
    ├── cool_app
    ├── examples
    ├── include
    │   ├── arch_multimedia_library.h
    │   └── arch_multimedia_library_graphic.h
    ├── opengl_app
    ├── src
    │   ├── arch_multimedia_library.c
    │   ├── arch_multimedia_library_graphic.c
    │   └── utils.c
    └── tests
        └── main.c
```