#ifndef MAJKT_PLATFORM_RENDERER_OPENGL_TEXTURE_H_
#define MAJKT_PLATFORM_RENDERER_OPENGL_TEXTURE_H_

#include "src/lib/renderer/texture.h"

namespace majkt {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return width_;  }
		virtual uint32_t GetHeight() const override { return height_; }

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string path_;
		uint32_t width_, height_;
		uint32_t renderer_id_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_OPENGL_TEXTURE_H_
