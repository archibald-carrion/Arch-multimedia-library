#include "../include/arch_multimedia_library_graphic.h"

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
    // Set the color for the rectangle
    glColor4f(r, g, b, a);

    // Draw the rectangle using OpenGL
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
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
}