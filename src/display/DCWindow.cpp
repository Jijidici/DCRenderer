#include "DCWindow.h"

#include "GL/glew.h"

#include "FrameBuffer.h"

namespace dc
{

void DCWindow::init() {
    if (!glfwInit())
    {
        std::cerr << "FAIL TO INIT GLFW ! EXIT PROGRAM" << std::endl;
        exit(EXIT_FAILURE);
    }

    m_win = glfwCreateWindow((int)m_width, (int)m_height, m_title, NULL, NULL);
    if (!m_win)
    {
        glfwTerminate();
        std::cerr << "FAIL TO CREATE WINDOW ! EXIT PROGRAM" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(m_win);
    glfwSetKeyCallback(m_win, key_callback);


    GLenum glewInitError = glewInit();
    if (GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

    m_screen->init();
}

bool DCWindow::isStillOpen() const {
    return !glfwWindowShouldClose(m_win);
}

void DCWindow::startLoop() const {
    glViewport(0, 0, (GLsizei)m_width, (GLsizei)m_height);
    glClear(GL_COLOR_BUFFER_BIT);
}

void DCWindow::endLoop() const {
    glfwSwapBuffers(m_win);
    glfwPollEvents();
}

void DCWindow::update(const FrameBuffer * buffer) const {
    m_screen->updateTexture(buffer);
    m_screen->draw();
}

} // dc