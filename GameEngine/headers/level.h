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
	uint8_t** grid; // Map grid (0 = empty, 1 = wall)
} Level;

void load_level_text(Level* level, const char* filename);

void initialize_level(Level* level, int width, int height);

void save_level_binary(const Level* level, const char* filename);

void free_level(Level* level);

void load_level_binary(Level* level, const char* filename);

// Check if a position is inside a wall
int is_wall(const Level* level, float x, float y);

#endif