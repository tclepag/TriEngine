//
// Created by lepag on 2/17/2025.
//

#ifndef SCREEN_H
#define SCREEN_H

#include <windows.h>
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>


namespace tri::core {

class Screen {
    struct ScreenInfo {
        int width = 800;
        int height = 600;
        std::string title = "Window";
        std::string className = "GLFWWindowClass";
    };

    struct WindowProcedure {
        UINT result;
        WPARAM wParam;
        LPARAM lParam;
    };
public:
    static Screen* main;
    static Screen* createMainInstance(const ScreenInfo& info);

    Screen* createChildInstance(const ScreenInfo& info);
    [[nodiscard]] WindowProcedure GetWindowProc() const; // Returns the last window procedure result
    MSG GrabNewMessage(); // Peeks and returns a msg to be used for dispatching
    [[nodiscard]] MSG NoPeekMessage() const; // Returns the current msg without peeking
    void Dispatch() const; // Translates and dispatches the message
    void Destroy() const; // Destroys this windowClass
    void SetContextNew() const; // Sets the Window OpenGL context to this window, if it hasn't already been set
    void Swap() const; // Swaps the foreground with the background buffer
    float AspectRatio() const; // Returns the aspect ratio of this window (width / height)
    static Screen* GetContextScreen(); // Returns the Screen associated with the current context
private:
    explicit Screen(ScreenInfo info);
    ~Screen();

    MSG m_msg;
    WNDCLASSEX m_wc = {};
    HWND m_hwnd;
    HDC m_hdc;
    HINSTANCE m_hInstance;
    PIXELFORMATDESCRIPTOR m_pixelDescriptor;
    int m_pixelFormat;
    HGLRC m_context;
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

    ScreenInfo m_Info;
    std::vector<Screen*> m_children;
    static std::unordered_map<HGLRC, Screen*> m_screenContextList;
protected:
    WindowProcedure m_windowProcedure = {};
};

} // core
// tri

#endif //SCREEN_H
