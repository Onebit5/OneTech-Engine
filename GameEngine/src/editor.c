#include <windows.h>
#include <stdio.h>
#include "editor.h"
#include "level.h"
#include "graphics.h"
#include "utils.h"

static int editor_mode = 0;

int is_editor_mode() {
	return editor_mode;
}

void toggle_editor_mode() {
	editor_mode = !editor_mode;
	printf("Editor mode: %s\n", editor_mode ? "ON" : "OFF");
}

void render_grid(uint8_t* buffer, const Level* level) {
    printf("Rendering grid with dimensions: %dx%d\n", level->width, level->height);

    for (int y = 0; y < level->height; y++) {
        for (int x = 0; x < level->width; x++) {
            uint8_t color = level->grid[y][x] ? 255 : 128; // White for walls, gray for empty spaces
            for (int py = 0; py < 10; py++) { // Scale each cell to 10x10 pixels
                for (int px = 0; px < 10; px++) {
                    plot_pixel_asm(buffer, x * 10 + px, y * 10 + py, color);
                }
            }
        }
    }
}