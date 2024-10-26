#include <windows.h>
#include <iostream>

HHOOK keyboardHook;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN) {
            return 1;
        }
    }
    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}
void Cleanup() {
    UnhookWindowsHookEx(keyboardHook);
}

int main() {
    keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    if (!keyboardHook) {
        std::cerr << "Hook Failed Error Code: " << GetLastError() << std::endl;
        return 1;
    }

    std::cout << "Your keyboard is locked now. You can start cleaning it and after you are done simply close the program." << std::endl;
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    Cleanup();
    return 0;
}
