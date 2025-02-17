//
// Created by lepag on 2/16/2025.
//

#include "Screen.hpp"


namespace tri::core {
    Screen* Screen::mainScreen = nullptr;

    Screen::Screen(int width, int height, const char* title, const char* iconPath) {
        GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (window == nullptr) {;
            glfwTerminate();
            throw std::runtime_error("Failed to create GLFW window");
        }

        this->m_wnd = window;
        this->windowIcon(iconPath);
        glfwSetWindowUserPointer(window, this);

        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        if (mainScreen != nullptr) {
            glfwDestroyWindow(window);
            throw std::runtime_error("Failed to create main screen since one already exists");
        }

        this->width = width;
        this->height = height;
        mainScreen = this;
    }

    void Screen::render() {}

    GLFWwindow *Screen::wnd() {
        return this->m_wnd;
    }

    Screen *Screen::main() {
        return mainScreen;
    }


    bool Screen::windowClosing() {
        return glfwWindowShouldClose(this->m_wnd);
    }

    void Screen::windowToClose(bool toClose) {
        glfwSetWindowShouldClose(this->m_wnd, toClose);
    }

    void Screen::windowTitle(const char *title) const {
        glfwSetWindowTitle(this->m_wnd, title);
    }

    void Screen::windowIcon(const char *iconPath) {
        std::shared_ptr<util::Image> imgPtr = std::make_shared<util::Image>(iconPath);
        std::weak_ptr<util::Image> img = imgPtr;
        if (auto lockedImg = img.lock()) {
            glfwSetWindowIcon(this->m_wnd, 1, lockedImg->img());
        }
        this->m_wnd_ico = img;
    }

    void Screen::focus() const {
        if (glfwGetCurrentContext() != this->m_wnd) {
            glfwMakeContextCurrent(this->m_wnd);
        }
    }

    void Screen::unfocus() const {
        if (glfwGetCurrentContext() == this->m_wnd) {
            glfwMakeContextCurrent(nullptr);
        }
    }

    float Screen::aspectRatio() const {
        return static_cast<float>(this->width) / static_cast<float>(this->height);
    }

    std::vector<Screen*> Screen::subScreens() {
        std::vector<Screen*> screens;
        for (auto& screen : m_screens) {
            screens.emplace_back(screen);
        }
        return screens;
    }


    Screen *Screen::screenFromWindow(GLFWwindow *window) {
        return static_cast<Screen*>(glfwGetWindowUserPointer(window));
    }

    Screen *Screen::currentContext() {
        return screenFromWindow(glfwGetCurrentContext());
    }

    void Screen::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        Screen* screen = screenFromWindow(window);
        if (screen == nullptr) {
            return;
        }

        glViewport(0, 0, width, height);
        screen->width = width;
        screen->height = height;
    }

    Screen::~Screen() {
        if (!this->m_screens.empty()) {
            for (const auto screen : m_screens) {
                screen->close();
            }
        }
        this->m_wnd_ico.reset();
        glfwDestroyWindow(this->m_wnd);
    }

} // core
// tri