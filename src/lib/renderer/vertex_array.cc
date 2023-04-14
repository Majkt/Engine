#include "src/lib/renderer/vertex_array.h"

#include "src/lib/renderer/renderer.h"
#include "src/lib/renderer/opengl_vertex_array.h"

namespace majkt {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:    LOG(INFO) << "RendererAPI::None is currently not supported!"; return nullptr;
			case RendererAPI::API::OpenGL:  return new OpenGLVertexArray();
			default: 						break;
		}

		LOG(WARNING) << "Unknown RendererAPI!";
		return nullptr;
	}

}
