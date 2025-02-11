#include <stdio.h>
#include "level.h"
#include "utils.h"

// Load a level from a text file
int load_level(const char* filename, Level* level) {
    printf("Attempting to open file: %s\n", filename);
    FILE* file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Could not open file '%s'.\n", filename);
        return -1;
    }
    printf("File opened successfully.\n");

    // Read dimensions
    if (fscanf_s(file, "%d %d", &level->width, &level->height) != 2) {
        fprintf(stderr, "Error: Failed to read dimensions from file.\n");
        fclose(file);
        return -1;
    }

    if (level->width <= 0 || level->height <= 0) {
        fprintf(stderr, "Error: Invalid dimensions (%d x %d). Dimensions must be positive.\n", level->width, level->height);
        fclose(file);
        return -1;
    }

    printf("Read dimensions: %dx%d\n", level->width, level->height);

    // Allocate memory for the grid
    level->grid = malloc(level->height * sizeof(uint8_t*));
    if (!level->grid) {
        fprintf(stderr, "Error: Memory allocation failed for grid rows.\n");
        fclose(file);
        return -1;
    }

    for (int y = 0; y < level->height; y++) {
        level->grid[y] = malloc(level->width * sizeof(uint8_t));
        if (!level->grid[y]) {
            fprintf(stderr, "Error: Memory allocation failed for grid row %d.\n", y);
            // Free previously allocated rows
            for (int i = 0; i < y; i++) {
                free(level->grid[i]);
            }
            free(level->grid);
            fclose(file);
            return -1;
        }
    }

    // Read grid data
    for (int y = 0; y < level->height; y++) {
        for (int x = 0; x < level->width; x++) {
            int temp;
            if (fscanf_s(file, "%d", &temp) != 1) {
                fprintf(stderr, "Error: Failed to read grid data at (%d, %d).\n", x, y);
                // Cleanup memory
                for (int i = 0; i < level->height; i++) {
                    free(level->grid[i]);
                }
                free(level->grid);
                fclose(file);
                return -1;
            }

            // Validate cell value
            if (temp < 0 || temp > 2) {
                fprintf(stderr, "Error: Invalid cell value %d at (%d, %d). Values must be 0, 1, or 2.\n", temp, x, y);
                // Cleanup memory
                for (int i = 0; i < level->height; i++) {
                    free(level->grid[i]);
                }
                free(level->grid);
                fclose(file);
                return -1;
            }

            level->grid[y][x] = (uint8_t)temp;

            // Track doors
            if (temp == 2) {
                level->door_count++; // Count total doors
            }

            printf("Grid[%d][%d] = %d\n", y, x, level->grid[y][x]);
        }
    }

    // Allocate doors array
    level->doors = malloc(level->door_count * sizeof(Door));
    if (!level->doors) { /* Handle error */ }

    // Populate door positions
    int door_idx = 0;
    for (int y = 0; y < level->height; y++) {
        for (int x = 0; x < level->width; x++) {
            if (level->grid[y][x] == 2) {
                level->doors[door_idx].x = x;
                level->doors[door_idx].y = y;
                level->doors[door_idx].open_pos = -2.f; // Closed by default
                door_idx++;
            }
        }
    }

    fclose(file);
    printf("Level loaded successfully.\n");
    return 0; // Success
}

// Function to free the level's memory
void free_level(Level* level) {
    if (level->grid) {
        for (int y = 0; y < level->height; y++) {
            free(level->grid[y]);
        }
        free(level->grid);
    }
    if (level->doors) {
        free(level->doors); // Free door array
    }
    level->grid = NULL;
    level->doors = NULL;
    level->width = level->height = level->door_count = 0;
}

// Check if a position is inside a wall
int is_wall(const Level* level, int x, int y) {
    if (x < 0 || x >= level->width || y < 0 || y >= level->height) {
        return 1; // Out of bounds is treated as a wall
    }
    return level->grid[y][x] == 1; // Return 1 if it's a wall
}

int is_door(const Level* level, int x, int y) {
    if (x < 0 || x >= level->width || y < 0 || y >= level->height) {
        return 0; // Out of bounds is not a door
    }
    return level->grid[y][x] == 2; // Return 1 if it's a door
}