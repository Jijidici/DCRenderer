#include "DCRenderer.h"

#include <vector>
#include <random>

#include "vec3.h"
#include "ray.h"
#include "Camera.h"
#include "scene/HitableList.h"
#include "scene/Sphere.h"

#define R_NEAR 0.001f
#define R_FAR  1000000.f 

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

// Local functions
v3f computeColor(const ray & r, const HitableList & scene) {
    Hitable::HitRecord hitRec = scene.hit(r, R_NEAR, R_FAR);
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
}

// Main render function
void DCRenderer::render(std::string & fbName, const size_t sampleID) {
    if (m_scene == nullptr || m_camera == nullptr)
    {
        std::fprintf(stderr, "Scene or Camera has not be set before the render begins\n");
        return;
    }

    const FrameBuffer * fb = getFramebuffer(fbName);
    size_t nx = fb->getWidth();
    size_t ny = fb->getHeight();
    size_t nchannel = fb->getChannel();
    float * buffer = fb->getBuffer();

    // Setup the random samples
    std::default_random_engine generator(sampleID);
    std::uniform_real_distribution<float> distribution;

    for (size_t j = 0; j < ny; ++j) {
        for (size_t i = 0; i < nx; ++i) {
            // rendering code
            float u = float(i + distribution(generator)) / float(nx);
            float v = float(j + distribution(generator)) / float(ny);
            ray r = m_camera->getRay(u, v);
            color col = computeColor(r, *m_scene);

            // fill the framebuffer
            size_t idx = i + j*nx;
            for (size_t c = 0; c < nchannel; ++c)
                buffer[int(nchannel * idx + c)] += col[int(c)];
        }
    }
}

} // dc