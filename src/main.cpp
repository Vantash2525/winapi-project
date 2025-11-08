#include <iostream>
#include <windows.h>

void create_window(){
    HINSTANCE hInstance = GetModuleHandle(NULL);
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = DefWindowProcA;
    wc.hInstance = hInstance;
    wc.lpszClassName = "windowclass";
    RegisterClassA(&wc);

    HWND hwnd = CreateWindowExW(WS_EX_LAYERED | WS_EX_TRANSPARENT, L"windowclass", L"External Encrypter", WS_POPUP, 0 ,0, 800, 600, NULL, NULL, hInstance, NULL);
    if(hwnd ){
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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT umsg, WPARAM wparam , LPARAM lparam){
    switch(umsg){
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd, umsg, wparam, lparam);
        }
}
int main() {
    std::cout << "starting application..." << std::endl;
    create_window();
    
}