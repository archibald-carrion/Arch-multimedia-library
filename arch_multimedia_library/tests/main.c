#include "../include/arch_multimedia_library.h"
#include "../include/arch_multimedia_library_graphic.h"
#include <stdio.h>

int main(int argc, char*argv[]) {
    arch_multimedia_library_window *window = arch_multimedia_library_create_window(800, 600, "Arch Window");
           
    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        return 1;
    }

    bool running = true;
    while (running) {

        // when we'll have a proper event system, we can use it, for the time being, we just check for keypresses
        // and close the window if we get one
        while (XPending(window->display)) {
            XEvent xev;
            XNextEvent(window->display, &xev);
            if (xev.type == KeyPress)
                running = false;
        }

        arch_graphics_clear_screen(
            window,
            1.0f, 0.5f, 0.2f, 1.0f
        );

        // add a rectangle in the middle of the screen
        arch_graphics_draw_rect(
            window,
            window->width / 2 - 50,
            window->height / 2 - 50,
            100, 200,
            0.0f, 0.0f, 1.0f, 1.0f
        );

        // glClearColor(0.2, 0.5, 0.2, 1.0);
        // glClear(GL_COLOR_BUFFER_BIT);
        glXSwapBuffers(window->display, window->window_id);
        usleep(16000); // ~60 FPS
    }

    printf("Closing window...\n");

    // Destroy the window
    arch_multimedia_library_destroy_window(window);

    return 0;
}