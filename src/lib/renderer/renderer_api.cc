#include "src/lib/renderer/renderer_api.h"
#include "src/lib/renderer/opengl_renderer_api.h"

namespace majkt {
	
	RendererAPI::API RendererAPI::api_ = RendererAPI::API::OpenGL;

	std::unique_ptr<RendererAPI> RendererAPI::Create()
	{
		switch (api_)
		{
			case RendererAPI::API::None:    LOG(WARNING) << "RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLRendererAPI>();
		}

		LOG(WARNING) << "Unknown RendererAPI!";
		return nullptr;
	}

}
