#include <stdio.h>
#include "level.h"

// Load a level from a file
void load_level(Level* level, const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0 || !file) {
        printf("Failed to load level: %s\n", filename);
        return;
    }

    // Read map dimensions
    fscanf_s(file, "%d %d", &level->width, &level->height, sizeof(int), sizeof(int));

    // Read map grid
    for (int y = 0; y < level->height; y++) {
        for (int x = 0; x < level->width; x++) {
            fscanf_s(file, "%hhu", &level->grid[y][x], sizeof(uint8_t));
        }
    }

    fclose(file);
}

// Check if a position is inside a wall
int is_wall(const Level* level, float x, float y) {
    int map_x = (int)(x); // Convert to map grid coordinates
    int map_y = (int)(y);

    // Check bounds and map cell
    if (map_x < 0 || map_x >= level->width || map_y < 0 || map_y >= level->height) {
        return 1; // Out of bounds is treated as a wall
    }
    return level->grid[map_y][map_x]; // Return 1 if it's a wall, 0 otherwise
}