/**
 * @file arch_multimedia_library_graphic.h
 * @brief Header file for graphic-related functionalities in the Arch Multimedia Library.
 *
 * This file provides declarations for functions that allow drawing basic
 * graphical elements such as rectangles and lines with specified colors.
 */

#ifndef ARCH_MULTIMEDIA_LIBRARY_GRAPHIC_H
#define ARCH_MULTIMEDIA_LIBRARY_GRAPHIC_H

#include "arch_multimedia_library.h"

/**
 * @brief Draws a rectangle on the screen.
 *
 * This function draws a rectangle at the specified position with the given
 * dimensions and color.
 *
 * @param x The x-coordinate of the top-left corner of the rectangle.
 * @param y The y-coordinate of the top-left corner of the rectangle.
 * @param width The width of the rectangle.
 * @param height The height of the rectangle.
 * @param r The red component of the rectangle's color (0.0 to 1.0).
 * @param g The green component of the rectangle's color (0.0 to 1.0).
 * @param b The blue component of the rectangle's color (0.0 to 1.0).
 * @param a The alpha (transparency) component of the rectangle's color (0.0 to 1.0).
 */
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
);

/**
 * @brief Draws a line between two points on the screen.
 *
 * This function draws a line from the starting point (x1, y1) to the ending
 * point (x2, y2) with the specified color.
 *
 * @param x1 The x-coordinate of the starting point of the line.
 * @param y1 The y-coordinate of the starting point of the line.
 * @param x2 The x-coordinate of the ending point of the line.
 * @param y2 The y-coordinate of the ending point of the line.
 * @param r The red component of the line's color (0.0 to 1.0).
 * @param g The green component of the line's color (0.0 to 1.0).
 * @param b The blue component of the line's color (0.0 to 1.0).
 * @param a The alpha (transparency) component of the line's color (0.0 to 1.0).
 */
void arch_graphics_draw_line(
    arch_multimedia_library_window *window,
    float x1,
    float y1,
    float x2,
    float y2,
    unsigned int thickness,
    float r,
    float g,
    float b,
    float a
);

/**
 * @brief Clears the screen with a specified color.
 *
 * This function fills the entire screen with the specified color.
 *
 * @param r The red component of the clear color (0.0 to 1.0).
 * @param g The green component of the clear color (0.0 to 1.0).
 * @param b The blue component of the clear color (0.0 to 1.0).
 * @param a The alpha (transparency) component of the clear color (0.0 to 1.0).
 */
void arch_graphics_clear_screen(
    arch_multimedia_library_window *window,
    float r,
    float g,
    float b,
    float a
);

/**
 * @brief Renders the graphics on the screen.
 *
 * This function is responsible for rendering the graphics on the screen.
 * It should be called after drawing operations to display the results.
 * 
 * @param window The window where the graphics will be rendered.
 */
void arch_graphics_render(
    arch_multimedia_library_window *window
);

#endif // ARCH_MULTIMEDIA_LIBRARY_GRAPHIC_H