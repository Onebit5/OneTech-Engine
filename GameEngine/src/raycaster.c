#include <math.h>
#include "raycaster.h"
#include "graphics.h"
#include "utils.h"

// Cast rays and render walls
void cast_rays(uint8_t* buffer, const Level* level, const Player* player) {
    // Validate input parameters
    if (!buffer || !level || !level->grid || !player) {
        printf("Error: Invalid input parameters.\n");
        return;
    }

    for (int x = 0; x < SCREEN_WIDTH; x++) {
        float camera_x = 2.0f * x / SCREEN_WIDTH - 1.0f;
        float ray_angle = player->angle + FOV * camera_x;
        float ray_dir_x = cos(ray_angle);
        float ray_dir_y = sin(ray_angle);
        float distance_to_wall = 0.0f;
        int hit_wall = 0;
        float eye_x = player->x;
        float eye_y = player->y;

        while (!hit_wall && distance_to_wall < 16.0f) {
            distance_to_wall += 0.1f;
            float test_x_f = eye_x + ray_dir_x * distance_to_wall;
            float test_y_f = eye_y + ray_dir_y * distance_to_wall;
            int test_x = (int)test_x_f;
            int test_y = (int)test_y_f;

            // Check bounds before accessing level->grid
            if (test_x >= 0 && test_x < level->width && test_y >= 0 && test_y < level->height) {
                if (is_wall(level, test_x, test_y)) {
                    hit_wall = 1;
                }
            }
            else {
                hit_wall = 1; // Out of bounds is treated as hitting a wall
                distance_to_wall = 16.0f;
            }
        }

        // Calculate line height and drawing bounds
        int line_height = (int)(SCREEN_HEIGHT / distance_to_wall);
        int draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
        int draw_end = line_height / 2 + SCREEN_HEIGHT / 2;

        // Clamp draw_start and draw_end to valid screen coordinates
        draw_start = max(0, draw_start);
        draw_end = min(SCREEN_HEIGHT - 1, draw_end);

        // Draw walls (blue)
        for (int y = draw_start; y < draw_end; y++) {
            plot_pixel_asm(buffer, x, y, 1); // Use index 1 (blue)
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