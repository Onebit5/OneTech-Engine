#include <windows.h> 
#include <stdio.h>   
#include "editor.h"  
#include "level.h"   
#include "graphics.h"
#include "utils.h"   

static int editor_mode = 0; // Static variable to track the editor mode state

// Function to check if the editor mode is active
int is_editor_mode() {
    return editor_mode; // Return the current state of editor_mode
}

// Function to toggle the editor mode on or off
void toggle_editor_mode() {
    editor_mode = !editor_mode; // Toggle the editor_mode variable
    printf("Editor mode: %s\n", editor_mode ? "ON" : "OFF"); // Print the current state of editor mode
}

// Function to render a grid based on the level data
void render_grid(uint8_t* buffer, const Level* level) {
    printf("Rendering grid with dimensions: %dx%d\n", level->width, level->height); // Log the dimensions of the grid

    // Loop through each row of the grid
    for (int y = 0; y < level->height; y++) {
        // Loop through each column of the grid
        for (int x = 0; x < level->width; x++) {
            uint8_t color = level->grid[y][x] ? 255 : 128; // Determine color: white for walls, gray for empty spaces
            // Loop to scale each cell to 10x10 pixels
            for (int py = 0; py < 10; py++) {
                for (int px = 0; px < 10; px++) {
                    plot_pixel_asm(buffer, x * 10 + px, y * 10 + py, color); // Plot the pixel in the buffer
                }
            }
        }
    }
}
