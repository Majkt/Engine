#ifndef MAJKT_PLATFORM_OPENGL_RENDERER_API_H_
#define MAJKT_PLATFORM_OPENGL_RENDERER_API_H_

#include "src/lib/renderer/renderer_api.h"

namespace majkt {

	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Init() override;
		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_OPENGL_RENDERER_API_H_
