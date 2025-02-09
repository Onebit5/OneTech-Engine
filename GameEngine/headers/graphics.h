#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <windows.h>
#include "utils.h"

// Function to clear the screen buffer
void clear_screen(uint8_t* buffer);

// Function to plot a pixel at (x, y) with a specified color using assembly
void plot_pixel_asm(uint8_t* buffer, int x, int y, uint8_t color);

// Function to render the buffer to the device context
void render_buffer(HDC hdc, uint8_t* buffer);

// Function to initialize the color palette
void initialize_palette();

#endif