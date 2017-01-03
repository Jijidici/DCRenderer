#include "DCRenderer.h"

#include "vec3.h"

namespace dc 
{

DCRenderer::~DCRenderer() {
    for (auto fb : m_frameBuffers)
    {
        delete fb.second;
    }
}

bool DCRenderer::genFrameBuffer(std::string & fbName, size_t channel)
{
    auto found = m_frameBuffers.find(fbName);
    if (found == m_frameBuffers.end())
    {
        FrameBuffer * fb = new FrameBuffer(m_width, m_height, channel);
        m_frameBuffers.insert(std::make_pair(fbName, fb));
        return true;
    }
    return false;
}

const FrameBuffer * DCRenderer::getFramebuffer(std::string & fbName) {
    auto found = m_frameBuffers.find(fbName);
    if (found != m_frameBuffers.end())
    {
        return found->second;
    }
    return nullptr;
}

void DCRenderer::render(std::string & fbName) {
    const FrameBuffer * fb = getFramebuffer(fbName);
    size_t nx = fb->getWidth();
    size_t ny = fb->getHeight();
    size_t nchannel = fb->getChannel();
    float * buffer = fb->getBuffer();


    for (size_t j = 0; j < ny; ++j) {
        for (size_t i = 0; i < nx; ++i) {
            color col(float(i) / float(nx), float(j) / float(ny), 0.f);
            size_t idx = i + j*nx;
            for (size_t c = 0; c < nchannel; ++c)
                buffer[(int)(nchannel * idx + c)] = col[c];
        }
    }
}

} // dc