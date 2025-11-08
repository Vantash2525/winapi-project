#include<windows.h>
#include<stdio.h>
HHOOK hook; 

void sendinput(){
    
    INPUT in[6] = {0};
    in[0].type = INPUT_KEYBOARD;
    in[0].ki.wVk = 'V';
    in[0].ki.dwFlags = 0;
    SendInput(1, &in[0], sizeof(INPUT));
    in[0].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &in[0], sizeof(INPUT));
    in[1].type = INPUT_KEYBOARD;
    in[1].ki.wVk = 'A';     
    in[1].ki.dwFlags = 0;
    SendInput(1, &in[1] , sizeof(INPUT));
    in[1].ki.dwFlags = KEYEVENTF_KEYUP;
    in[2].type = INPUT_KEYBOARD;
    in[2].ki.wVk = 'S';
    in[2].ki.dwFlags = 0;
    SendInput(1 , &in[2] , sizeof(INPUT));
    in[2].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1 , &in[2] , sizeof(INPUT));
    in[3].type = INPUT_KEYBOARD;
    in[3].ki.wVk = VK_RETURN;
    in[3].ki.dwFlags = 0;
    SendInput(1 , &in[3] , sizeof(INPUT));
    in[3].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1 , &in[3] , sizeof(INPUT));
    

}
LRESULT CALLBACK mouseProc(int ncode , WPARAM wparam , LPARAM lparam ){
    if(ncode == HC_ACTION && wparam == WM_LBUTTONDOWN){
        KBDLLHOOKSTRUCT *kb = (KBDLLHOOKSTRUCT *)lparam;
        HWND hwnd = GetForegroundWindow();
        if(hwnd){
            SetForegroundWindow(hwnd);
            sendinput();
            //MessageBoxA(NULL , "Input sent to the active window", "Info", MB_OK | MB_ICONINFORMATION);
        }
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hinstace , HINSTANCE hprev , LPSTR lpcmd , int cmdshow){
    hook = SetWindowsHookExA(WH_MOUSE_LL , mouseProc , 0 , 0 );
    if(hook == NULL){
        MessageBoxA(NULL , "failed to set hook " , "Error" , MB_OK | MB_ICONINFORMATION);
        return 1;
    }
    MSG msg;
    while (GetMessage(&msg , NULL , 0 , 0 )){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}