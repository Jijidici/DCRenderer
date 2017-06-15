#include "RenderTask.h"

#include <random>
#include <algorithm>

#include "ray.h"
#include "Camera.h"
#include "scene\HitableList.h"

#include "display/FrameBuffer.h"

namespace dc {

void RenderTask::renderSample(const std::string fbName, const size_t sampleID) {

    while (tileID < m_tileCount)
    {
        uint32_t currentTile = tileID++;

        // Compute tile bounds
        uint32_t width = m_rend->m_width;
        uint32_t height = m_rend->m_height;
        uint32_t tileBeginX = TILE_SIZE * (currentTile % m_widthInTile);
        uint32_t tileBeginY = TILE_SIZE * (currentTile / m_widthInTile);
        uint32_t tileEndX = std::min(tileBeginX + TILE_SIZE, width);
        uint32_t tileEndY = std::min(tileBeginY + TILE_SIZE, height);


        // Setup the random samples
        std::default_random_engine generator((sampleID + 223) * currentTile);

        // Get framebuffer
        const FrameBuffer * fb = m_rend->getFramebuffer(fbName);
        uint32_t nchannel = fb->getChannel();
        float * buffer = fb->getBuffer();

        for (uint32_t j = tileBeginY; j < tileEndY; ++j) {
            for (uint32_t i = tileBeginX; i < tileEndX; ++i) {
                // rendering code
                float u = float(i + m_rend->m_distribution(generator)) / float(width);
                float v = float(j + m_rend->m_distribution(generator)) / float(height);
                ray r = m_rend->m_camera->getRay(u, v);
                color col = m_rend->computeColor(r, generator);

                // fill the framebuffer
                uint32_t idx = i + j * width;
                for (uint32_t c = 0; c < nchannel; ++c)
                    buffer[nchannel * idx + c] += col[c];
            }
        }
    }
}

} // dc