#ifndef MAJKT_PLATFORM_RENDERER_H_
#define MAJKT_PLATFORM_RENDERER_H_

#include "src/lib/renderer/render_command.h"
#include "src/lib/renderer/orthographic_camera.h"
#include "src/lib/renderer/shader.h"

namespace majkt {

	// Defines a Renderer class that provides functionality for rendering graphics using a specific API.
	// The class has methods for initializing and shutting the renderer, handling window resize events, beginning
	// and ending a scene, and submitting data to be rendered. The class also contains a private SceneData struct
	// that stores the view projection matrix used for rendering. The Renderer class is designed to work with an
	// OrthographicCamera and a Shader, and it uses a VertexArray to specify the geometry to be rendered.

	class Renderer
	{
        public:
			static void Init();
			static void Shutdown();
			static void OnWindowResize(uint32_t width, uint32_t height);
			static void BeginScene(OrthographicCamera& camera);
			static void EndScene();
			static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));
			inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
		private:
			struct SceneData
			{
				glm::mat4 ViewProjectionMatrix;
			};

			static std::unique_ptr<SceneData> scene_data_;
		};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_H_
