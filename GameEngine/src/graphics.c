#include <windows.h>
#include "graphics.h"

// Clear the screen buffer
void clear_screen(uint8_t* buffer) {
    memset(buffer, 0, SCREEN_WIDTH * SCREEN_HEIGHT);
}

// Plot a pixel in the screen buffer (optimized with inline assembly)
void plot_pixel_asm(uint8_t* buffer, int x, int y, uint8_t color) {
    if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {
        __asm {
            mov edi, buffer       // Load buffer address
            mov eax, y            // Load y
            imul eax, SCREEN_WIDTH // Multiply y by screen width
            add eax, x            // Add x to get the offset
            movzx ebx, color      // Load color
            mov[edi + eax], bl   // Write pixel to buffer
        }
    }
}

// Render the screen buffer to the window
void render_buffer(HDC hdc, uint8_t* buffer) {
    // Define a 256-color palette (grayscale for simplicity)
    static COLORREF palette[256];
    for (int i = 0; i < 256; i++) {
        palette[i] = RGB(i, i, i); // Grayscale
    }

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
        0, 0, 0, SCREEN_HEIGHT,           // Source rectangle
        buffer,
        (BITMAPINFO*)&bmi,
        DIB_PAL_COLORS
    );
}