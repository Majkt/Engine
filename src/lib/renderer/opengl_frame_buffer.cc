#include "src/lib/renderer/opengl_frame_buffer.h"

#include <glad/glad.h>

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	static const uint32_t kmax_framebuffer_size_{8192};

	namespace Utils {

		static GLenum TextureTarget(bool multisampled)
		{
			if (multisampled) glEnable(GL_MULTISAMPLE);  
			return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
		}

		static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
		{
			glGenTextures(count, outID);
		}

		static void BindTexture(bool multisampled, uint32_t id)
		{
			glBindTexture(TextureTarget(multisampled), id);
		}

		static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, uint32_t width, uint32_t height, int index)		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
		}

		static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
		{
			bool multisampled = samples > 1;
			if (multisampled)
			{
				glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
			}
			else
			{
				glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			}

			glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
		}

		static bool IsDepthFormat(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
			}

			return false;
		}

		static GLenum MajktFBTextureFormatToGL(FramebufferTextureFormat format)
		{
			switch (format)
			{
				case FramebufferTextureFormat::RGBA8:       return GL_RGBA8;
				case FramebufferTextureFormat::RED_INTEGER: return GL_RED_INTEGER;
			}

			LOG(FATAL) << "Unknown format!";
			return 0;
		}

	} // namespace Utils

	OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
		: specification_(spec)
	{
		for (auto spec : specification_.Attachments.Attachments)
		{
			if (!Utils::IsDepthFormat(spec.TextureFormat))
				color_attachments_specifications_.emplace_back(spec);
			else
				depth_attachment_specification_ = spec;
		}
		Invalidate();
	}

	OpenGLFramebuffer::~OpenGLFramebuffer()
	{
		glDeleteFramebuffers(1, &renderer_id_);
		glDeleteTextures(color_attachments_.size(), color_attachments_.data());
		glDeleteTextures(1, &depth_attachment_);
	}

	void OpenGLFramebuffer::Invalidate()
	{
		if (renderer_id_)
		{
			glDeleteFramebuffers(1, &renderer_id_);
			glDeleteTextures(color_attachments_.size(), color_attachments_.data());
			glDeleteTextures(1, &depth_attachment_);

			color_attachments_.clear();
			depth_attachment_ = 0;
		}

		glGenFramebuffers(1, &renderer_id_);
		glBindFramebuffer(GL_FRAMEBUFFER, renderer_id_);

		bool multisample = specification_.Samples > 1;

		// Attachments
		if (color_attachments_specifications_.size())
		{
			color_attachments_.resize(color_attachments_specifications_.size());
			Utils::CreateTextures(multisample, color_attachments_.data(), color_attachments_.size());

			for (size_t i = 0; i < color_attachments_.size(); i++)
			{
				Utils::BindTexture(multisample, color_attachments_[i]);
				switch (color_attachments_specifications_[i].TextureFormat)
				{
					case FramebufferTextureFormat::RGBA8:
						Utils::AttachColorTexture(color_attachments_[i], specification_.Samples, GL_RGBA8, GL_RGBA, specification_.Width, specification_.Height, i);
						break;
					case FramebufferTextureFormat::RED_INTEGER:
						Utils::AttachColorTexture(color_attachments_[i], specification_.Samples, GL_R32I, GL_RED_INTEGER, specification_.Width, specification_.Height, i);
						break;
				}
			}
		}

		if (depth_attachment_specification_.TextureFormat != FramebufferTextureFormat::None)
		{
			Utils::CreateTextures(multisample, &depth_attachment_, 1);
			Utils::BindTexture(multisample, depth_attachment_);
			switch (depth_attachment_specification_.TextureFormat)
			{
				case FramebufferTextureFormat::DEPTH24STENCIL8:
					Utils::AttachDepthTexture(depth_attachment_, specification_.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, specification_.Width, specification_.Height);
					break;
			}
		}

		if (color_attachments_.size() > 1)
		{
			if(color_attachments_.size() > 4) LOG(WARNING) << "Renderer supports only 4 color attachments!";
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(color_attachments_.size(), buffers);
		}
		else if (color_attachments_.empty())
		{
			// Only depth-pass
			glDrawBuffer(GL_NONE);
		}
		
		if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG(WARNING) << "Framebuffer is incomplete!  " << glGetError();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, renderer_id_);

		glViewport(0, 0, specification_.Width, specification_.Height);
	}

	void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
	{
		if (width == 0 || height == 0 || width > kmax_framebuffer_size_ || height > kmax_framebuffer_size_)
		{
			LOG(INFO) << "Attempted to rezize framebuffer to " << width << " " << height;
			return;
		}
		specification_.Width = width;
		specification_.Height = height;

		Invalidate();
	}

	void OpenGLFramebuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	int OpenGLFramebuffer::ReadPixel(uint32_t attachmentIndex, int x, int y)
	{
		if (attachmentIndex >= color_attachments_.size()) LOG(WARNING) << "Attachment index out of range!";

		glReadBuffer(GL_COLOR_ATTACHMENT0 + attachmentIndex);
		int pixelData;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixelData);
		return pixelData;

	}

	void OpenGLFramebuffer::ClearAttachment(uint32_t attachmentIndex, int value)
	{
		if (attachmentIndex >= color_attachments_.size()) LOG(ERROR) << "Attachment index out of range!";

		glClearBufferiv(GL_COLOR, attachmentIndex, &value);
		bool multisample = specification_.Samples > 1;
		Utils::BindTexture(multisample, depth_attachment_);
	}

}
