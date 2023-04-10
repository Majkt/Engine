#ifndef MAJKT_PLATFORM_RENDER_COMMAND_H_
#define MAJKT_PLATFORM_RENDER_COMMAND_H_

#include "src/lib/renderer/renderer_api.h"

namespace majkt {

	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			renderer_api_->SetClearColor(color);
		}

		inline static void Clear()
		{
			renderer_api_->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			renderer_api_->DrawIndexed(vertexArray);
		}
	private:
		static RendererAPI* renderer_api_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDER_COMMAND_H_
