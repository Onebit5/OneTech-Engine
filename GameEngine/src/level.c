#include <stdio.h>
#include "level.h"
#include "utils.h"

// Load a level from a text file
void load_level(Level* level, const char* filename) {
    FILE* file;
    if (fopen_s(&file, filename, "r") != 0 || !file) {
        printf("Failed to load level: %s\n", filename);
        return;
    }

    // Read map dimensions
    if (fscanf_s(file, "%d %d", &level->width, &level->height) != 2) {
        printf("Error reading dimensions from file.\n");
        fclose(file);
        return;
    }

    // Allocate memory for the grid
    level->grid = malloc(level->height * sizeof(uint8_t*));
    if (!level->grid) {
        printf("Memory allocation failed for grid.\n");
        fclose(file);
        return;
    }
    for (int y = 0; y < level->height; y++) {
        level->grid[y] = malloc(level->width * sizeof(uint8_t));
        if (!level->grid[y]) {
            printf("Memory allocation failed for grid row %d.\n", y);
            for (int i = 0; i < y; i++) {
                free(level->grid[i]);
            }
            free(level->grid);
            fclose(file);
            return;
        }
    }

    // Read map grid
    for (int y = 0; y < level->height; y++) {
        for (int x = 0; x < level->width; x++) {
            if (fscanf_s(file, "%hhu", &level->grid[y][x]) != 1) {
                printf("Error reading grid data at (%d, %d).\n", x, y);
                for (int i = 0; i < level->height; i++) {
                    free(level->grid[i]);
                }
                free(level->grid);
                fclose(file);
                return;
            }
        }
    }

    fclose(file);
    printf("Level loaded successfully from text file: %s\n", filename);
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