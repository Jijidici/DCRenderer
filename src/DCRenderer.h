#pragma once

#include <unordered_map>
#include <string>

#include "display/FrameBuffer.h"

namespace dc {

class DCRenderer {
public:
    DCRenderer(size_t width, size_t height)
        : m_width(width), m_height(height) {}

    ~DCRenderer();

    bool genFrameBuffer(std::string & fbName, size_t channel);
    const FrameBuffer * getFramebuffer(std::string & fbName);

    void render(std::string & fbName, const size_t sampleID);

private:
    size_t m_width;
    size_t m_height;
    std::unordered_map<std::string, FrameBuffer *> m_frameBuffers;
};

} // dc