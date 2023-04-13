#include "src/lib/renderer/opengl_texture.h"

#include <stb/stb_image.h>

#include <glad/glad.h>

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: path_(path)
	{        
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (data == nullptr) {
            stbi_image_free(data);
            LOG(WARNING) << "Failed to load image!";
        }
		width_ = width;
		height_ = height;

        glGenTextures(1, &renderer_id_);
        glBindTexture(GL_TEXTURE_2D, renderer_id_);
        
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // load and generate the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_, height_, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &renderer_id_);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
        glBindTexture(GL_TEXTURE_2D, renderer_id_);
	}
}
