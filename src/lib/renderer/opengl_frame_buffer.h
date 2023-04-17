#ifndef MAJKT_PLATFORM_RENDERER_OPENGL_FRAME_BUFFER_H_
#define MAJKT_PLATFORM_RENDERER_OPENGL_FRAME_BUFFER_H_

#include "src/lib/renderer/frame_buffer.h"
#include <glm/glm.hpp>

namespace majkt {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FramebufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void Resize(uint32_t width, uint32_t height) override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return color_attachment_; }

		virtual const FramebufferSpecification& GetSpecification() const override { return specification_; }
	private:
		uint32_t renderer_id_ = 0;
		uint32_t color_attachment_ = 0, depth_attachment_ = 0;
		FramebufferSpecification specification_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_OPENGL_FRAME_BUFFER_H_
