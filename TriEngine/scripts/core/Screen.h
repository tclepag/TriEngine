//
// Created by lepag on 2/17/2025.
//

#ifndef SCREEN_H
#define SCREEN_H

#include <functional>
#include <windows.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>
#include <glad/glad.h>
#include <iostream>


namespace tri::core {

class Screen {
public:
    enum Style {
        Minimized,
        Fullscreen,
    };
    struct ScreenInfo {
        int width = 800;
        int height = 600;
        LPCTSTR title = "Window";
        LPCTSTR className = "GLFWWindowClass";
        HWND parent = nullptr;
    };

    struct WindowProcedure {
        UINT result;
        WPARAM wParam;
        LPARAM lParam;
    };

    HWND hWnd;
    HINSTANCE hInstance;
    HDC hdc;
    HGLRC hrc;
    WindowProcedure windowProcedure = {};

    MSG msg{};

    static void createWindowClass(WNDCLASSEX wndclass);

    explicit Screen(const ScreenInfo &info);
    ~Screen();

    void setWindowCloseRequest();
    void makeCurrent() const;
    bool shouldKill() const;
    bool message();
    int getMessage();
    void dispatch() const;
    float aspectRatio() const;

    void setStyle(Style style);

    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    static std::vector<std::string> classNames;
private:
    RECT rect = {0, 0, 800, 600};
    Style style = Minimized;
    DWORD winStyle = WS_OVERLAPPEDWINDOW;
    std::function<bool()> closePrompt;
};

} // core
// tri

#endif //SCREEN_H
