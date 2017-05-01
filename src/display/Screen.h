#pragma once

#include "GL/glew.h"

#include "Program.h"
#include "Framebuffer.h"

namespace dc
{
class Screen {
public:
    Screen(size_t width, size_t height)
        : m_width(width), m_height(height), m_program(nullptr) {}

    ~Screen() {
        if (m_program)
        {
            delete m_program;
            m_program = nullptr;
        }
    }

    void init();
    void updateTexture(const FrameBuffer * buffer);
    void updateSampleCount(const size_t sampleCount);
    void draw() const;


private:
    size_t m_width;
    size_t m_height;
    GLuint m_quadVAO;
    GLuint m_quadVBO[3];
    GLuint m_texture;
    GLuint m_sampleCountLocation;
    Program * m_program;


};
} // dc