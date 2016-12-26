#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "vec3.h"
#include "GLFW\glfw3.h"

using namespace dc;

int main (void) {

	glfwInit();
    int nx = 200;
    int ny = 100;
    int nchannel = 4;

    unsigned char * data = new unsigned char[nchannel*nx*ny];

    for (int j = 0; j < ny; ++j) {
        for (int i = 0; i < nx; ++i) {
            color col(float(i) / float(nx), float(j) / float(ny), 0.2f);
            float alpha = 1.f;
            
            int ir = int(255.99f*col.r());
            int ig = int(255.99f*col.g());
            int ib = int(255.99f*col.b());
            int ia = int(255.99f*alpha);
            
            int idx = i + j*nx;
            data[nchannel * idx + 0] = ir;
            data[nchannel * idx + 1] = ig;
            data[nchannel * idx + 2] = ib;
            data[nchannel * idx + 3] = ia;
        }
    }

    stbi_write_png("out.png", nx, ny, nchannel, data, 0);
    delete[] data;

	return 0;
}