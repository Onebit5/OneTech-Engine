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

        int grid_x = (int)new_x;
        int grid_y = (int)new_y;

        // Check both walls and doors
        if (!is_wall(level, grid_x, grid_y) && !is_door(level, grid_x, grid_y)) {
            player->x = new_x;
            player->y = new_y;
            printf("Moved forward to (%.2f, %.2f)\n", player->x, player->y);
        }
        else {
            printf("Blocked by a wall or door\n");
        }
    }

    if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Move backward
        float new_x = player->x - MOVE_STEP * cos(player->angle);
        float new_y = player->y - MOVE_STEP * sin(player->angle);

        int grid_x = (int)new_x;
        int grid_y = (int)new_y;

        // Check both walls and doors
        if (!is_wall(level, grid_x, grid_y) && !is_door(level, grid_x, grid_y)) {
            player->x = new_x;
            player->y = new_y;
            printf("Moved backward to (%.2f, %.2f)\n", player->x, player->y);
        }
        else {
            printf("Blocked by a wall or door\n");
        }
    }

    if (GetAsyncKeyState(VK_MENU) & 0x8000 && (GetAsyncKeyState(VK_LEFT) & 0x8000)) { // Strafe left
        float new_x = player->x + MOVE_STEP * sin(player->angle);
        float new_y = player->y - MOVE_STEP * cos(player->angle); // Negate Y

        int grid_x = (int)new_x;
        int grid_y = (int)new_y;

        // Check both walls and doors
        if (!is_wall(level, grid_x, grid_y) && !is_door(level, grid_x, grid_y)) {
            player->x = new_x;
            player->y = new_y;
            printf("Strafed left to (%.2f, %.2f)\n", player->x, player->y);
        }
        else {
            printf("Blocked by a wall or door\n");
        }
    }
    else if (GetAsyncKeyState(VK_LEFT) & 0x8000) { // Rotate left
        player->angle -= ROTATE_STEP;
        printf("Rotated left to angle %.2f\n", player->angle);
    }

    if (GetAsyncKeyState(VK_MENU) & 0x8000 && (GetAsyncKeyState(VK_RIGHT) & 0x8000)) { // Strafe right
        float new_x = player->x - MOVE_STEP * sin(player->angle);
        float new_y = player->y + MOVE_STEP * cos(player->angle); // Negate Y

        int grid_x = (int)new_x;
        int grid_y = (int)new_y;

        // Check both walls and doors
        if (!is_wall(level, grid_x, grid_y) && !is_door(level, grid_x, grid_y)) {
            player->x = new_x;
            player->y = new_y;
            printf("Strafed right to (%.2f, %.2f)\n", player->x, player->y);
        }
        else {
            printf("Blocked by a wall or door\n");
        }
    }
    else if (GetAsyncKeyState(VK_RIGHT) & 0x8000) { // Rotate right
        player->angle += ROTATE_STEP;
        printf("Rotated right to angle %.2f\n", player->angle);
    }

    // Open doors with spacebar
    if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
        float tolerance = 0.5f; // Allow some leeway for player alignment

        for (int d = 0; d < level->door_count; d++) {
            Door* door = &level->doors[d];
            printf("Player position: (%.2f, %.2f)\n", player->x, player->y);
            printf("Checking door at (%d, %d)\n", door->x, door->y);

            if ((fabs(player->x - door->x) < tolerance && fabs(player->y - door->y) <= 1 + tolerance) ||
                (fabs(player->y - door->y) < tolerance && fabs(player->x - door->x) <= 1 + tolerance)) {
                printf("Player is near the door!\n");
                if (door->open_pos > -2.f) { // Only open if not fully open
                    door->open_pos = fmax(door->open_pos - 0.1f, -2.f); // Clamp to -2.f
                    printf("Door open_pos updated to %.2f\n", door->open_pos);
                }
            }
        }
    }

    // Normalize angle to [0, 2π)
    if (player->angle < 0) player->angle += 2 * M_PI;
    if (player->angle > 2 * M_PI) player->angle -= 2 * M_PI;
}