#include <math.h>
#include "raycaster.h"
#include "graphics.h"
#include "utils.h"

// Cast rays and render levels
void cast_rays(uint8_t* buffer, const Level* level, const Player* player) {
    // Precompute constants for optimization
    float fov_half = FOV / 2.f;

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        // Calculate camera plane coordinates (-1 to 1)
        float camera_x = 2.f * x / SCREEN_WIDTH - 1.f;
        float ray_angle = player->angle + fov_half * camera_x;

        // Precompute ray direction vector
        float ray_dir_x = cos(ray_angle);
        float ray_dir_y = sin(ray_angle);

        // DDA variables
        int map_x = (int)player->x;
        int map_y = (int)player->y;
        float side_dist_x, side_dist_y;
        float delta_dist_x = fabs(1.f / ray_dir_x);
        float delta_dist_y = fabs(1.f / ray_dir_y);
        float perp_wall_dist;

        int step_x, step_y;
        int hit = 0; // Was there a wall hit?
        int side; // Was a NS or EW wall hit?

        // Step direction and initial side distance
        if (ray_dir_x < 0) {
            step_x = -1;
            side_dist_x = (player->x - map_x) * delta_dist_x;
        }
        else {
            step_x = 1;
            side_dist_x = (map_x + 1.f - player->x) * delta_dist_x;
        }
        if (ray_dir_y < 0) {
            step_y = -1;
            side_dist_y = (player->y - map_y) * delta_dist_y;
        }
        else {
            step_y = 1;
            side_dist_y = (map_y + 1.f - player->y) * delta_dist_y;
        }

        // Perform DDA
        while (!hit) {
            // Jump to next map square, either in x-direction or y-direction
            if (side_dist_x < side_dist_y) {
                side_dist_x += delta_dist_x;
                map_x += step_x;
                side = 0; // Horizontal wall
            }
            else {
                side_dist_y += delta_dist_y;
                map_y += step_y;
                side = 1; // Vertical wall
            }

            // Check if ray has hit a wall
            if (map_x >= 0 && map_x < level->width && map_y >= 0 && map_y < level->height) {
                if (is_wall(level, map_x, map_y)) {
                    hit = 1;
                }
                else if (is_door(level, map_x, map_y)) {
                    // Adjust distance based on door's open position
                    for (int d = 0; d < level->door_count; d++) {
                        Door* door = &level->doors[d];
                        if (map_x == door->x && map_y >= door->y && map_y < door->y + 2) {
                            perp_wall_dist += door->open_pos;
                            break;
                        }
                    }
                    hit = 1;
                }
            }
            else {
                hit = 1; // Out of bounds is treated as hitting a wall
            }
        }

        // Calculate perpendicular wall distance
        if (side == 0) {
            perp_wall_dist = (map_x - player->x + (1.f - step_x) / 2.f) / ray_dir_x;
        }
        else {
            perp_wall_dist = (map_y - player->y + (1.f - step_y) / 2.f) / ray_dir_y;
        }

        // Fisheye correction is inherently handled by using perpendicular distance

        // Calculate line height and drawing bounds
        int line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;

        // Clamp draw_start and draw_end to valid screen coordinates
        draw_start = max(0, draw_start);
        draw_end = min(SCREEN_HEIGHT - 1, draw_end);

        // Draw walls (blue)
        if (is_wall(level, map_x, map_y)) {
            for (int y = draw_start; y < draw_end; y++) {
                plot_pixel_asm(buffer, x, y, 1); // Use index 1 (blue)
            }
        }
        // Draw doors (red)
        else if (is_door(level, map_x, map_y)) {
            for (int y = draw_start; y < draw_end; y++) {
                plot_pixel_asm(buffer, x, y, 4); // Use index 4 (red)
            }
        }

        // Draw floor (gray)
        for (int y = draw_end; y < SCREEN_HEIGHT; y++) {
            plot_pixel_asm(buffer, x, y, 2); // Use index 2 (gray)
        }

        // Draw ceiling (light gray)
        for (int y = 0; y < draw_start; y++) {
            plot_pixel_asm(buffer, x, y, 3); // Use index 3 (light gray)
        }
    }
}