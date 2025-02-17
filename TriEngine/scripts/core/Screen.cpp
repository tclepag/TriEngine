//
// Created by lepag on 2/17/2025.
//

#include "Screen.h"

#include <iostream>


namespace tri::core {
    Screen* Screen::main = nullptr;
    std::unordered_map<HGLRC, Screen*> Screen::m_screenContextList = {};

    LRESULT CALLBACK Screen::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        if (auto* pThis = reinterpret_cast<Screen *>(GetWindowLongPtr(hWnd, GWLP_USERDATA))) {
            pThis->m_windowProcedure = {
                message,
                wParam,
                lParam,
            };
        }
        return 0;
    }

    Screen::Screen(ScreenInfo info): m_msg({}), m_pixelDescriptor({0}) {
        m_wc = {0}; // Zero out the structure
        m_hInstance = GetModuleHandle(nullptr);

        const char* className = info.className.c_str();
        const char* titleName = info.title.c_str();

        m_wc.lpfnWndProc = WindowProc; // Window procedure function
        m_wc.cbSize = sizeof(WNDCLASSEX);
        m_wc.hInstance = m_hInstance; // Handle to the application instance
        m_wc.lpszClassName = className; // Class name
        m_wc.style = CS_HREDRAW | CS_VREDRAW; // Redraw on resizing

        std::cout << "Registering class name: " << info.className << std::endl;
        std::cout << "Instance handle: " << m_hInstance << std::endl;

        std::cout << "Creating window with class: " << info.className << std::endl;
        std::cout << "Title: " << info.title << std::endl;
        std::cout << "Size: " << info.width << "x" << info.height << std::endl;
        std::cout << "Style: " << m_wc.style << std::endl;



        if (!RegisterClassEx(&m_wc)) {
            MessageBox(nullptr, "Window class registration failed", "Error", MB_ICONERROR);
            DWORD error = GetLastError();
            std::cerr << "RegisterClassEx failed! Error: " << error << std::endl;
            exit(-1);
        }

        SetLastError(12345);
        HWND hwnd = CreateWindowEx(
    0,                              // Extended style
    "GLFWWindowClass",              // Class name
    "Debug Window",                 // Window title
    WS_OVERLAPPEDWINDOW,            // Window style
    CW_USEDEFAULT, CW_USEDEFAULT,   // Position
    800, 600,                       // Size
    nullptr, nullptr,                // Parent & menu
    GetModuleHandle(nullptr),                      // Instance handle
    nullptr                          // Additional params
);


        if (!hwnd) {
            std::cerr << "CreateWindowEx failed! Error: " << GetLastError() << std::endl;
        }
        std::cout << "DUMMY ERROR: " << GetLastError() << std::endl;

        if (m_hwnd == nullptr) {
            DWORD error = GetLastError();
            std::cerr << "Failed to create window! Error: " << error << std::endl;
            throw std::runtime_error("Failed to create window");
        }

        SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
        ShowWindow(m_hwnd, SW_SHOWNORMAL);

        // Device Context
        m_hdc = GetDC(m_hwnd);

        // OpenGL Pixel Description
        m_pixelDescriptor.nSize = sizeof(m_pixelDescriptor);
        m_pixelDescriptor.nVersion = 1;
        m_pixelDescriptor.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        m_pixelDescriptor.iPixelType = PFD_TYPE_RGBA;
        m_pixelDescriptor.cColorBits = 32;
        m_pixelDescriptor.cRedBits = 8;
        m_pixelDescriptor.cGreenBits = 8;
        m_pixelDescriptor.cBlueBits = 8;
        m_pixelDescriptor.cAlphaBits = 8;

        m_pixelFormat = ChoosePixelFormat(m_hdc, &m_pixelDescriptor);
        SetPixelFormat(m_hdc, m_pixelFormat, &m_pixelDescriptor);

        m_context = wglCreateContext(m_hdc);
        wglMakeCurrent(m_hdc, m_context);

        m_screenContextList[m_context] = this;

        UpdateWindow(m_hwnd);
        m_Info = std::move(info);
    }

    MSG Screen::GrabNewMessage() {
        PeekMessage(&m_msg, nullptr, 0, 0, PM_REMOVE);
        return m_msg;
    }

    MSG Screen::NoPeekMessage() const {
        return m_msg;
    }

    void Screen::Swap() const {
        SwapBuffers(m_hdc);
    }

    Screen::WindowProcedure Screen::GetWindowProc() const {
        return m_windowProcedure;
    }

    Screen *Screen::createMainInstance(const ScreenInfo& info) {
        if (main != nullptr) {
            throw std::runtime_error("Screen::createMainInstance called more than once");
        }

        auto* mainScreen = new Screen(info);
        main = mainScreen;
        return main;
    }

    Screen *Screen::createChildInstance(const ScreenInfo& info) {
        auto* childScreen = new Screen(info);
        m_children.push_back(childScreen);
        return childScreen;
    }

    void Screen::Dispatch() const {
        TranslateMessage(&m_msg);
        DispatchMessage(&m_msg);
    }

    float Screen::AspectRatio() const {
        return static_cast<float>(m_Info.width) / static_cast<float>(m_Info.height);
    }

    Screen::~Screen() {
        for (const auto& child : m_children) {
            child->Destroy();
        }
        m_screenContextList[m_context] = nullptr;

        wglDeleteContext(m_context);
        ReleaseDC(m_hwnd, m_hdc);
        UnregisterClass(m_wc.lpszClassName, m_hInstance);
    }

    void Screen::SetContextNew() const {
        if (wglGetCurrentContext() != m_context) {
            if (!wglMakeCurrent(m_hdc, m_context)) {
                DWORD error = GetLastError();
                std::cerr << "wglMakeCurrent failed! Error code: " << error << std::endl;
                throw std::runtime_error("Failed to make context current");
            }
            wglMakeCurrent(m_hdc, m_context);
        }
    }

    Screen *Screen::GetContextScreen() {
        HGLRC currentContext = wglGetCurrentContext();
        if (m_screenContextList.contains(currentContext)) {
            return m_screenContextList[currentContext];
        }
        return nullptr;
    }

    void Screen::Destroy() const {
        delete this;
    }

} // core
// tri