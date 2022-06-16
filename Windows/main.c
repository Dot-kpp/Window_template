#define UNICODE
#define _UNICODE

#include <Windows.h>
#include <winbase.h>
#include <stdio.h>

int globalRunning = 1;


	
	
LRESULT CALLBACK
WindowProc (HWND window,
            UINT message,
            WPARAM wParam,
            LPARAM lParam)
{
    LRESULT result;
    switch(message)
    {
        case WM_CLOSE:
        {
            globalRunning = 0;
        } break;

        default:
        {
            result = DefWindowProc(window, message, wParam, lParam);
        } break;
    }
    return (0);
}

int WINAPI 
wWinMain(HINSTANCE instance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    WNDCLASS window_class = {0};

    wchar_t CLASS_NAME[] = L"GameWindowClass";

    window_class.lpfnWndProc = WindowProc;
    window_class.hInstance = instance;
    window_class.lpszClassName - CLASS_NAME;

    RegisterClass(&window_class);

    HWND window = CreateWindowEx(0,
                                CLASS_NAME,
                                L"Game",
                                WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                0,
                                0,
                                instance,
                                0);
    while (globalRunning)
    {
        MSG message;
        while (PeekMessage(&message, window, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
        }
    }
    return (0);
}
