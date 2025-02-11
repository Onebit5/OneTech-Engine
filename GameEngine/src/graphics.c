#include <windows.h>
#include "graphics.h"
#include "utils.h"

// Clear the screen buffer
void clear_screen(uint8_t* buffer) {
    if (!buffer) {
        printf("Error: screen_buffer is null.\n");
        return;
    }

    memset(buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT); // Set all bytes in the buffer to zero
}

// Plot a pixel in the screen buffer
void plot_pixel_asm(uint8_t* buffer, int x, int y, uint8_t color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        __asm {
            mov edi, buffer // Load buffer address
            mov eax, y // Load y
            imul eax, SCREEN_WIDTH // Multiply y by screen width
            add eax, x // Add x to get the offset
            movzx ebx, color // Load color
            mov[edi + eax], bl // Write pixel to buffer
        }
    }
}

// Define a 256-color palette 
static COLORREF palette[256];

void initialize_palette() {
    // Black background
    palette[0] = RGB(0, 0, 0);

    // Walls: blue
    palette[1] = RGB(0, 0, 255);

    // Floor: gray
    palette[2] = RGB(128, 128, 128); 

    // Ceiling: light gray
    palette[3] = RGB(192, 192, 192); 

    // Doors: red
    palette[4] = RGB(255, 0, 0);
}

// Render the screen buffer to the window
void render_buffer(HDC hdc, uint8_t* buffer) {
    // Create a bitmap to hold the screen buffer
    BITMAPINFO bmi = { 0 };
    bmi.bmiHeader.biSize = sizeof(bmi.bmiHeader);
    bmi.bmiHeader.biWidth = SCREEN_WIDTH;
    bmi.bmiHeader.biHeight = -SCREEN_HEIGHT; // Negative height for top-down DIB
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 8;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biClrUsed = 256;

    // Copy the palette into the BITMAPINFO structure
    for (int i = 0; i < 256; i++) {
        bmi.bmiColors[i].rgbRed = GetRValue(palette[i]);
        bmi.bmiColors[i].rgbGreen = GetGValue(palette[i]);
        bmi.bmiColors[i].rgbBlue = GetBValue(palette[i]);
        bmi.bmiColors[i].rgbReserved = 0;
    }

    // Draw the buffer to the window
    SetDIBitsToDevice(
        hdc,
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, // Destination rectangle
        0, 0, 0, SCREEN_HEIGHT, // Source rectangle
        buffer,
        &bmi,
        DIB_RGB_COLORS // Use RGB colors instead of palette indices
    );
}