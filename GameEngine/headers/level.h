#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>
#include <windows.h>
#include "utils.h"

// Define a structure to represent a game level
typedef struct {
	int width; // Width of the level
	int height; // Height of the level
	uint8_t grid[MAX_MAP_HEIGHT][MAX_MAP_WIDTH]; // Map grid (0 = empty, 1 = wall)
} Level;

// Load a level from a file
void load_level(Level* level, const char* filename);

// Save a level to a file
void save_level(const Level* level, const char* filename);

// Check if a position is inside a wall
int is_wall(const Level* level, float x, float y);

#endif