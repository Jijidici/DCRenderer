#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

int main (void) {
    int nx = 200;
    int ny = 100;
    int nchannel = 4;

    unsigned char * data = new unsigned char[nchannel*nx*ny];

    for (int j = 0; j < ny; ++j) {
        for (int i = 0; i < nx; ++i) {
            float r = float(i) / float(nx);
            float g = float(j) / float(ny);
            float b = 0.2f;
            float a = 1.f;
            
            int ir = int(255.99f*r);
            int ig = int(255.99f*g);
            int ib = int(255.99f*b);
            int ia = int(255.99f*a);
            
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