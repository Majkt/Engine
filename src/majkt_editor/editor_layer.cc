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

	extern const std::filesystem::path asset_path_;

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
		play_button_ = majkt::Texture2D::Create(get_current_dir() + "/src/majkt_editor/assets/editor/play_button.png");
		stop_button_ = majkt::Texture2D::Create(get_current_dir() + "/src/majkt_editor/assets/editor/stop_button.png");

		FramebufferSpecification fbSpec;
		fbSpec.Attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		framebuffer_ = Framebuffer::Create(fbSpec);

		// Creates Scene
		active_scene_ = std::make_shared<Scene>();
		editor_camera_ = EditorCamera(30.0f, 1.778f, 0.1f, 1000.0f);
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
			editor_camera_.SetViewportSize(viewport_size_.x, viewport_size_.y);

			active_scene_->OnViewportResize((uint32_t)viewport_size_.x, (uint32_t)viewport_size_.y);
		}

		// Render
		Renderer2D::ResetStats();
		framebuffer_->Bind();
		RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		RenderCommand::Clear();

		// Clear our entity ID attachment to -1
		framebuffer_->ClearAttachment(1, -1);

		switch (scene_state_)
		{
			case SceneState::Edit:
			{
				if (viewport_focused_)
					camera_controller_.OnUpdate(ts);

				editor_camera_.OnUpdate(ts);

				active_scene_->OnUpdateEditor(ts, editor_camera_);
				break;
			}
			case SceneState::Play:
			{
				active_scene_->OnUpdateRuntime(ts);
				break;
			}
		}	
		auto[mx, my] = ImGui::GetMousePos();
		mx -= viewport_bounds_[0].x;
		my -= viewport_bounds_[0].y;
		glm::vec2 viewportSize = viewport_bounds_[1] - viewport_bounds_[0];
		my = viewportSize.y - my;
		int mouseX = (int)mx;
		int mouseY = (int)my;

		// Check if the mouse position is within the boundaries of the viewport
		if (mouseX >= 0 && mouseY >= 0 && mouseX < (int)viewportSize.x && mouseY < (int)viewportSize.y)
		{
			// Read the pixel data at the mouse position from the framebuffer
			int pixelData = framebuffer_->ReadPixel(1, mouseX, mouseY);
			
			// If the pixel data is -1, set the hovered entity to an empty Entity object,
			// otherwise, create an Entity object using the pixel data as the entity identifier
			hovered_entity_ = pixelData == -1 ? Entity() : Entity((entt::entity)pixelData, active_scene_.get());
		}
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
			// if (ImGui::BeginMenu("Majkt Editor"))
			// {
			// 	if (ImGui::MenuItem("Quit Majkt Editor")) 
			// 		Application::Get().Close();
			// 	ImGui::EndMenu();
			// }

			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("New", "Ctrl+N"))
					NewScene();
				if (ImGui::MenuItem("Open...", "Ctrl+O"))
					OpenScene();
				if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
					SaveSceneAs();
				if (ImGui::MenuItem("Close", "Cmd+Q")) 
					Application::Get().Close();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit")){ ImGui::EndMenu(); }
			if (ImGui::BeginMenu("Window")){ ImGui::EndMenu();}
			

			ImGui::EndMenuBar();
		}

		scene_hierarchy_panel_.OnImGuiRender();
		content_browser_panel_.OnImGuiRender();
		ImGui::Begin("Stats", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar );

		std::string name{"None"};
		if (hovered_entity_)
			name = hovered_entity_.GetComponent<TagComponent>().Tag;
		ImGui::Text("Hovered Entity: %s", name.c_str());

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();
		viewport_bounds_[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		viewport_bounds_[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		viewport_focused_ = ImGui::IsWindowFocused();
		viewport_hovered_ = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!viewport_focused_ && !viewport_hovered_);
		
		ImVec2 viewportPanelSize{ImGui::GetContentRegionAvail()};
		viewport_size_ = { viewportPanelSize.x, viewportPanelSize.y };
		uint64_t textureID = framebuffer_->GetColorAttachmentRendererID();
		ImGui::Image(reinterpret_cast<void*>(textureID), ImVec2{ viewport_size_.x, viewport_size_.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

		// Begin a drag and drop target with ImGui
		if (ImGui::BeginDragDropTarget())
		{
			// Check if a payload of type "CONTENT_BROWSER_ITEM" is accepted
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("CONTENT_BROWSER_ITEM"))
			{
				// Extract the path from the payload data
				const wchar_t* path = (const wchar_t*)payload->Data;

				// Open the scene using the provided asset path and the extracted path
				OpenScene(std::filesystem::path(asset_path_) / path);
			}
			
			// End the drag and drop target
			ImGui::EndDragDropTarget();
		}

		// Gizmos
		Entity selectedEntity = scene_hierarchy_panel_.GetSelectedEntity();
		if (selectedEntity && gizmo_type_ != -1)
		{
			ImGuizmo::SetOrthographic(false);
			ImGuizmo::SetDrawlist();

			ImGuizmo::SetRect(viewport_bounds_[0].x, viewport_bounds_[0].y, viewport_bounds_[1].x - viewport_bounds_[0].x, viewport_bounds_[1].y - viewport_bounds_[0].y);

			// Camera
			const glm::mat4& cameraProjection = editor_camera_.GetProjection();
			glm::mat4 cameraView = editor_camera_.GetViewMatrix();

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
		UI_Toolbar();

		ImGui::End();
	}

	void EditorLayer::UI_Toolbar()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
		ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
		auto& colors = ImGui::GetStyle().Colors;
		const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
		const auto& buttonActive = colors[ImGuiCol_ButtonActive];
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

		ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse);

		float size = ImGui::GetWindowHeight() - 4.0f;
		std::shared_ptr<Texture2D> icon = scene_state_ == SceneState::Edit ? play_button_ : stop_button_;
		ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
		if (ImGui::ImageButton((ImTextureID)icon->GetRendererID(), ImVec2(size, size), ImVec2(0, 0), ImVec2(1, 1), 0))
		{
			if (scene_state_ == SceneState::Edit)
				OnScenePlay();
			else if (scene_state_ == SceneState::Play)
				OnSceneStop();
		}
		ImGui::PopStyleVar(2);
		ImGui::PopStyleColor(3);
		ImGui::End();
	}

	bool EditorLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	{
		// Check if the left mouse button is pressed
		if (e.GetMouseButton() == Mouse::ButtonLeft)
		{
			// Check if the viewport is being hovered, ImGuizmo is not being interacted with,
			// and the left Alt key is not pressed
			if (viewport_hovered_ && !ImGuizmo::IsOver() && !Input::IsKeyPressed(Key::LeftAlt))
			{
				// Set the selected entity in the scene hierarchy panel to the hovered entity
				scene_hierarchy_panel_.SetSelectedEntity(hovered_entity_);
			}
		}
		return false;
	}

	void EditorLayer::NewScene()
	{
		active_scene_ = std::make_shared<Scene>();
		active_scene_->OnViewportResize((uint32_t)viewport_size_.x, (uint32_t)viewport_size_.y);
		scene_hierarchy_panel_.SetContext(active_scene_);
		editor_scene_path_ = std::filesystem::path();
	}

	void EditorLayer::OpenScene()
	{
		std::string filepath = FileOptions::OpenFile("Majkt Scene (*.majkt)\0*.majkt\0");
		if (!filepath.empty())
			OpenScene(filepath);
	}

	void EditorLayer::OpenScene(const std::filesystem::path& path)
	{
		if (scene_state_ != SceneState::Edit)
			OnSceneStop();

		if (path.extension().string() != ".majkt")
		{
			LOG(WARNING) << "Could not load " << path.filename().string() << " - not a scene file";
			return;
		}

		std::shared_ptr<Scene> newScene = std::make_shared<Scene>();
		LOG(INFO) << "Loading scene " << path.filename().string();
		SceneSerializer serializer(newScene);

		if (serializer.Deserialize(path.string()))
		{
			editor_scene_ = newScene;
			editor_scene_->OnViewportResize((uint32_t)viewport_size_.x, (uint32_t)viewport_size_.y);
			scene_hierarchy_panel_.SetContext(editor_scene_);			
			active_scene_ = editor_scene_;
			editor_scene_path_ = path;
		}
	}

	void EditorLayer::SaveScene()
	{
		if (!editor_scene_path_.empty())
			SerializeScene(active_scene_, editor_scene_path_);
		else
			SaveSceneAs();
 	}

	void EditorLayer::SaveSceneAs()
	{
		std::string filepath = FileOptions::SaveFile("Majkt Scene (*.majkt)\0*.majkt\0");
		if (!filepath.empty())
		{
			filepath += ".majkt";
			SerializeScene(active_scene_, filepath);
			editor_scene_path_ = filepath;
		}
	}

	void EditorLayer::SerializeScene(std::shared_ptr<Scene> scene, const std::filesystem::path& path)
	{
		SceneSerializer serializer(scene);
		serializer.Serialize(path.string());
	}

	bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
	{
		// Shortcuts
		if (e.GetRepeatCount() > 0)
			return false;

		bool control = Input::IsKeyPressed(Key::LeftControl) || Input::IsKeyPressed(Key::RightControl);
		bool shift = Input::IsKeyPressed(Key::LeftShift) || Input::IsKeyPressed(Key::RightShift);
		bool command = Input::IsKeyPressed(Key::LeftSuper) || Input::IsKeyPressed(Key::RightSuper);

		switch (e.GetKeyCode())
		{
			case Key::N:
			{
				if (control || command)
					NewScene();
				break;
			}
			case Key::O:
			{
				if (control || command)
					OpenScene();
				break;
			}
			case Key::S:
			{
				if (control || command)
				{
					if (shift)
						SaveSceneAs();
					else
						SaveScene();
				}
				break;
			}
			
			case Key::D:
			{
				if (control || command)
					OnDuplicateEntity();
 				break;
 			}

			case Key::Q:
			{
				if (command)
					Application::Get().Close();
					
				if (!ImGuizmo::IsUsing())
					gizmo_type_ = -1;
				break;
			}
			case Key::W:
			{
				if (!ImGuizmo::IsUsing())
					gizmo_type_ = ImGuizmo::OPERATION::TRANSLATE;
				break;
			}
			case Key::E:
			{
				if (!ImGuizmo::IsUsing())
					gizmo_type_ = ImGuizmo::OPERATION::ROTATE;
				break;
			}
			case Key::R:
			{
				if (!ImGuizmo::IsUsing())
					gizmo_type_ = ImGuizmo::OPERATION::SCALE;
				break;
			}
		}
	}
	
	void EditorLayer::OnEvent(Event& e)
	{
		camera_controller_.OnEvent(e);
		if (scene_state_ == SceneState::Edit)
		{
			editor_camera_.OnEvent(e);
		}
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<KeyPressedEvent>(absl::bind_front(&EditorLayer::OnKeyPressed, this));
		dispatcher.Dispatch<MouseButtonPressedEvent>(absl::bind_front(&EditorLayer::OnMouseButtonPressed, this));
	}

	void EditorLayer::OnScenePlay()
	{
		scene_state_ = SceneState::Play;
		active_scene_ = Scene::Copy(editor_scene_);
		active_scene_->OnRuntimeStart();
		scene_hierarchy_panel_.SetContext(active_scene_);
	}

	void EditorLayer::OnSceneStop()
	{
		scene_state_ = SceneState::Edit;
		active_scene_->OnRuntimeStop();
		active_scene_ = editor_scene_;
		scene_hierarchy_panel_.SetContext(active_scene_);
	}
 
	void EditorLayer::OnDuplicateEntity()
	{
		if (scene_state_ != SceneState::Edit)
			return;

		Entity selectedEntity = scene_hierarchy_panel_.GetSelectedEntity();
		if (selectedEntity)
			editor_scene_->DuplicateEntity(selectedEntity);
 	}

}
