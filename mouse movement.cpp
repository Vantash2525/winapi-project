#include <windows.h>
#include <stdio.h>
#include <windowsx.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:{
            CreateWindowA("Button", "Click Me",
                          WS_VISIBLE | WS_CHILD,
                          100, 100, 120, 40,
                          hwnd, (HMENU)1,
                          ((LPCREATESTRUCTA)lParam)->hInstance, NULL);

            CreateWindowA("Edit", "text",
                          WS_CHILD | WS_VISIBLE | WS_BORDER,
                          20, 20, 200, 25,
                          hwnd, (HMENU)2,
                          ((LPCREATESTRUCTA)lParam)->hInstance, NULL);
            return 0;
            }
        case WM_CLOSE:
            if (MessageBoxW(hwnd, L"Are you sure you want to close the window?", L"Close Window", MB_YESNO) == IDYES) {
                DestroyWindow(hwnd);
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_MOUSEMOVE: {
            HWND hedit = GetDlgItem(hwnd, 2);
            if (!hedit) return 0;

            int x = GET_X_LPARAM(lParam);
            int y = GET_Y_LPARAM(lParam);
            char buffer[100];
            sprintf(buffer, "Mouse at X:%d Y:%d", x, y);
            SetWindowTextA(hedit, buffer);
            return 0;
        }

        case WM_COMMAND:{
            HWND hbtn = GetDlgItem(hwnd, 1);
            if (LOWORD(wParam) == 1) {
                MessageBoxA(hbtn, "Button clicked!", "Notification", MB_OK);
                return 0;
            }
            break;
        }
        default:
            return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "TransparentClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(100, 120, 240));

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,
        "TransparentClass",
        "Initial Title",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        100, 100, 800, 600,
        NULL, NULL,
        hInstance, NULL
    );

    if (!hwnd) {
        MessageBoxA(NULL, "Window creation failed", "Error", MB_OK);
        return 1;
    }

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}
