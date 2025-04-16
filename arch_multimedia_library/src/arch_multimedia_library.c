#include "../include/arch_multimedia_library.h"

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
    static int visual_attributes[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER, // Enable double buffering instead of single buffering
        None
    };

    int screen = DefaultScreen(window->display);
    XVisualInfo *visual_information = glXChooseVisual(window->display, screen, visual_attributes);
    if (!visual_information) {
        fprintf(stderr, "No appropriate visual found\n");
        XCloseDisplay(window->display);
        free(window);
        return NULL;
    }

    // Create window
    Window root = RootWindow(window->display, visual_information->screen);
    Colormap cmap = XCreateColormap(window->display, root, visual_information->visual, AllocNone);
    XSetWindowAttributes swa = {
        .colormap = cmap,
        .event_mask = ExposureMask | KeyPressMask | StructureNotifyMask
    };

    window->window_id = XCreateWindow(window->display, root, 0, 0, width, height, 0,
                                       visual_information->depth, InputOutput, visual_information->visual,
                                       CWColormap | CWEventMask, &swa);

    XStoreName(window->display, window->window_id, title);
    XMapWindow(window->display, window->window_id);

    window->width = width;
    window->height = height;
    window->is_closing = false;

    /*
    https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/glXCreateContext.xml
    */

    window->glx_context = glXCreateContext(window->display, visual_information, NULL, GL_TRUE);
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
