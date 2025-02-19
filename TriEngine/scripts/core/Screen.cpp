//
// Created by lepag on 2/17/2025.
//

#include "Screen.h"



namespace tri::core {
    std::vector<std::string> Screen::classNames = {};

    LRESULT CALLBACK Screen::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
        auto* pThis = reinterpret_cast<Screen *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        std::cout << message << std::endl;
        if (pThis) {
            pThis->windowProcedure = {
                message,
                wParam,
                lParam,
            };

            switch (message) {
                case WM_DESTROY: {
                    if (wglGetCurrentContext() == pThis->hrc) {
                        wglMakeCurrent(nullptr, nullptr);
                    }

                    wglDeleteContext(pThis->hrc);
                    pThis->hrc = nullptr;

                    ReleaseDC(hWnd, pThis->hdc);
                    pThis->hrc = nullptr;

                    PostQuitMessage(0);
                    delete pThis;
                    return 0;
                }
                case WM_CLOSE: {
                    if (!pThis->closePrompt || pThis->closePrompt()) {
                        DestroyWindow(pThis->hWnd);
                    }
                    return 0;
                }
                case WM_NCHITTEST: {
                    LRESULT hit = DefWindowProc(hWnd, message, wParam, lParam);
                    if (hit == HTCLIENT) {
                        // Let Windows handle resizing properly.
                        return hit;
                    }
                    return hit;
                }

                default: {
                    break;
                }
            }
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    void Screen::createWindowClass(WNDCLASSEX wndclass) {
        wndclass.cbSize = sizeof(WNDCLASSEX);
        wndclass.lpfnWndProc = WindowProc;
        wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;

        if (RegisterClassEx(&wndclass) == 0) {
            DWORD error = GetLastError();
            std::cerr << "Failed to register window class: " << error << std::endl;
            throw std::runtime_error("Failed to register window class");
        }

        classNames.emplace_back(wndclass.lpszClassName);
    }


    Screen::Screen(const ScreenInfo &info) {
        msg = {};
        hInstance = GetModuleHandle(nullptr);

         hWnd = CreateWindowEx(
            0,
            info.className,
            info.title,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            info.width,
            info.height,
            info.parent,
            nullptr,
            hInstance,
            nullptr
        );

        if (!hWnd) {
            throw std::runtime_error("Failed to create window");
        }

        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

        hdc = GetDC(hWnd);
        if (!hdc) {
            DWORD error = GetLastError();
            std::cerr << "Failed to register hdc: " << error << std::endl;
            throw std::runtime_error("Failed to get device context");
        }

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
        pfd.nVersion = 1;
        pfd.dwFlags = PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.cColorBits = 32;
        pfd.cRedBits = 8;
        pfd.cGreenBits = 8;
        pfd.cBlueBits = 8;
        pfd.cAlphaBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;

        int pixelFormat = ChoosePixelFormat(hdc, &pfd);
        if (pixelFormat == 0)
        {
            MessageBox(nullptr, "Failed to choose pixel format", "Error", MB_OK | MB_ICONERROR);
            throw std::runtime_error("Failed to choose pixel format");
        }

        if (!SetPixelFormat(hdc, pixelFormat, &pfd))
        {
            MessageBox(nullptr, "Failed to set pixel format", "Error", MB_OK | MB_ICONERROR);
            throw std::runtime_error("Failed to set pixel format");
        }

        hrc = wglCreateContext(hdc);
        if (!hrc) {
            DWORD error = GetLastError();
            std::cerr << "Failed to register hrc: " << error << std::endl;
            throw std::runtime_error("Failed to create OpenGL context");
        }

        ShowWindow(hWnd, SW_SHOWNORMAL);
        UpdateWindow(hWnd);
    }

    Screen::~Screen() = default;

    void Screen::setStyle(Style style) {
        switch (style) {
            case Minimized:
                ChangeDisplaySettings(nullptr, 0);
                SetWindowLong(hWnd, GWL_STYLE, winStyle);
                SetWindowPos(hWnd, HWND_TOP, rect.left, rect.top,
                         rect.right - rect.left, rect.bottom - rect.top,
                         SWP_NOZORDER | SWP_FRAMECHANGED);
            case Fullscreen:
                GetWindowRect(hWnd, &rect);
                winStyle = GetWindowLong(hWnd, GWL_STYLE);
                SetWindowLong(hWnd, GWL_STYLE, winStyle & ~WS_OVERLAPPEDWINDOW);
                DEVMODE dm = {};
                dm.dmSize = sizeof(dm);
                dm.dmPelsWidth = 1920;
                dm.dmPelsHeight = 1080;
                dm.dmBitsPerPel = 32;
                dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_BITSPERPEL;
                ChangeDisplaySettings(&dm, CDS_FULLSCREEN);
                SetWindowPos(hWnd, HWND_TOP, 0, 0, 1920, 1080, SWP_NOZORDER | SWP_FRAMECHANGED);
        }
    }

    void Screen::makeCurrent() const {
        if (wglGetCurrentContext() != hrc) {
            wglMakeCurrent(hdc, hrc);
        }
    }

    bool Screen::shouldKill() const {
        return msg.message == WM_DESTROY ||
            msg.message == WM_QUIT;
    }

    bool Screen::message() {
        if (!IsWindow(hWnd)) {
            msg.message = WM_QUIT;
            return true;
        }
        return PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE);
    }

    float Screen::aspectRatio() const {
        RECT clientRect;
        if (GetClientRect(hWnd, &clientRect)) {
            int width = clientRect.right - clientRect.left;
            int height = clientRect.bottom - clientRect.top;
            return static_cast<float>(width) / static_cast<float>(height);
        }
        std::cerr << "Failed to get client rectangle." << std::endl;
        return 1.0f;
    }


    int Screen::getMessage() {
        if (!IsWindow(hWnd)) {
            msg.message = WM_QUIT;
            return 0;
        }
        return GetMessage(&msg, hWnd, 0, 0);
    }

    void Screen::dispatch() const {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }


} // core
// tri