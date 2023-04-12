#include "src/lib/renderer/shader.h"
#include "src/lib/renderer/renderer.h"
#include "src/lib/renderer/opengl_shader.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    LOG(WARNING) << "RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLShader(vertexSrc, fragmentSrc);
		}

		LOG(WARNING) << "Unknown RendererAPI!";
		return nullptr;
	}

}
