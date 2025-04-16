#include "../include/arch_multimedia_library_graphic.h"

// TODO: could add a boolean return value to say if operation was successful or not
void arch_graphics_draw_rect(
    arch_multimedia_library_window *window,
    float x,
    float y,
    float width,
    float height,
    float r,
    float g,
    float b,
    float a
)
{
    // Check if the window is initialized
    if (window == NULL || window->display == NULL) {
        fprintf(stderr, "Error: Invalid window parameter in arch_graphics_draw_rect.\n");
        return;
    }

    // Set the color for the rectangle
    glColor4f(r, g, b, a);

    // Draw the rectangle using OpenGL
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();

    // realize the swap buffers when we use double buffering
    // glXSwapBuffers(window->display, window->window_id);
}

void arch_graphics_draw_line(
    arch_multimedia_library_window *window,
    float x1,
    float y1,
    float x2,
    float y2,
    float r,
    float g,
    float b,
    float a
)
{
    // Set the color for the line
    glColor4f(r, g, b, a);

    // Draw the line using OpenGL
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

void arch_graphics_clear_screen(
    arch_multimedia_library_window *window,
    float r,
    float g,
    float b,
    float a
)
{
    // Set the clear color
    glClearColor(r, g, b, a);
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);

    /**
     * https://registry.khronos.org/OpenGL-Refpages/gl4/html/glViewport.xhtml
    */

    // now we can set the viewport and projection
    glViewport(0, 0, window->width, window->height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, window->width, window->height, 0, -1, 1);  // Top-left origin

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    

}


void arch_graphics_render(
    arch_multimedia_library_window *window
)
{
    // Swap the buffers to display the rendered content
    glXSwapBuffers(window->display, window->window_id);
}