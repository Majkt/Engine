#ifndef MAJKT_EDITOR_EDITOR_LAYER_H_
#define MAJKT_EDITOR_EDITOR_LAYER_H_

#include "src/lib/majkt_export.h"

namespace majkt {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;
	private:
		majkt::OrthographicCameraController camera_controller_;

		// Temp
		std::shared_ptr<VertexArray> square_vertex_array_;
		std::shared_ptr<Shader> flat_color_shader_;
		std::shared_ptr<Framebuffer> frame_buffer_;

		std::shared_ptr<Texture2D> checker_board_texture_, style_texture_;
		glm::vec2 viewport_size_ = { 0.0f, 0.0f };

		glm::vec4 square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f };
	};

} // namespace majkt

#endif  // MAJKT_EDITOR_EDITOR_LAYER_H_
