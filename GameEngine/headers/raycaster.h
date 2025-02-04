#pragma once

#ifndef RAYCASTER_H
#define RAYCASTER_H

#include <stdint.h>
#include "graphics.h"
#include "level.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

typedef struct {
    float x, y;  // Position
    float angle; // Viewing angle
} Player;

// Cast rays and render walls
void cast_rays(uint8_t* buffer, const Level* level, const Player* player);

#endif