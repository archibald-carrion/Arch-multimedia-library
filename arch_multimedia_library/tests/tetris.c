#include "../include/arch_multimedia_library.h"
#include "../include/arch_multimedia_library_graphic.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <X11/keysym.h>

#define GRID_WIDTH 10
#define GRID_HEIGHT 20
#define CELL_SIZE 30

typedef struct {
    int shape[4][4];
    int x, y;
    int size;
    float r, g, b;
} Tetromino;

int grid[GRID_HEIGHT][GRID_WIDTH] = {0};
int grid_colors[GRID_HEIGHT][GRID_WIDTH][3] = {0};

// Tetromino shapes
int shapes[7][4][4] = {
    // I
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}},
    // O
    {{1,1,0,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    // T
    {{0,1,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // S
    {{0,1,1,0}, {1,1,0,0}, {0,0,0,0}, {0,0,0,0}},
    // Z
    {{1,1,0,0}, {0,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // J
    {{1,0,0,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}},
    // L
    {{0,0,1,0}, {1,1,1,0}, {0,0,0,0}, {0,0,0,0}}
};

float colors[7][3] = {
    {0.0f, 1.0f, 1.0f},  // Cyan - I
    {1.0f, 1.0f, 0.0f},  // Yellow - O
    {0.5f, 0.0f, 0.5f},  // Purple - T
    {0.0f, 1.0f, 0.0f},  // Green - S
    {1.0f, 0.0f, 0.0f},  // Red - Z
    {0.0f, 0.0f, 1.0f},  // Blue - J
    {1.0f, 0.5f, 0.0f}   // Orange - L
};

Tetromino current;
int score = 0;
bool game_over = false;

void create_tetromino() {
    int type = rand() % 7;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            current.shape[i][j] = shapes[type][i][j];
        }
    }
    current.x = GRID_WIDTH / 2 - 2;
    current.y = 0;
    current.size = 4;
    current.r = colors[type][0];
    current.g = colors[type][1];
    current.b = colors[type][2];
}

bool check_collision(int offset_x, int offset_y, int test_shape[4][4]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (test_shape[i][j]) {
                int new_x = current.x + j + offset_x;
                int new_y = current.y + i + offset_y;
                
                if (new_x < 0 || new_x >= GRID_WIDTH || new_y >= GRID_HEIGHT) {
                    return true;
                }
                if (new_y >= 0 && grid[new_y][new_x]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void lock_tetromino() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (current.shape[i][j]) {
                int grid_x = current.x + j;
                int grid_y = current.y + i;
                if (grid_y >= 0 && grid_y < GRID_HEIGHT && grid_x >= 0 && grid_x < GRID_WIDTH) {
                    grid[grid_y][grid_x] = 1;
                    grid_colors[grid_y][grid_x][0] = (int)(current.r * 255);
                    grid_colors[grid_y][grid_x][1] = (int)(current.g * 255);
                    grid_colors[grid_y][grid_x][2] = (int)(current.b * 255);
                }
            }
        }
    }
}

void clear_lines() {
    for (int i = GRID_HEIGHT - 1; i >= 0; i--) {
        bool full = true;
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (!grid[i][j]) {
                full = false;
                break;
            }
        }
        
        if (full) {
            score += 100;
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < GRID_WIDTH; j++) {
                    grid[k][j] = grid[k-1][j];
                    grid_colors[k][j][0] = grid_colors[k-1][j][0];
                    grid_colors[k][j][1] = grid_colors[k-1][j][1];
                    grid_colors[k][j][2] = grid_colors[k-1][j][2];
                }
            }
            for (int j = 0; j < GRID_WIDTH; j++) {
                grid[0][j] = 0;
            }
            i++;
        }
    }
}

void rotate_tetromino() {
    int rotated[4][4] = {0};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            rotated[j][3-i] = current.shape[i][j];
        }
    }
    
    if (!check_collision(0, 0, rotated)) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                current.shape[i][j] = rotated[i][j];
            }
        }
    }
}

