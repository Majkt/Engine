#include "src/majkt_editor/editor_layer.h"
#include "src/lib/scene/scene_serializer.h"
#include "src/lib/core/file_options.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "third_party/imguizmo/ImGuizmo.h"
#include "absl/functional/bind_front.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), camera_controller_(1280.0f / 720.0f), square_color_({ 0.2f, 0.3f, 0.8f, 1.0f })
	{
	}

	void EditorLayer::OnAttach()
	{
		MAJKT_PROFILE_FUNCTION();
		Application::Get().GetImGuiLayer()->SetIniPath(false, get_current_dir() + "/src/majkt_editor/assets/imgui.ini");

	    checker_board_texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/majkt_editor/assets/textures/Checkerboard.png");
	    style_texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/majkt_editor/assets/textures/style.png");

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		framebuffer_ = Framebuffer::Create(fbSpec);

		// Creates Scene
		active_scene_ = std::make_shared<Scene>();
		scene_hierarchy_panel_.SetContext(active_scene_);
	}

	void EditorLayer::OnDetach()
	{
		MAJKT_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(Timestep ts)
	{
		MAJKT_PROFILE_FUNCTION();

		// Resize
		if (FramebufferSpecification spec = framebuffer_->GetSpecification();
			viewport_size_.x > 0.0f && viewport_size_.y > 0.0f &&
			(spec.Width != viewport_size_.x || spec.Height != viewport_size_.y))
		{
			framebuffer_->Resize((uint32_t)viewport_size_.x, (uint32_t)viewport_size_.y);
			camera_controller_.OnResize(viewport_size_.x, viewport_size_.y);
		
			active_scene_->OnViewportResize((uint32_t)viewport_size_.x, (uint32_t)viewport_size_.y);
		}

		// Update
		if (viewport_focused_)
			camera_controller_.OnUpdate(ts);

		// Render
		Renderer2D::ResetStats();
		framebuffer_->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();

		// Update scene
		active_scene_->OnUpdate(ts);
		framebuffer_->Unbind();
	}

	void EditorLayer::OnImGuiRender()
	{
		MAJKT_PROFILE_FUNCTION();

		// Note: Switch this to true to enable dockspace
		static bool dockspaceOpen = true;
		static bool opt_fullscreen_persistant = true;
		bool opt_fullscreen = opt_fullscreen_persistant;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive, 
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise 
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
		ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.0f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Serialize"))
				{
					SceneSerializer serializer(active_scene_);
					serializer.Serialize(get_current_dir() + "/src/majkt_editor/assets/scenes/example.majkt");
				}

				if (ImGui::MenuItem("Deserialize"))
				{
					SceneSerializer serializer(active_scene_);
					serializer.Deserialize(get_current_dir() + "/src/majkt_editor/assets/scenes/example.majkt");
				}

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		scene_hierarchy_panel_.OnImGuiRender();
		ImGui::Begin("Stats");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		viewport_focused_ = ImGui::IsWindowFocused();
		viewport_hovered_ = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!viewport_focused_ && !viewport_hovered_);
		
		ImVec2 viewportPanelSize{ImGui::GetContentRegionAvail()};
		viewport_size_ = { viewportPanelSize.x, viewportPanelSize.y };
		uint64_t textureID = framebuffer_->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ viewport_size_.x, viewport_size_.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		// Gizmos
		Entity selectedEntity = scene_hierarchy_panel_.GetSelectedEntity();
		if (selectedEntity && gizmo_type_ != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			float windowWidth = (float)ImGui::GetWindowWidth();
			float windowHeight = (float)ImGui::GetWindowHeight();
			ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

			// Camera
			auto cameraEntity = active_scene_->GetPrimaryCameraEntity();
			const auto& camera = cameraEntity.GetComponent<CameraComponent>().Camera;
			const glm::mat4& cameraProjection = camera.GetProjection();
			glm::mat4 cameraView = glm::inverse(cameraEntity.GetComponent<TransformComponent>().GetTransform());

			// Entity transform
			auto& tc = selectedEntity.GetComponent<TransformComponent>();
			glm::mat4 transform = tc.GetTransform();

			// Snapping
			bool snap = Input::IsKeyPressed(Key::LeftControl);
			float snapValue = 0.5f; // Snap to 0.5m for translation/scale
			// Snap to 45 degrees for rotation
			if (gizmo_type_ == ImGuizmo::OPERATION::ROTATE)
				snapValue = 45.0f;

			float snapValues[3] = { snapValue, snapValue, snapValue };

			ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
				(ImGuizmo::OPERATION)gizmo_type_, ImGuizmo::LOCAL, glm::value_ptr(transform),
				nullptr, snap ? snapValues : nullptr);

			if (ImGuizmo::IsUsing())
			{
				glm::vec3 translation, rotation, scale;
				math::DecomposeTransform(transform, translation, rotation, scale);

				glm::vec3 deltaRotation = rotation - tc.Rotation;
				tc.Translation = translation;
				tc.Rotation += deltaRotation;
				tc.Scale = scale;
			}
		}

		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::NewScene()
	{
		active_scene_ = std::make_shared<Scene>();
		active_scene_->OnViewportResize((uint32_t)viewport_size_.x, (uint32_t)viewport_size_.y);
		scene_hierarchy_panel_.SetContext(active_scene_);
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileOptions::OpenFile("Majkt Scene (*.majkt)\0*.majkt\0");
		if (!filepath.empty())
		{
			active_scene_ = std::make_shared<Scene>();
			active_scene_->OnViewportResize((uint32_t)viewport_size_.x, (uint32_t)viewport_size_.y);
			scene_hierarchy_panel_.SetContext(active_scene_);

			SceneSerializer serializer(active_scene_);
			serializer.Deserialize(filepath);
		}
	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileOptions::SaveFile("Majkt Scene (*.majkt)\0*.majkt\0");
		if (!filepath.empty())
		{
			filepath += ".majkt";
			SceneSerializer serializer(active_scene_);
			serializer.Serialize(filepath);
		}
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		switch (e.GetKeyCode())
		{
			case Key::N:
			{
				if (shift)
					NewScene();
				break;
			}
			case Key::O:
			{
				if (shift)
					OpenScene();
				break;
			}
			case Key::S:
			{
				if (shift)
					SaveSceneAs();
				break;
			}
					
			// Gizmos
			case Key::Q:
				gizmo_type_ = -1;
				break;
			case Key::W:
				gizmo_type_ = ImGuizmo::OPERATION::TRANSLATE;
				break;
			case Key::E:
				gizmo_type_ = ImGuizmo::OPERATION::ROTATE;
				break;
			case Key::R:
				gizmo_type_ = ImGuizmo::OPERATION::SCALE;
				break;
		}
	}
	
	void EditorLayer::OnEvent(Event& e)
	{
		camera_controller_.OnEvent(e);
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(absl::bind_front(&EditorLayer::OnKeyPressed, this));
	}
}
