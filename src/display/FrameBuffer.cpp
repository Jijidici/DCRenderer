#include "Framebuffer.h"

#include <cassert>
#include <cstring>

namespace dc
{
FrameBuffer::FrameBuffer(size_t width, size_t height, size_t channel) {
    assert(width > 0 && height > 0 && channel > 0);

    m_width = width;
    m_height = height;
    m_channel = channel;
    m_pixelCount = width * height;
    m_bufferSize = m_pixelCount * channel * sizeof(float);

    m_buffer = new float[m_width * m_height * m_channel];
    memset(m_buffer, 0, m_bufferSize);
}

FrameBuffer::~FrameBuffer() {
    delete[] m_buffer;
}
} //dc 