
#ifndef MAJKT_PLATFORM_RENDERER_2D_H_
#define MAJKT_PLATFORM_RENDERER_2D_H_

#include "src/lib/renderer/orthographic_camera.h"

namespace majkt {

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();

		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_2D_H_

