#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <Windows.h>
#include "JNI.h"
#include <tchar.h>

class MainWindow {
public:
    static MainWindow* instance;
    MainWindow(HINSTANCE hInstance);
    void Show(int nCmdShow);
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    HWND hwnd;
    HWND hEditX, hEditY, hEditZ;
    HWND hLabelX, hLabelY, hLabelZ;
    HWND hButton;
};

#endif
