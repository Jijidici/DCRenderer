#pragma once

namespace dc
{

enum Format {
    R = 1,
    RG,
    RGB,
    RGBA,
    COUNT
};

class FrameBuffer {
public:
    FrameBuffer(size_t width, size_t height, size_t channel);
    ~FrameBuffer();

    inline float * getBuffer() const { return m_buffer; }
    inline size_t getWidth() const { return m_width; }
    inline size_t getHeight() const { return m_height; }
    inline size_t getChannel() const { return m_channel; }
    inline size_t getPixelCount() const { return m_pixelCount; }
    inline size_t getBufferSize() const { return m_bufferSize; }

private:
    float * m_buffer;
    size_t m_width;
    size_t m_height;
    size_t m_channel;
    size_t m_pixelCount;
    size_t m_bufferSize;
};
} // dc