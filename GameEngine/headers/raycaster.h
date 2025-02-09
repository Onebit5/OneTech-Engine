#pragma once

#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <stdint.h>
#include "graphics.h"
#include "level.h"
#include "utils.h"

// Define a structure to represent the player
typedef struct {
    float x, y;  // Position of the player in 2D space
    float angle; // Viewing angle of the player
} Player;

// Function to cast rays and render walls based on the player's position and level
void cast_rays(uint8_t* buffer, const Level* level, const Player* player);

#endif