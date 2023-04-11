#ifndef MAJKT_PLATFORM_RENDERER_H_
#define MAJKT_PLATFORM_RENDERER_H_

#include "src/lib/renderer/render_command.h"
#include "src/lib/renderer/orthographic_camera.h"
#include "src/lib/renderer/shader.h"

namespace majkt {

	class Renderer
	{
        public:
			static void BeginScene(OrthographicCamera& camera);
			static void EndScene();
			static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);
			inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		private:
			struct SceneData
			{
				glm::mat4 ViewProjectionMatrix;
			};

			static SceneData* scene_data_;
		};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_H_
