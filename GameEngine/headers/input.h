#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "level.h"
#include "raycaster.h"
#include "utils.h"

// Function to handle player input, taking a pointer to the player and level as parameters
void handle_input(Player* player, const Level* level);

// Function to handle mouse input, taking a pointer to the level as a parameter
void handle_mouse_input(Level* level);

// Function to handle editor input, taking a pointer to the level as a parameter
void handle_editor_input(Level* level);

#endif