#include <iostream>
#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT umsg, WPARAM wparam , LPARAM lparam){
    switch(umsg){
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_PAINT:{
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            EndPaint(hwnd, &ps);
            return 0;
        }
        default:
            return DefWindowProc(hwnd, umsg, wparam, lparam);
        }
}

void create_window(){
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "windowclass";
    wc.hbrBackground = CreateSolidBrush(RGB(255,0,255));
    RegisterClassA(&wc);

HWND hwnd = CreateWindowExA( WS_EX_LAYERED | WS_EX_TOPMOST, "windowclass", "External Encrypter", WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE, 0 ,0, 800, 600, NULL, NULL, hInstance, NULL);

    SetLayeredWindowAttributes(hwnd, RGB(255,0,255), 0, LWA_COLORKEY);

    if(hwnd==NULL){
        MessageBoxA(hwnd , "window created", "info", MB_OK);
    }
    ShowWindow(hwnd , SW_SHOW);
    UpdateWindow(hwnd);
    
    MSG msg;
    while(GetMessage(&msg, NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

int main() {
    std::cout << "starting application..." << std::endl;
    create_window();
    
}