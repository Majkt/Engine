#ifndef MAJKT_PLATFORM_RENDER_COMMAND_H_
#define MAJKT_PLATFORM_RENDER_COMMAND_H_

#include "src/lib/renderer/renderer_api.h"

namespace majkt {

	class RenderCommand
	{
	public:
		inline static void Init()
		{
			renderer_api_->Init();
		}

		inline static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
		{
			renderer_api_->SetViewport(x, y, width, height);
		}

		inline static void SetClearColor(const glm::vec4& color)
		{
			renderer_api_->SetClearColor(color);
		}

		inline static void Clear()
		{
			renderer_api_->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray, uint32_t count = 0)
		{
			renderer_api_->DrawIndexed(vertexArray, count);
		}
	private:
		static std::unique_ptr<RendererAPI> renderer_api_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDER_COMMAND_H_
