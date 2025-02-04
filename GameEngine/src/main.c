#include <windows.h>
#include "graphics.h"
#include "input.h"
#include "level.h"
#include "raycaster.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 200

uint8_t screen_buffer[SCREEN_WIDTH * SCREEN_HEIGHT];
Player player = { 4.5f, 4.5f, (float)(M_PI / 2.0) };
Level level;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Load level
    load_level(&level, "level.txt");

    // Create window
    WNDCLASS wc = { 0 };
    wc.lpfnWndProc = DefWindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"RaycasterWindowClass";
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(
        L"RaycasterWindowClass",
        L"OneTech Engine",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2,
        NULL, NULL, hInstance, NULL
    );
    ShowWindow(hwnd, nCmdShow);

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