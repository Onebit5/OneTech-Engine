#pragma once

#ifndef INPUT_H
#define INPUT_H

#include "level.h"
#include "raycaster.h"
#include "utils.h"

// Handle keyboard
void handle_input(Player* player, const Level* level);
void handle_mouse_input(Level* level);
void handle_editor_input(Level* level);

#endif