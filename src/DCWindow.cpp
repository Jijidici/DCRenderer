#include "DCWindow.h"

namespace dc
{

void DCWindow::init() {
    if (!glfwInit())
    {
        std::cerr << "FAIL TO INIT GLFW ! EXIT PROGRAM" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_win = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
    if (!m_win)
    {
        glfwTerminate();
        std::cerr << "FAIL TO CREATE WINDOW ! EXIT PROGRAM" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_win);
    glfwSetKeyCallback(m_win, key_callback);
}

bool DCWindow::isStillOpen() const {
    return !glfwWindowShouldClose(m_win);
}

void DCWindow::endLoop() const {
    glfwSwapBuffers(m_win);
    glfwPollEvents();
}

} // dc