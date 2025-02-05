#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <windows.h>
#include "utils.h"

void clear_screen(uint8_t* buffer);
void plot_pixel_asm(uint8_t* buffer, int x, int y, uint8_t color);
void render_buffer(HDC hdc, uint8_t* buffer);
void initialize_palette();

#endif