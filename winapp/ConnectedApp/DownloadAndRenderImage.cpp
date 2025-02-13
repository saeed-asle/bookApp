#include "DownloadAndRenderImage.h"
#include "httplib.h"
#include "stb_image.h"
#include <GL/gl.h>
#include <iostream>

void DownloadAndRenderImage(CommonObjects& common) {
    // If a download is triggered, perform it synchronously (without threads)
    if (common.start_download) {
        std::cout << "Starting download for image URL: " << common.url << std::endl;

        httplib::Client cli("https://covers.openlibrary.org");
        cli.set_follow_location(true);

        auto res = cli.Get(common.url.c_str());

        if (res && res->status == 200) {
            std::cout << "Image download successful!" << std::endl;

            int width, height, channels;
            unsigned char* image_data = stbi_load_from_memory(reinterpret_cast<const unsigned char*>(res->body.c_str()), res->body.size(), &width, &height, &channels, 4);

            if (image_data) {
                std::cout << "Image loaded, width: " << width << ", height: " << height << std::endl;

                glGenTextures(1, &common.cover_texture_id);
                glBindTexture(GL_TEXTURE_2D, common.cover_texture_id);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                GLint error = glGetError();
                if (error != GL_NO_ERROR) {
                    std::cerr << "OpenGL error: " << error << std::endl;
                }

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

                GLint minFilterStatus = 0;
                glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_MIN_FILTER, &minFilterStatus);
                std::cout << "GL_TEXTURE_MIN_FILTER status: " << minFilterStatus << std::endl;

                // Free the image data after loading it to OpenGL
                stbi_image_free(image_data);
            }
            else {
                std::cerr << "Failed to load cover image data" << std::endl;
            }

            common.data_ready = true;
        }
        else {
            std::cerr << "Failed to download image from URL: " << common.url << std::endl;
            common.start_download = false;
        }

        common.start_download = false;
    }
}
