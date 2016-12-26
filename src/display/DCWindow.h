#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <iostream>
#include "GLFW/glfw3.h"

namespace dc
{

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

class DCWindow {
public:
    DCWindow(int32_t width, int32_t height, const char * title)
        : m_width(width), m_height(height), m_title(title) {
        init();
    }

    ~DCWindow() {
        glfwTerminate();
    }

    void init();
    bool isStillOpen() const;
    void endLoop() const;

    inline int32_t width() const { return m_width; }
    inline int32_t height() const { return m_height; }
    inline const char * title() const { return m_title; }

private:
    GLFWwindow * m_win;
    int32_t m_width;
    int32_t m_height;
    const char * m_title;
};

} // dc