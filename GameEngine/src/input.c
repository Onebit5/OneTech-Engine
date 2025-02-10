#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include "input.h"
#include "level.h"
#include "utils.h"

// Handles player input for movement and rotation
void handle_input(Player* player, const Level* level) {
    // Movement input
    if (GetAsyncKeyState(VK_UP) & 0x8000) { // Move forward
        float new_x = player->x + MOVE_STEP * cos(player->angle);
        float new_y = player->y + MOVE_STEP * sin(player->angle);
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
        float new_x = player->x - MOVE_STEP * cos(player->angle);
        float new_y = player->y - MOVE_STEP * sin(player->angle);
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
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Rotate left
        player->angle -= ROTATE_STEP;
        printf("Rotated left to angle %.2f\n", player->angle);
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
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Rotate right
        player->angle += ROTATE_STEP;
        printf("Rotated right to angle %.2f\n", player->angle);
    }

    

    // Normalize angle to [0, 2π]
    if (player->angle < 0) player->angle += 2 * M_PI;
    if (player->angle > 2 * M_PI) player->angle -= 2 * M_PI;
}