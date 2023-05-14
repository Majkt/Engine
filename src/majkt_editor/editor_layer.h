#ifndef MAJKT_EDITOR_EDITOR_LAYER_H_
#define MAJKT_EDITOR_EDITOR_LAYER_H_

#include "src/lib/majkt_export.h"
#include "src/lib/scene/scene_hierarchy_panel.h"

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
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		
		void NewScene();
		void OpenScene();
		void OpenScene(const std::filesystem::path& path);
		void SaveScene();
		void SaveSceneAs();

		void SerializeScene(std::shared_ptr<Scene> scene, const std::filesystem::path& path);

		void OnScenePlay();
		void OnSceneStop();

		void OnDuplicateEntity();
		void UI_Toolbar();

		majkt::OrthographicCameraController camera_controller_;

		std::shared_ptr<VertexArray> square_vertex_array_;
		std::shared_ptr<Shader> flat_color_shader_;
		std::shared_ptr<Framebuffer> framebuffer_;

		std::shared_ptr<Scene> active_scene_;
		std::shared_ptr<Scene> editor_scene_;
		std::filesystem::path editor_scene_path_;
		Entity square_entity_;
		Entity camera_entity_;
		Entity second_camera_;
		Entity hovered_entity_;

		bool primary_camera_{true};

		EditorCamera editor_camera_;

		std::shared_ptr<Texture2D> checker_board_texture_, style_texture_;
		bool viewport_focused_ = false, viewport_hovered_ = false;
		glm::vec2 viewport_size_ = { 0.0f, 0.0f };
		glm::vec2 viewport_bounds_[2];

		glm::vec4 square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f };
		
		int gizmo_type_{-1};

		enum class SceneState
		{
			Edit = 0, Play = 1
		};
		SceneState scene_state_ = SceneState::Edit;

		// Panels
		SceneHierarchyPanel scene_hierarchy_panel_;
		ContentBrowserPanel content_browser_panel_;

		std::shared_ptr<Texture2D> play_button_, stop_button_;
	};

} // namespace majkt

#endif  // MAJKT_EDITOR_EDITOR_LAYER_H_
