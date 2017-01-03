#include "Screen.h"

#include <cstdint>

namespace dc
{

void Screen::init() {
    
    // create quad
    int32_t quad_triangleIndices[] = {0, 1, 2, 2, 3, 0};
    float quad_vertices[] = { -1.f, -1.f, 1.f, -1.f, 1.f, 1.f, -1.f, 1.f };
    float quad_uvs[] = {0.f, 0.f, 1.f, 0.f, 1.f, 1.f, 0.f, 1.f};

    glGenVertexArrays(1, &m_quadVAO);
    glGenBuffers(3, m_quadVBO);

    glBindVertexArray(m_quadVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_quadVBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_triangleIndices), quad_triangleIndices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO[1]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, m_quadVBO[2]);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, (void*)0);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_uvs), quad_uvs, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // create shader
    const char * vShader = " \n\
        #version 410 core \n\
        layout(location = 0) in vec2 pos; \n\
        layout(location = 1) in vec2 texcoord; \n\
        out vec2 uv; \n\
        void main() { \n\
            uv = texcoord; \n\
            gl_Position = vec4(pos, 0.0, 1.0); \n\
        }";

    const char * fShader = "\n\
        #version 410 core \n\
        out vec4 fragColor; \n\
        in vec2 uv; \n\
        uniform sampler2D uTex; \n\
        void main() { \n\
             fragColor = vec4(texture(uTex, uv).rgb, 1.0); \n\
        } ";

    m_program = new Program(buildProgram(vShader, fShader));

    // create texture
    glGenTextures(1, &m_texture);
    GLuint texLocation = glGetUniformLocation(m_program->getGLId(), "uTex");
    glProgramUniform1i(m_program->getGLId(), texLocation, 0);
    glActiveTexture(GL_TEXTURE0);
}

void Screen::updateTexture(const FrameBuffer * buffer) {
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (GLsizei) buffer->getWidth(), (GLsizei) buffer->getHeight(), 0, GL_RGB, GL_FLOAT, (const GLvoid *) buffer->getBuffer());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Screen::draw() const {
    glBindTexture(GL_TEXTURE_2D, m_texture);
    m_program->use();
    glBindVertexArray(m_quadVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

} // dc