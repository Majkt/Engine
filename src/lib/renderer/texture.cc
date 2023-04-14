#include "src/lib/renderer/renderer.h"
#include "src/lib/renderer/texture.h"
#include "src/lib/renderer/opengl_texture.h"

#include <memory>

namespace majkt {

	std::shared_ptr<Texture2D> Texture2D::Create(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    LOG(WARNING) << "RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
			default: 						break;
		}

		LOG(WARNING) << "Unknown RendererAPI!";
		return nullptr;
	}

}
