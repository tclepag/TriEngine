//
// Created by lepag on 2/16/2025.
//

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <stdexcept>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../util/Image.hpp"

namespace tri {
namespace core {

class Screen {
public:
    int width, height;
public:
    Screen(int width = 800, int height = 600, const char* title = "TriWindow", const char* iconPath = "content/images/app.bmp");
    ~Screen();

    // Returns the GLFWwindow associated with this Screen
    GLFWwindow* wnd();
    // Ran every frame
    // If active is false then you must call destruction
    virtual void render();
    // Runs glfwSetWindowToClose, if true then it will try to stop the mainloop and destroy this window
    void windowToClose(bool toClose);
    // Returns whether the window is set to close
    bool windowClosing();
    // Sets the windows width
    int windowWidth(int width);
    // Sets the windows height
    int windowHeight(int height);
    // Sets the windows title
    void windowTitle(const char* title) const;
    // Sets the windows icon
    void windowIcon(const char* iconPath);
    // Sets the window to be current context
    void focus() const;
    // Removes the window from current context if it ever was the context
    void unfocus() const;
    // Gets aspect ratio
    float aspectRatio() const;

    // Closes
    void close() {
        this->~Screen();
    };
    // Creates a subscreen
    Screen* subScreen(int width = 800, int height = 600, const char* title = "TriWindow", const char* iconPath = "content/images/app.bmp") {
        auto* s = new Screen(width, height, title, iconPath);
        m_screens.emplace_back(s);
        return s;
    }
    // Returns the current screen that is focused
    Screen* currentContext();
    // Returns the screen that uses this window
    static Screen* screenFromWindow(GLFWwindow *window);
    // Gets all subscreens
    std::vector<Screen*> subScreens();
private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
protected:
    GLFWwindow* m_wnd;
    std::vector<Screen*> m_screens;
    std::weak_ptr<util::Image> m_wnd_ico;
};

} // core
} // tri

#endif //SCREEN_HPP
