#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "display/DCWindow.h"
#include "DCRenderer.h"

#define WIDTH 640
#define HEIGHT 320

using namespace dc;

int main (void) {
    DCWindow renderWindow(WIDTH, HEIGHT, "DCRenderer");
    DCRenderer renderer(WIDTH, HEIGHT);

    std::string beautyPass = "beauty";
    renderer.genFrameBuffer(beautyPass, Format::RGB);

    size_t sampleCount = 0;
    while (renderWindow.isStillOpen()) {
        renderWindow.startLoop();

        ++sampleCount;
        fprintf(stdout, "Samples : %d\n", sampleCount);
        renderer.render(beautyPass, sampleCount);
        const FrameBuffer * beautyFB = renderer.getFramebuffer(beautyPass);
        renderWindow.update(beautyFB, sampleCount);

        renderWindow.endLoop();
    }

	return 0;
}