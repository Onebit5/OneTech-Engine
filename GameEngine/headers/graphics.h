#pragma once

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <windows.h>

// Screen dimensions
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

#define M_PI 3.14159265359

void clear_screen(uint8_t* buffer);
void plot_pixel_asm(uint8_t* buffer, int x, int y, uint8_t color);
void render_buffer(HDC hdc, uint8_t* buffer);

#endif