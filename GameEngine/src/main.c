#include <windows.h>
#include <stdbool.h>  
#include <stdint.h>   
#include <math.h>
#include <stdio.h>
#include "graphics.h"
#include "input.h"
#include "level.h"
#include "raycaster.h"
#include "utils.h"

uint8_t screen_buffer[SCREEN_WIDTH * SCREEN_HEIGHT];
Player player = { 4.5f, 4.5f, (float)(M_PI / 2.0) };
Level level = { 0 };

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Allocate console for debugging
    AllocConsole();
    FILE* fp;
    freopen_s(&fp, "CONOUT$", "w", stdout); // Redirect stdout to the console
    freopen_s(&fp, "CONIN$", "r", stdin);  // Redirect stdin to the console
    SetConsoleTitle(L"OneTech Engine Console");

    // Console loaded successfully
    printf("Console opened successfully!\n");

    // Initialize colors
    initialize_palette();

    // Load level
    load_level(&level, "level.txt");

    // Register window class
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"RaycasterWindowClass";

    if (!RegisterClass(&wc)) {
        printf("Failed to register window class! Error: %d\n", GetLastError());
        return -1;
    }

    // Create window
    HWND hwnd = CreateWindow(
        L"RaycasterWindowClass",
        L"OneTech Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) {
        printf("Failed to create window! Error: %d\n", GetLastError());
        return -1;
    }

    ShowWindow(hwnd, nCmdShow);
    SetFocus(hwnd); // Ensure the window has focus
    printf("Window created successfully.\n");

    // Main loop
    MSG msg;
    while (1) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        clear_screen(screen_buffer);

        handle_input(&player, &level);
        cast_rays(screen_buffer, &level, &player);

        HDC hdc = GetDC(hwnd);
        render_buffer(hdc, screen_buffer);
        ReleaseDC(hwnd, hdc);
    }

    return 0;
}