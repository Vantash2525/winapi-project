#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CLOSE:
            if(MessageBoxW(hwnd,L"are you sure you want to close the window?", L"close window", MB_YESNO)==IDYES){
                DestroyWindow(hwnd);
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProcA(hwnd, msg, wParam, lParam);
    }

}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, int nCmdShow) {

    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "TransparentClass";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);   // No default background
    wc.style = CS_HREDRAW | CS_VREDRAW; // Redraw on resize

    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExA(
        0,                  // 🔹 Required for transparency
        "TransparentClass",
        "Transparent Window",
        WS_OVERLAPPEDWINDOW | WS_VISIBLE,          // 🔹 No border, no title
        100, 100, 800, 600,             // Position and size
        NULL, NULL,
        hInstance, NULL
    );

    if (!hwnd) {
        MessageBoxA(NULL, "Window creation failed", "Error", MB_OK);
        return 1;
    }
    ShowWindow(hwnd , nCmdShow);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
