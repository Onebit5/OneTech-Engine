#include <windows.h>
#include "graphics.h"
#include "utils.h"

// Clear the screen buffer
void clear_screen(uint8_t* buffer) {
    memset(buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT);
}

// Plot a pixel in the screen buffer (optimized with inline assembly)
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

    // Walls: Shades of red
    for (int i = 1; i < 32; i++) {
        palette[i] = RGB(i * 8, 0, 0); // Dark to bright red
    }

    // Floor: Shade of browns
    for (int i = 32; i < 64; i++) {
        int intensity = (i - 32) * 8;
        palette[i] = RGB(intensity, intensity / 2, 0); // Dark to light brown
    }

    // Ceiling: Shades of blue
    for (int i = 64; i < 96; i++) {
        int intensity = (i - 64) * 8;
        palette[i] = RGB(0, 0, intensity); // Dark to light blue
    }
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

    // Draw the buffer to the window
    SetDIBitsToDevice(
        hdc,
        0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, // Destination rectangle
        0, 0, 0, SCREEN_HEIGHT, // Source rectangle
        buffer,
        (BITMAPINFO*)&bmi,
        DIB_PAL_COLORS
    );
}