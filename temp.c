#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#define whatsapp_hwnd 0x00030610 

HHOOK hook;
char buffer[256];

LRESULT CALLBACK keyProc(int ncode , WPARAM wparam , LPARAM lparam ){
    if(ncode == HC_ACTION && wparam == WM_KEYDOWN){
        SetFocus((HWND)whatsapp_hwnd);
        GetWindowTextA((HWND)whatsapp_hwnd , buffer , sizeof(buffer));
        if(IsWindowEnabled((HWND)whatsapp_hwnd)){
            MessageBoxA(NULL , buffer , "input window ", MB_OK);
            SetForegroundWindow((HWND)whatsapp_hwnd);
        }
    }     
    return 0;
}

int WINAPI WinMain(HINSTANCE hinstace , HINSTANCE hprev , LPSTR lpcmd , int ncmdshow){
    SetWindowsHookExA(WH_KEYBOARD_LL , keyProc , 0 , 0);
    MSG msg;
    while(GetMessage(&msg , NULL , 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}