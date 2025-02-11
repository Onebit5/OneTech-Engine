#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "level.h"
#include "raycaster.h"
#include "utils.h"

// Function to handle player input, taking a pointer to the player and level as parameters
void handle_input(Player* player, const Level* level);

#endif