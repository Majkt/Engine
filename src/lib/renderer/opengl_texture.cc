#include "src/lib/renderer/opengl_texture.h"
#include "src/lib/debug/instrumentor.h"

#include <stb/stb_image.h>

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {
	
	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: width_(width), height_(height)
	{
		MAJKT_PROFILE_FUNCTION();
		internal_format_ = GL_RGBA8;
		data_format_ = GL_RGBA;

        glGenTextures(1, &renderer_id_);
        glBindTexture(GL_TEXTURE_2D, renderer_id_);
		
		// glTexStorage2D(GL_TEXTURE_2D, 1, internal_format_, width_, height_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: path_(path)
	{        
		MAJKT_PROFILE_FUNCTION();
		int width{0}, height{0}, channels{0};
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = nullptr;
		{
			MAJKT_PROFILE_SCOPE("stbi_load - OpenGLTexture2D::OpenGLTexture2D(const std:string&)");
			data = stbi_load(path.c_str(), &width, &height, &channels, 0);
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

		internal_format_ = internalFormat;
		data_format_ = dataFormat;

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
		MAJKT_PROFILE_FUNCTION();
		glDeleteTextures(1, &renderer_id_);
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		MAJKT_PROFILE_FUNCTION();
		uint32_t bpp = data_format_ == GL_RGBA ? 4 : 3;
		if (size != width_ * height_ * bpp) LOG(FATAL) << "Data must be entire texture!";
		// glTextureSubImage2D(renderer_id_, 0, 0, 0, width_, height_, data_format_, GL_UNSIGNED_BYTE, data);
		glTexImage2D(GL_TEXTURE_2D, 0, internal_format_, width_, height_, 0, data_format_, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		MAJKT_PROFILE_FUNCTION();

		glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, renderer_id_);
	}
}