void draw_game(arch_multimedia_library_window *window) {
    int offset_x = (window->width - GRID_WIDTH * CELL_SIZE) / 2;
    int offset_y = 50;
    
    // Draw grid
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            if (grid[i][j]) {
                arch_graphics_draw_rect(window,
                    offset_x + j * CELL_SIZE,
                    offset_y + i * CELL_SIZE,
                    CELL_SIZE - 2, CELL_SIZE - 2,
                    grid_colors[i][j][0] / 255.0f,
                    grid_colors[i][j][1] / 255.0f,
                    grid_colors[i][j][2] / 255.0f,
                    1.0f);
            }
        }
    }
    
    // Draw current tetromino
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (current.shape[i][j]) {
                arch_graphics_draw_rect(window,
                    offset_x + (current.x + j) * CELL_SIZE,
                    offset_y + (current.y + i) * CELL_SIZE,
                    CELL_SIZE - 2, CELL_SIZE - 2,
                    current.r, current.g, current.b, 1.0f);
            }
        }
    }
    
    // Draw grid lines
    for (int i = 0; i <= GRID_WIDTH; i++) {
        arch_graphics_draw_line(window,
            offset_x + i * CELL_SIZE, offset_y,
            offset_x + i * CELL_SIZE, offset_y + GRID_HEIGHT * CELL_SIZE,
            1, 0.3f, 0.3f, 0.3f, 1.0f);
    }
    for (int i = 0; i <= GRID_HEIGHT; i++) {
        arch_graphics_draw_line(window,
            offset_x, offset_y + i * CELL_SIZE,
            offset_x + GRID_WIDTH * CELL_SIZE, offset_y + i * CELL_SIZE,
            1, 0.3f, 0.3f, 0.3f, 1.0f);
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));
    
    arch_multimedia_library_window *window = arch_multimedia_library_create_window(
        500, 700, "Tetris");
    if (!window) {
        fprintf(stderr, "Failed to create window\n");
        return 1;
    }
    
    Atom wm_delete = XInternAtom(window->display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(window->display, window->window_id, &wm_delete, 1);
    
    create_tetromino();
    
    bool running = true;
    int fall_counter = 0;
    int fall_speed = 30;
    
    while (running && !window->is_closing && !game_over) {
        while (XPending(window->display)) {
            XEvent xev;
            XNextEvent(window->display, &xev);
            
            if (xev.type == KeyPress) {
                KeySym key = XLookupKeysym(&xev.xkey, 0);
                
                if (key == XK_Left) {
                    if (!check_collision(-1, 0, current.shape)) {
                        current.x--;
                    }
                } else if (key == XK_Right) {
                    if (!check_collision(1, 0, current.shape)) {
                        current.x++;
                    }
                } else if (key == XK_Down) {
                    if (!check_collision(0, 1, current.shape)) {
                        current.y++;
                    }
                } else if (key == XK_Up) {
                    rotate_tetromino();
                } else if (key == XK_space) {
                    while (!check_collision(0, 1, current.shape)) {
                        current.y++;
                    }
                } else if (key == XK_Escape) {
                    running = false;
                }
            }
            
            if (xev.type == ClientMessage && (Atom)xev.xclient.data.l[0] == wm_delete) {
                running = false;
                window->is_closing = true;
            }
        }
        
        fall_counter++;
        if (fall_counter >= fall_speed) {
            fall_counter = 0;
            
            if (!check_collision(0, 1, current.shape)) {
                current.y++;
            } else {
                lock_tetromino();
                clear_lines();
                create_tetromino();
                
                if (check_collision(0, 0, current.shape)) {
                    game_over = true;
                    printf("Game Over! Score: %d\n", score);
                }
            }
        }
        
        arch_graphics_clear_screen(window, 0.1f, 0.1f, 0.15f, 1.0f);
        draw_game(window);
        arch_graphics_render(window);
        
        usleep(16000);
    }
    
    if(!game_over) {
    	printf("Final Score: %d\n", score);
    }

    arch_multimedia_library_destroy_window(window);
    return 0;
}
