#ifndef MAJKT_PLATFORM_RENDERER_API_H_
#define MAJKT_PLATFORM_RENDERER_API_H_

#include "src/lib/renderer/vertex_array.h"

#include <glm/glm.hpp>

namespace majkt {
	
    class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};
		virtual void Init() = 0;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;

		inline static API GetAPI() { return api_; }
	private:
		static API api_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_API_H_
