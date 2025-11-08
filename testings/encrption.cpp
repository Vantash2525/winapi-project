#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static HWND hBtn;

    switch (msg) {
        case WM_CREATE: {
            hBtn = CreateWindowA("Button", "Click Me",
                                 WS_VISIBLE | WS_CHILD,
                                 100, 100, 100, 40,
                                 hwnd, (HMENU)1,
                                 ((LPCREATESTRUCT)lParam)->hInstance, NULL);
            return 0;
        }

        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                MessageBoxA(hwnd, "Button clicked!", "Overlay", MB_OK);
            }
            return 0;

        case WM_NCHITTEST: {
            // Convert to client space
            POINT pt = { GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            ScreenToClient(hwnd, &pt);

            // Get the button rect in client space
            RECT rcBtn;
            GetWindowRect(hBtn, &rcBtn);
            ScreenToClient(hwnd, (LPPOINT)&rcBtn.left);
            ScreenToClient(hwnd, (LPPOINT)&rcBtn.right);

            if (PtInRect(&rcBtn, pt)) {
                return HTCLIENT; // Allow button clicks
            }

            return HTTRANSPARENT; // Pass other clicks through
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {
    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "ClickThroughWindow";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0)); // Black becomes transparent

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        WS_EX_LAYERED | WS_EX_TOPMOST,
        "ClickThroughWindow",
        "Transparent Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        300, 200, 500, 400,
        NULL, NULL,
        hInstance, NULL
    );

    // Make black (0,0,0) fully transparent
    SetLayeredWindowAttributes(hwnd, RGB(0, 0, 0), 0, LWA_COLORKEY);

    MSG msg;
    while (GetMessageA(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}
