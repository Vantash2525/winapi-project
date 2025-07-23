#include<windows.h>
#include<stdio.h>
HHOOK hook ;
char buffer[256];
char classname[256];
char hwndstr[256];
void sendtext(){
    INPUT in;
    in.type = INPUT_KEYBOARD;
    in.ki.wVk =  'A';
    in.ki.dwFlags = 0;
    SendInput(1 , &in , sizeof(INPUT));a
    in.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1 , &in , sizeof(INPUT));
}
LRESULT CALLBACK MouseProc(int ncode , WPARAM wparam , LPARAM lparam){
    if(ncode == HC_ACTION && wparam == WM_LBUTTONDOWN){
        MSLLHOOKSTRUCT *ms = (MSLLHOOKSTRUCT *)lparam;
        POINT pt = ms->pt;
        HWND hwnd = WindowFromPoint(pt);
        if(hwnd){
            GetWindowTextA(hwnd, buffer, sizeof(buffer));
            snprintf(hwndstr, sizeof(hwndstr), "HWND for %s: %p " , buffer, hwnd);
            if(IsWindowEnabled(hwnd)){
                SetForegroundWindow(hwnd);
                sendtext();
                MessageBoxA(NULL , hwndstr, " window's handle " , MB_OK | MB_ICONINFORMATION);
            }
            
        }
    }
    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd ,UINT msg , WPARAM wparam , LPARAM lparam) {
    switch(msg){
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            return DefWindowProc(hwnd , msg , wparam , lparam ); 
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hinstance , HINSTANCE hprev , LPSTR lpcmdline , int ncmdshow) {

    hook = SetWindowsHookEx(WH_MOUSE_LL , MouseProc , 0 , 0 );
    if(!hook){
        MessageBoxEx(NULL , "failed to se the hook ", "Error" , MB_OK | MB_ICONERROR, 0);
        return 1;
    }

    MSG msg;
    while(GetMessage(&msg , NULL , 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);

    }
    return 0;
}