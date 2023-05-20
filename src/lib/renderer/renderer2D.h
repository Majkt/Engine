
#ifndef MAJKT_PLATFORM_RENDERER_2D_H_
#define MAJKT_PLATFORM_RENDERER_2D_H_

#include "src/lib/renderer/camera.h"
// #include "src/lib/renderer/editor_camera.h"
#include "src/lib/renderer/orthographic_camera.h"
#include "src/lib/renderer/texture.h"
#include "src/lib/scene/components.h"

namespace majkt {
	class EditorCamera;
	struct SpriteRendererComponent;

	// This defines a Renderer2D class that provides functions for rendering 2D graphics using OpenGL.
	// It includes functions for drawing quads, rotated quads, and sprites with various parameters such as
	// position, size, color, and texture. The class also provides functions for beginning and ending a scene,
	// flushing the batch, and resetting and getting statistics for the number of draw calls and quads rendered.
	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(const Camera& camera, const glm::mat4& transform);	
		static void BeginScene(const EditorCamera& camera);	
		static void BeginScene(const OrthographicCamera& camera);
		static void EndScene();
		static void Flush();
		
		// Primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawQuad(const glm::mat4& transform, const glm::vec4& color, int entityID = -1);
		static void DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f), int entityID = -1);

		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
		static void DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));
		static void DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor = 1.0f, const glm::vec4& tintColor = glm::vec4(1.0f));

		static void DrawSprite(const glm::mat4& transform, SpriteRendererComponent& src, int entityID);

		// Stats
		struct Statistics
		{
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;

			uint32_t const GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t const GetTotalIndexCount() { return QuadCount * 6; }
		};
		static void ResetStats();
		static Statistics GetStats();
	private:
		static void StartBatch();
		static void NextBatch();
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_2D_H_

