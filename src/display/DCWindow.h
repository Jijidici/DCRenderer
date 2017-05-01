#pragma once

#include <stdlib.h>
#include <iostream>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "Screen.h"
#include "Framebuffer.h"

namespace dc
{

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

class DCWindow {
public:
    DCWindow(size_t width, size_t height, const char * title)
        : m_width(width), m_height(height), m_title(title) {
        m_screen = new Screen(m_width, m_height);
        init();
    }

    ~DCWindow() {
        glfwTerminate();
        delete m_screen;
    }

    void init();
    bool isStillOpen() const;
    void startLoop() const;
    void endLoop() const;
    void update(const FrameBuffer * buffer, const size_t sampleCount) const;

    inline size_t getWidth() const { return m_width; }
    inline size_t getHeight() const { return m_height; }
    inline const char * getTitle() const { return m_title; }

private:
    GLFWwindow * m_win;
    Screen * m_screen;
    size_t m_width;
    size_t m_height;
    const char * m_title;
};

} // dc