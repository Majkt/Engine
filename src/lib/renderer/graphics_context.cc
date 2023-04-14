#include "src/lib/renderer/graphics_context.h"

#include "src/lib/renderer/renderer.h"
#include "src/lib/renderer/opengl_context.h"

namespace majkt {

	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    LOG(WARNING) << "RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
		}

		LOG(WARNING) << "Unknown RendererAPI!";
		return nullptr;
	}

}
