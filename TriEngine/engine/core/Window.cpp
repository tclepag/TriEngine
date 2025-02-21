//
// Created by lepag on 2/21/25.
//

#include "Window.h"


namespace tri::core {
    Window::Window(Window *parent, int width, int height, std::string title, std::string icon) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        p_window = glfwCreateWindow(
            width,
            height,
            title.c_str(),
            nullptr,
            parent->p_window
            );
        p_parent = parent;

        glfwMakeContextCurrent(p_window);

        auto* img = new utility::Image(icon);
        glfwSetWindowIcon(p_window, 1, img->GetGLFWimage());
        img->Free();
    }

    Window::~Window() {
        glfwDestroyWindow(p_window);
    }

    glm::vec2 Window::getDimensions() {
        int width;
        int height;
        glfwGetWindowSize(p_window, &width, &height);
        return {width, height};
    }

    float Window::getAspectRatio() const {
        int width;
        int height;
        glfwGetWindowSize(p_window, &width, &height);

        return static_cast<float>(width) / static_cast<float>(height);
    }

    void Window::update() {
    }

    void Window::render() {

    }

    void Window::processInput() {
    }

    void Window::terminate() const {
        glfwSetWindowShouldClose(p_window, true);
    }

    bool Window::isTerminating() const {
        return glfwWindowShouldClose(p_window);
    }
} // core
// tri