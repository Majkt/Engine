#ifndef MAJKT_PLATFORM_RENDERER_H_
#define MAJKT_PLATFORM_RENDERER_H_

#include "src/lib/renderer/render_command.h"

namespace majkt {

	class Renderer
	{
        public:
			static void BeginScene();
			static void EndScene();

			static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

			inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_H_
