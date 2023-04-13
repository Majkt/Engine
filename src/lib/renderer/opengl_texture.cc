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
		int width{0}, height{0}, channels{0};
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        if (data == nullptr) {
            stbi_image_free(data);
            LOG(FATAL) << "Failed to load image!";
        }
		width_ = width;
		height_ = height;

		GLenum internalFormat{0}, dataFormat{0};
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

        glGenTextures(1, &renderer_id_);
        glBindTexture(GL_TEXTURE_2D, renderer_id_);
        
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// load image, create texture and generate mipmaps
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width_, height_, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &renderer_id_);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glActiveTexture(slot);
        glBindTexture(GL_TEXTURE_2D, renderer_id_);
	}
}
