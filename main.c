#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "pixelWindowUpdater.h"
#include "timer.h"

LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

    switch (msg)
    {
    case WM_CLOSE:
            //m_pWnd->close();
            DestroyWindow(hwnd);
            break;
    case WM_DESTROY:
            PostQuitMessage(0);
            break;
    default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    //Step 1: Registering the Window Class
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = wndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "windowClass";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc))
    {
            MessageBox(NULL, "Window Registration Failed!", "Error!",
                    MB_ICONEXCLAMATION | MB_OK);
            return 0;
    }

    // Step 2: Creating the Window
    hwnd = CreateWindowEx(
            0,
            "windowClass",
            "PixelWindow",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, SCREEN_WIDTH, SCREEN_HEIGHT,
            NULL, NULL, hInstance, NULL);

    if (hwnd == NULL)
    {
            MessageBox(NULL, "Window Creation Failed!", "Error!",
                    MB_ICONEXCLAMATION | MB_OK);
            return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

//#pragma region Centre Screen
    RECT rc;
    GetWindowRect(hwnd, &rc);
    int xPos = (GetSystemMetrics(SM_CXSCREEN) - rc.right) / 2;
    int yPos = (GetSystemMetrics(SM_CYSCREEN) - rc.bottom) / 2;
    SetWindowPos(hwnd, 0, xPos, yPos, 0, 0, SWP_NOZORDER | SWP_NOSIZE);  // Centre screen.
//#pragma endregion

    PixelWindow wnd;
    pxwnd_init(&wnd, hwnd);

    Timer timer = timer_create();
    double lasttime = 0.0;
    
    // Step 3: The Message Loop
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
        
        double total = timer_get_total(&timer);
        wnd_update(total - lasttime, total, &wnd);
        lasttime = total;
    }

    return Msg.wParam;
}
