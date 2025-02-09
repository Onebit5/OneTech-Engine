#pragma once

#ifndef EDITOR_H
#define EDITOR_H

#include "level.h"
#include "graphics.h"
#include "utils.h"

// Function to check if the editor mode is active
int is_editor_mode();

// Function to toggle the editor mode on or off
void toggle_editor_mode();

// Function to render the grid on the screen based on the level data
void render_grid(uint8_t* buffer, const Level* level);

#endif 
