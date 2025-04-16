/**
 * @file arch_multimedia_library.h
 * @brief Header file for the Arch Multimedia Library, providing functionality
 *        for creating and managing X11 windows with OpenGL rendering support.
 *
 * This library simplifies the creation and management of X11 windows and
 * OpenGL contexts for multimedia applications. It includes functions for
 * creating windows, setting their properties, and cleaning up resources.
 */

#ifndef ARCH_MULTIMEDIA_LIBRARY_H
#define ARCH_MULTIMEDIA_LIBRARY_H

#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

/**
 * @struct arch_multimedia_library_window
 * @brief Represents a window with an OpenGL context.
 *
 * This structure contains information about an X11 window, its OpenGL context,
 * dimensions, and state.
 *
 * @var arch_multimedia_library_window::display
 * The X11 display connection.
 *
 * @var arch_multimedia_library_window::glx_context
 * The OpenGL rendering context.
 *
 * @var arch_multimedia_library_window::window_id
 * The X11 window ID.
 *
 * @var arch_multimedia_library_window::width
 * The width of the window in pixels.
 *
 * @var arch_multimedia_library_window::height
 * The height of the window in pixels.
 *
 * @var arch_multimedia_library_window::is_closing
 * A flag indicating whether the window is in the process of closing.
 */
typedef struct {
    Display *display; // X11 display connection
    GLXContext glx_context; // OpenGL context
    unsigned long window_id;
    int width;
    int height;
    bool is_closing;
    // is fullscreen would be a cool feature ?
} arch_multimedia_library_window;



/**
 * @brief Creates a new window with an OpenGL context.
 *
 * This function initializes an X11 window with the specified dimensions and
 * title, and sets up an OpenGL rendering context for it.
 *
 * @param width The width of the window in pixels.
 * @param height The height of the window in pixels.
 * @param title The title of the window.
 * @return A pointer to the created window structure, or NULL on failure.
 */
arch_multimedia_library_window* arch_multimedia_library_create_window(int width, int height, const char *title);

/**
 * @brief Destroys a window and releases its resources.
 *
 * This function cleans up the resources associated with a window, including
 * its OpenGL context and X11 window.
 *
 * @param window A pointer to the window structure to be destroyed.
 */
void arch_multimedia_library_destroy_window(arch_multimedia_library_window *window);

/**
 * @brief Sets the title of a window.
 *
 * This function updates the title of the specified window.
 *
 * @param window A pointer to the window structure.
 * @param title The new title for the window.
 */
void arch_multimedia_library_set_window_title(arch_multimedia_library_window *window, const char *title);

/**
 * @brief Sets the size of a window.
 *
 * This function updates the dimensions of the specified window.
 *
 * @param window A pointer to the window structure.
 * @param width The new width of the window in pixels.
 * @param height The new height of the window in pixels.
 */
void arch_multimedia_library_set_window_size(arch_multimedia_library_window *window, int width, int height);

#endif // ARCH_MULTIMEDIA_LIBRARY_H