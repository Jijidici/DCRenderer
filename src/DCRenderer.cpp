#include "DCRenderer.h"

#include <vector>
#include <thread>

#include "RenderTask.h"
#include "Camera.h"
#include "scene/HitableList.h"
#include "scene/Sphere.h"

namespace dc 
{

#define R_NEAR 0.001f
#define R_FAR  1000000.f

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

const FrameBuffer * DCRenderer::getFramebuffer(const std::string fbName) {
    auto found = m_frameBuffers.find(fbName);
    if (found != m_frameBuffers.end())
    {
        return found->second;
    }
    return nullptr;
}

v3f DCRenderer::computeColor(const ray & r) {
    Hitable::HitRecord hitRec = m_scene->hit(r, R_NEAR, R_FAR);
    if (hitRec.t > 0.f) {
        return 0.5f * (hitRec.N + 1.f);
    }

    // hit background
    float bgMixCoef = 0.5f * (r.direction().y() + 1.f);
    return (1.f - bgMixCoef) * color(1.f, 1.f, 1.f) + bgMixCoef * color(0.5f, 0.7f, 1.f);
}

// Setup function
void DCRenderer::prepare(const HitableList * scene, const Camera * camera) {
    m_scene = scene;
    m_camera = camera;
    m_threadCount = std::thread::hardware_concurrency();
}

// Main render function
void DCRenderer::render(const std::string fbName, const size_t sampleID) {
    if (m_scene == nullptr || m_camera == nullptr)
    {
        std::fprintf(stderr, "Scene or Camera has not be set before the render begins\n");
        exit(EXIT_FAILURE);
    }

    RenderTask task(this);
    std::vector<std::thread> threads(m_threadCount);
    for (uint32_t i = 0; i < m_threadCount; ++i)
        threads[i] = std::thread([&task, fbName, sampleID] { task.renderSample(fbName, sampleID); });
    
    for (uint32_t i = 0; i < m_threadCount; ++i)
        threads[i].join();
}

} // dc