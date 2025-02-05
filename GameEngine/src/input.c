#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include "input.h"
#include "level.h"
#include "editor.h"
#include "utils.h"

#define MOVE_STEP .01f
#define ROTATE_STEP .001f

void handle_input(Player* player, const Level* level) {
    // Movement input
    if (GetAsyncKeyState(VK_UP) & 0x8000) { // Move forward
        float new_x = player->x - MOVE_STEP * cos(player->angle);
        float new_y = player->y + MOVE_STEP * sin(player->angle); // Negate Y
        if (!is_wall(level, new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
            printf("Moved forward to (%.2f, %.2f)\n", player->x, player->y);
        }
        else {
            printf("Blocked by a wall\n");
        }
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Move backward
        float new_x = player->x + MOVE_STEP * cos(player->angle);
        float new_y = player->y - MOVE_STEP * sin(player->angle); // Negate Y
        if (!is_wall(level, new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
            printf("Moved backward to (%.2f, %.2f)\n", player->x, player->y);
        }
        else {
            printf("Blocked by a wall\n");
        }
    }

    if (GetAsyncKeyState(VK_MENU) & 0x8000 && (GetAsyncKeyState(VK_LEFT) & 0x8000)) { // Strafe left
        float new_x = player->x + MOVE_STEP * sin(player->angle);
        float new_y = player->y - MOVE_STEP * cos(player->angle); // Negate Y
        if (!is_wall(level, new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
            printf("Strafed left to (%.2f, %.2f)\n", player->x, player->y);
        }
        else {
            printf("Blocked by a wall\n");
        }
    }

    if (GetAsyncKeyState(VK_MENU) & 0x8000 && (GetAsyncKeyState(VK_RIGHT) & 0x8000)) { // Strafe right
        float new_x = player->x - MOVE_STEP * sin(player->angle);
        float new_y = player->y + MOVE_STEP * cos(player->angle); // Negate Y
        if (!is_wall(level, new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
            printf("Strafed right to (%.2f, %.2f)\n", player->x, player->y);
        }
        else {
            printf("Blocked by a wall\n");
        }
    }

    // Rotation input
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Rotate left
        player->angle -= ROTATE_STEP;
        printf("Rotated left to angle %.2f\n", player->angle);
    }

    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Rotate right
        player->angle += ROTATE_STEP;
        printf("Rotated right to angle %.2f\n", player->angle);
    }

    // Normalize angle to [0, 2π]
    if (player->angle < 0) player->angle += 2 * M_PI;
    if (player->angle > 2 * M_PI) player->angle -= 2 * M_PI;

    // Change to editor mode
    if (GetAsyncKeyState('E') & 0x8000) {
        toggle_editor_mode();
    }
}

void handle_editor_input(Level* level) {
    // Save or load the level
    if (GetAsyncKeyState('S') & 0x8000) {
        save_level(&level, "level.txt");
    }
    if (GetAsyncKeyState('L') & 0x8000) {
        load_level(&level, "level.txt");
    }
    // Change to game mode
    if (GetAsyncKeyState('G') & 0x8000) {
        toggle_editor_mode();
    }
}

void handle_mouse_input(Level* level) {
    POINT mouse_pos;
    GetCursorPos(&mouse_pos);
    ScreenToClient(GetForegroundWindow(), &mouse_pos);

    int grid_x = mouse_pos.x / 10; // Convert pixel coordinates to grid coordinates
    int grid_y = mouse_pos.y / 10;

    if (grid_x >= 0 && grid_x < level->width && grid_y >= 0 && grid_y < level->height) {
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // Left-click to add a wall
            level->grid[grid_y][grid_x] = 1;
        }
        if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) { // Right-click to add a wall
            level->grid[grid_y][grid_x] = 0;
        }
    }
}