#pragma once

#include <unordered_map>
#include <string>

#include "display/FrameBuffer.h"

namespace dc {

class HitableList;
class Camera;

class DCRenderer {
public:
    DCRenderer(size_t width, size_t height)
        : m_width(width), m_height(height), m_scene(nullptr), m_camera(nullptr) {}

    ~DCRenderer();

    bool genFrameBuffer(std::string & fbName, size_t channel);
    const FrameBuffer * getFramebuffer(std::string & fbName);

    void prepare(const HitableList * scene, const Camera * camera);
    void render(std::string & fbName, const size_t sampleID);

private:
    size_t m_width;
    size_t m_height;
    std::unordered_map<std::string, FrameBuffer *> m_frameBuffers;

    const HitableList * m_scene;
    const Camera * m_camera;
};

} // dc