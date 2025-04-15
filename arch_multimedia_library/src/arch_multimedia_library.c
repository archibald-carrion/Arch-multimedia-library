#include "../include/arch_multimedia_library.h"

/**
 * @brief Creates a window with OpenGL context using X11 and GLX.
 * @param width The width of the window.
 * @param height The height of the window.
 * @param title The title of the window.
 * @return A pointer to the created window structure, or NULL on failure.
 */
arch_multimedia_library_window* arch_multimedia_library_create_window(int width, int height, const char *title) {

    arch_multimedia_library_window *window = malloc(sizeof(arch_multimedia_library_window));
    if (!window) {
        fprintf(stderr, "Failed to allocate memory for window\n");
        return NULL;
    }

    window->display = XOpenDisplay(NULL);
    if (!window->display) {
        fprintf(stderr, "Cannot connect to X server\n");
        free(window);
        return NULL;
    }

    // Choose a visual
    static int visualAttribs[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        None
    };

    int screen = DefaultScreen(window->display);
    XVisualInfo *vi = glXChooseVisual(window->display, screen, visualAttribs);
    if (!vi) {
        fprintf(stderr, "No appropriate visual found\n");
        XCloseDisplay(window->display);
        free(window);
        return NULL;
    }

    // Create window
    Window root = RootWindow(window->display, vi->screen);
    Colormap cmap = XCreateColormap(window->display, root, vi->visual, AllocNone);
    XSetWindowAttributes swa = {
        .colormap = cmap,
        .event_mask = ExposureMask | KeyPressMask | StructureNotifyMask
    };

    window->window_id = XCreateWindow(window->display, root, 0, 0, width, height, 0,
                                       vi->depth, InputOutput, vi->visual,
                                       CWColormap | CWEventMask, &swa);

    XStoreName(window->display, window->window_id, title);
    XMapWindow(window->display, window->window_id);

    window->width = width;
    window->height = height;
    window->is_closing = false;

    /*
    https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glXCreateContext.xml
    */

    window->glx_context = glXCreateContext(window->display, vi, NULL, GL_TRUE);
    if (!window->glx_context) {
        fprintf(stderr, "Failed to create OpenGL context\n");
        XDestroyWindow(window->display, window->window_id);
        XCloseDisplay(window->display);
        free(window);
        return NULL;
    }

    glXMakeCurrent(window->display, window->window_id, window->glx_context);
    return window;
}

/**
 * @brief Destroys the window and cleans up resources.
 * @param window The window to be destroyed.
 * 
 * This function releases all resources associated with the specified window,
 * including the OpenGL context and the X window itself.
 */
void arch_multimedia_library_destroy_window(arch_multimedia_library_window *window) {
    if (window) {
        glXMakeCurrent(window->display, None, NULL);
        glXDestroyContext(window->display, window->glx_context);
        XDestroyWindow(window->display, window->window_id);
        XCloseDisplay(window->display);
        free(window);
    }
}

void arch_multimedia_library_set_window_title(arch_multimedia_library_window *window, const char *title) {

    if (window && title) {
        XStoreName(window->display, window->window_id, title);
    }
}

void arch_multimedia_library_set_window_size(arch_multimedia_library_window *window, int width, int height) {

}
