#include "../include/arch_multimedia_library.h"
#include "../include/arch_multimedia_library_graphic.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    arch_multimedia_library_window *window = arch_multimedia_library_create_window(800, 600, "Arch Window");

    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        return 1;
    }

    // Register for window close (X button) event, for the moment it's here, but in future implementation
    // it should be in the input management system of arch_multimedia_library
    Atom wm_delete = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(window->display, window->window_id, &wm_delete, 1);

    bool running = true;
    while (running && !window->is_closing) {
        // Event handling loop
        while (XPending(window->display)) {
            XEvent xev;
            XNextEvent(window->display, &xev);

            // Handle keypresses (temporary)
            if (xev.type == KeyPress)
                running = false;

            // Handle window close (X) button so we can close the app correctly
            if (xev.type == ClientMessage && (Atom)xev.xclient.data.l[0] == wm_delete) {
                running = false;
                window->is_closing = true;
            }
        }

        arch_graphics_clear_screen(
            window,
            1.0f, 0.5f, 0.2f, 1.0f
        );

        // Draw a rectangle in the middle of the screen
        arch_graphics_draw_rect(
            window,
            window->width / 2 - 50,
            window->height / 2 - 50,
            100, 200,
            0.0f, 0.0f, 1.0f, 1.0f
        );

        // Draw a line from the top left to the bottom right
        arch_graphics_draw_line(
            window,
            0, 0,
            window->width, window->height,
            5, // thickness
            1.0f, 0.0f, 0.0f, 1.0f
        );

        arch_graphics_render(window);
        usleep(16000); // ~60 FPS
    }

    printf("Closing window...\n");
    arch_multimedia_library_destroy_window(window);

    return 0;
}
