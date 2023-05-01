#ifndef MAJKT_PLATFORM_RENDERER_OPENGL_FRAME_BUFFER_H_
#define MAJKT_PLATFORM_RENDERER_OPENGL_FRAME_BUFFER_H_

#include "src/lib/renderer/frame_buffer.h"
#include <glm/glm.hpp>

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

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
		virtual int ReadPixel(uint32_t attachmentIndex, int x, int y) override;

		virtual void ClearAttachment(uint32_t attachmentIndex, int value) override;
		virtual uint32_t GetColorAttachmentRendererID(uint32_t index = 0) const override { if(index >= color_attachments_.size()) LOG(FATAL) << "Index outside color attachment."; return color_attachments_[index]; }

		virtual const FramebufferSpecification& GetSpecification() const override { return specification_; }
	private:
		uint32_t renderer_id_ = 0;
		FramebufferSpecification specification_;

		std::vector<FramebufferTextureSpecification> color_attachments_specifications_;
		FramebufferTextureSpecification depth_attachment_specification_ = FramebufferTextureFormat::None;

		std::vector<uint32_t> color_attachments_;
		uint32_t depth_attachment_ = 0;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_OPENGL_FRAME_BUFFER_H_
