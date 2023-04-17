#include "src/lib/renderer/frame_buffer.h"
#include "src/lib/renderer/renderer.h"
#include "src/lib/renderer/opengl_frame_buffer.h"

namespace majkt {

	std::shared_ptr<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    LOG(WARNING) << "RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLFramebuffer>(spec);
		}

		LOG(WARNING) << "Unknown RendererAPI!";
		return nullptr;
	}

} // namespace majkt
