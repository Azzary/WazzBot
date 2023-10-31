#include "MainWindow.h"
#include <stdio.h>

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow(HINSTANCE hInstance) {
    instance = this;
    WNDCLASS wc = { 0 };
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WindowProc;
    wc.lpszClassName = L"MainWindowClass";
    RegisterClass(&wc);

    hwnd = CreateWindow(L"MainWindowClass", L"App", WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 750, 500, NULL, NULL, hInstance, this);
    hEditX = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 10, 10, 50, 20, hwnd, (HMENU)1, hInstance, NULL);
    hEditY = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 70, 10, 50, 20, hwnd, (HMENU)2, hInstance, NULL);
    hEditZ = CreateWindow(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 130, 10, 50, 20, hwnd, (HMENU)3, hInstance, NULL);

    hLabelX = CreateWindow(L"STATIC", L"X: ", WS_CHILD | WS_VISIBLE, 300, 10, 50, 20, hwnd, NULL, hInstance, NULL);
    hLabelY = CreateWindow(L"STATIC", L"Y: ", WS_CHILD | WS_VISIBLE, 350, 10, 50, 20, hwnd, NULL, hInstance, NULL);
    hLabelZ = CreateWindow(L"STATIC", L"Z: ", WS_CHILD | WS_VISIBLE, 400, 10, 50, 20, hwnd, NULL, hInstance, NULL);
    hButton = CreateWindow(L"BUTTON", L"Déplacer", WS_CHILD | WS_VISIBLE, 200, 10, 80, 30, hwnd, (HMENU)4, hInstance, NULL);
}

void MainWindow::Show(int nCmdShow) {
    ShowWindow(hwnd, nCmdShow);
}

LRESULT CALLBACK MainWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_COMMAND) {
        if (LOWORD(wParam) == 4) {
            TCHAR buffer[16];
            GetDlgItemText(hwnd, 1, buffer, 16);
            int x = _ttoi(buffer);
            GetDlgItemText(hwnd, 2, buffer, 16);
            int y = _ttoi(buffer);
            GetDlgItemText(hwnd, 3, buffer, 16);
            short z = (short)_ttoi(buffer);

            printf("x: %d, y: %d, z: %d\n", x, y, z);

            auto player = p_jni->p_wakfu_game_entity->GetLocalPlayerCharacter();
            if (player != nullptr) {
                player->move(x, y, z);
                Sleep(1000);
            }
        }
    }


    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
