#pragma once

#include <unordered_map>
#include <string>
#include <random>

#include "vec3.h"
#include "ray.h"

#include "display/FrameBuffer.h"

namespace dc {

class HitableList;
class Camera;
class RenderTask;

class DCRenderer {
public:
    DCRenderer(size_t width, size_t height)
        : m_width(width)
        , m_height(height)
        , m_scene(nullptr)
        , m_camera(nullptr)
        , m_threadCount(1) {}

    ~DCRenderer();

    bool genFrameBuffer(std::string & fbName, size_t channel);
    const FrameBuffer * getFramebuffer(const std::string fbName);

    void prepare(const HitableList * scene, const Camera * camera);
    void render(const std::string fbName, const size_t sampleID);

    friend class RenderTask;

private:
    v3f computeColor(const ray & r, std::default_random_engine & generator) const;
    v3f randomInUnitSphere(std::default_random_engine & generator) const;

    uint32_t m_width;
    uint32_t m_height;
    std::unordered_map<std::string, FrameBuffer *> m_frameBuffers;

    const HitableList * m_scene;
    const Camera * m_camera;
    unsigned int m_threadCount;
    std::uniform_real_distribution<float> m_distribution;
};

} // dc