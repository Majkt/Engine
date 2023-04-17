#include "src/lib/renderer/opengl_frame_buffer.h"

#include <glad/glad.h>

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: specification_(spec)
	{
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &renderer_id_);
		glDeleteTextures(1, &color_attachment_);
		glDeleteTextures(1, &depth_attachment_);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (renderer_id_)
		{
			glDeleteFramebuffers(1, &renderer_id_);
			glDeleteTextures(1, &color_attachment_);
			glDeleteTextures(1, &depth_attachment_);
		}

		glGenFramebuffers(1, &renderer_id_);
		glBindFramebuffer(GL_FRAMEBUFFER, renderer_id_);

		glGenTextures(1, &color_attachment_);
		glBindTexture(GL_TEXTURE_2D, color_attachment_);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, specification_.Width, specification_.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_attachment_, 0);

		glGenTextures(1, &depth_attachment_);
		glBindTexture(GL_TEXTURE_2D, depth_attachment_);
		// glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, specification_.Width, specification_.Height);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, specification_.Width, specification_.Height, 0,
			GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_attachment_, 0);

		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            LOG(WARNING) << "Framebuffer is incomplete!";

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, renderer_id_);

		glViewport(0, 0, specification_.Width, specification_.Height);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		specification_.Width = width;
		specification_.Height = height;

		Invalidate();
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}


}
