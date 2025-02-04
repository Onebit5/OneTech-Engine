#include <windows.h>
#include "input.h"
#include "level.h"

#define MOVE_STEP .1f
#define ROTATE_STEP .05f

void handle_input(Player* player, const Level* level) {
    // Movement input
    if (GetAsyncKeyState(VK_UP) & 0x8000) { // Move forward
        float new_x = player->x + MOVE_STEP * sin(player->angle);
        float new_y = player->y + MOVE_STEP * cos(player->angle);
        if (!is_wall(level, new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (GetAsyncKeyState(VK_DOWN) & 0x8000) { // Move backward
        float new_x = player->x - MOVE_STEP * sin(player->angle);
        float new_y = player->y - MOVE_STEP * cos(player->angle);
        if (!is_wall(level, new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
        }
    }

    // Strafing input
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && !(GetAsyncKeyState('ALT') & 0x8000)) { // Strafe left
        float new_x = player->x - MOVE_STEP * cos(player->angle);
        float new_y = player->y + MOVE_STEP * sin(player->angle);
        if (!is_wall(level, new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
        }
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && !(GetAsyncKeyState('ALT') & 0x8000)) { // Strafe right
        float new_x = player->x + MOVE_STEP * cos(player->angle);
        float new_y = player->y - MOVE_STEP * sin(player->angle);
        if (!is_wall(level, new_x, new_y)) {
            player->x = new_x;
            player->y = new_y;
        }
    }

    // Rotation input
    if (GetAsyncKeyState(VK_LEFT) & 0x8000 && GetAsyncKeyState('ALT') & 0x8000) { // Rotate left
        player->angle -= ROTATE_STEP;
    }
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000 && GetAsyncKeyState('ALT') & 0x8000) { // Rotate right
        player->angle += ROTATE_STEP;
    }

    // Normalize angle to [0, 2π]
    if (player->angle < 0) player->angle += 2 * M_PI;
    if (player->angle > 2 * M_PI) player->angle -= 2 * M_PI;
}