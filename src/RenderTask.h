#pragma once

#include <atomic>
#include "DCRenderer.h"

namespace dc {

class RenderTask {
public:
    friend class DCRenderer;
    static const int32_t TILE_SIZE = 16;
    static const int32_t TILE_PIXEL_COUNT = TILE_SIZE * TILE_SIZE;

    RenderTask(DCRenderer * renderer) 
        : m_rend(renderer) {
        float imagePixelCount = (float) (m_rend->m_width * m_rend->m_height);
        m_tileCount = (uint32_t) std::ceilf(imagePixelCount / (float) TILE_PIXEL_COUNT);
        m_widthInTile = (uint32_t) std::ceilf((float) m_rend->m_width / (float) TILE_SIZE);
    }

    void renderSample(const std::string fbName, const size_t sampleID);

private:
    DCRenderer * m_rend;
    uint32_t m_tileCount;
    uint32_t m_widthInTile;
    std::atomic<uint32_t> tileID = 0;
};

} // dc