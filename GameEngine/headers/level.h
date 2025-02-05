#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>
#include <windows.h>
#include "utils.h"

#define MAX_MAP_WIDTH 64
#define MAX_MAP_HEIGHT 64

typedef struct {
	int width;
	int height;
	uint8_t grid[MAX_MAP_HEIGHT][MAX_MAP_WIDTH]; // Map grid (0 = empty, 1 = wall)
} Level;

// Load a level from a file
void load_level(Level* level, const char* filename);

// Save a level to a file
void save_level(const Level* level, const char* filename);

// Check if a position is inside a wall
int is_wall(const Level* level, float x, float y);

#endif