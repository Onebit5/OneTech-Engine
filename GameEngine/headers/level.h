#pragma once

#ifndef LEVEL_H
#define LEVEL_H

#include <stdint.h>
#include <windows.h>
#include "utils.h"

// Define a structure to represent a door in the game
typedef struct {
	int x; // X-coordinate of the door's base
	int y; // Y-coordinate of the door's base
	float open_pos; // Current open position (0 = closed, -2 = fully open)
} Door;

// Define a structure to represent a game level
typedef struct {
	int width; // Width of the level
	int height; // Height of the level
	uint8_t** grid; // Map grid represented as a 2D array
	Door* doors; // Pointer to an array of doors in the level
	int door_count; // Number of doors in the level
} Level;

// Function to load a level from a file
int load_level(const char* filename, Level* level);

// Function to free allocated memory for a level
void free_level(Level* level);

// Function to check if a given position is inside a wall
int is_wall(const Level* level, int x, int y);

// Function to check if a given position is a door
int is_door(const Level* level, int x, int y);

#endif