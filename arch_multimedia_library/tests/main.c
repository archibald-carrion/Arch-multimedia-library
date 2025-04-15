#include "../include/arch_multimedia_library.h"
#include <stdio.h>

int main(int argc, char*argv[]) {
    arch_multimedia_library_window *window = arch_multimedia_library_create_window(800, 600, "Arch Window");
           
    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        return 1;
    }

    bool running = true;
    while (running) {
        while (XPending(window->display)) {
            XEvent xev;
            XNextEvent(window->display, &xev);
            if (xev.type == KeyPress)
                running = false;
        }

        glClearColor(0.2, 0.5, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glXSwapBuffers(window->display, window->window_id);
        usleep(16000); // ~60 FPS
    }

    // Destroy the window
    arch_multimedia_library_destroy_window(window);

    return 0;
}