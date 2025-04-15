#ifndef ARCH_MULTIMEDIA_LIBRARY_H
#define ARCH_MULTIMEDIA_LIBRARY_H

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct {
    Display *display; // X11 display connection
    GLXContext glx_context; // OpenGL context
    unsigned long window_id;
    int width;
    int height;
    bool is_closing;
    // is fullscreen would be a cool feature ?
} arch_multimedia_library_window;

arch_multimedia_library_window* arch_multimedia_library_create_window(int width, int height, const char *title);
void arch_multimedia_library_destroy_window(arch_multimedia_library_window *window);
void arch_multimedia_library_set_window_title(arch_multimedia_library_window *window, const char *title);
void arch_multimedia_library_set_window_size(arch_multimedia_library_window *window, int width, int height);

#endif // ARCH_MULTIMEDIA_LIBRARY_H