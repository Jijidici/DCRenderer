#include "DCRenderer.h"

#include "vec3.h"
#include "ray.h"

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
float hitSphere(const v3f & center, float radius, const ray & r) {
    v3f oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4.f * a * c;
    if (discriminant < 0.f)
        return -1.f;
    else
        return (-b - sqrtf(discriminant)) / (2.0f * a);
}

v3f computeColor(const ray & r) {
    v3f sphereCenter = v3f(0.f, 0.f, -1.f);
    float sphereRadius = 0.5f;
    float t = hitSphere(sphereCenter, sphereRadius, r);
    if (t > 0.f) {
        v3f N = normalize(r.pointAtParameter(t) - sphereCenter);
        return 0.5f * (N + 1.f);
    }

    t = 0.5f * (r.direction().y() + 1.f);
    return (1.f - t) * color(1.f, 1.f, 1.f) + t * color(0.5f, 0.7f, 1.f);
}

// Main render function
void DCRenderer::render(std::string & fbName) {
    const FrameBuffer * fb = getFramebuffer(fbName);
    size_t nx = fb->getWidth();
    size_t ny = fb->getHeight();
    size_t nchannel = fb->getChannel();
    float * buffer = fb->getBuffer();

    v3f lowerLeftCorner(-2.f, -1.f, -1.f);
    v3f horizontal(4.f, 0.f, 0.f);
    v3f vertical(0.f, 2.f, 0.f);
    v3f origin(0.f, 0.f, 0.f);

    for (size_t j = 0; j < ny; ++j) {
        for (size_t i = 0; i < nx; ++i) {

            // rendering code
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lowerLeftCorner + u * horizontal + v * vertical);
            color col = computeColor(r);

            // fill the framebuffer
            size_t idx = i + j*nx;
            for (size_t c = 0; c < nchannel; ++c)
                buffer[int(nchannel * idx + c)] = col[int(c)];
        }
    }
}

} // dc