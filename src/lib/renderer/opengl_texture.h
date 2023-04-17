#ifndef MAJKT_PLATFORM_RENDERER_OPENGL_TEXTURE_H_
#define MAJKT_PLATFORM_RENDERER_OPENGL_TEXTURE_H_

#include "src/lib/renderer/texture.h"

#include <glad/glad.h>

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(uint32_t width, uint32_t height);
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return width_;  }
		virtual uint32_t GetHeight() const override { return height_; }

		virtual void SetData(void* data, uint32_t size) override;
		virtual void Bind(uint32_t slot = 0) const override;

		virtual bool operator==(const Texture& other) const override
		{
			return renderer_id_ == ((OpenGLTexture2D&)other).renderer_id_;
		}
	private:
		std::string path_;
		uint32_t width_, height_;
		uint32_t renderer_id_;
		GLenum internal_format_, data_format_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_OPENGL_TEXTURE_H_
