#include "src/majkt_editor/editor_layer.h"

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace majkt {

	EditorLayer::EditorLayer()
		: Layer("EditorLayer"), camera_controller_(1280.0f / 720.0f), square_color_({ 0.2f, 0.3f, 0.8f, 1.0f })
	{
	}

	void EditorLayer::OnAttach()
	{
		MAJKT_PROFILE_FUNCTION();

	    checker_board_texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/sandbox/assets/textures/Checkerboard.png");
	    style_texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/sandbox/assets/textures/style.png");

		FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		framebuffer_ = Framebuffer::Create(fbSpec);

		active_scene_ = std::make_shared<Scene>();

		// Entity
		auto square = active_scene_->CreateEntity("Green Square");
		square.AddComponent<SpriteRendererComponent>(glm::vec4{0.0f, 1.0f, 0.0f, 1.0f});

		square_entity_ = square;

		camera_entity_ = active_scene_->CreateEntity("Camera Entity");
		camera_entity_.AddComponent<CameraComponent>();

		second_camera_ = active_scene_->CreateEntity("Clip-Space Entity");
		auto& cc = second_camera_.AddComponent<CameraComponent>();
		cc.Primary = false;
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
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				// Disabling fullscreen would allow the window to be moved to the front of other windows, 
				// which we can't undo at the moment without finer window depth/z control.
				//ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen_persistant);

				if (ImGui::MenuItem("Exit")) Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		if (square_entity_)
		{
			ImGui::Separator();
			auto& tag = square_entity_.GetComponent<TagComponent>().Tag;
			ImGui::Text("%s", tag.c_str());

			auto& squareColor = square_entity_.GetComponent<SpriteRendererComponent>().Color;
			ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor));
			ImGui::Separator();
		}

		ImGui::DragFloat3("Camera Transform",
			glm::value_ptr(camera_entity_.GetComponent<TransformComponent>().Transform[3]));

		if (ImGui::Checkbox("Camera A", &primary_camera_))
		{
			camera_entity_.GetComponent<CameraComponent>().Primary = primary_camera_;
			second_camera_.GetComponent<CameraComponent>().Primary = !primary_camera_;
		}

		{
			auto& camera = second_camera_.GetComponent<CameraComponent>().Camera;
			float orthoSize = camera.GetOrthographicSize();
			if (ImGui::DragFloat("Second Camera Ortho Size", &orthoSize))
				camera.SetOrthographicSize(orthoSize);
		}

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");

		viewport_focused_ = ImGui::IsWindowFocused();
		viewport_hovered_ = ImGui::IsWindowHovered();
		Application::Get().GetImGuiLayer()->BlockEvents(!viewport_focused_ || !viewport_hovered_);

		ImVec2 viewportPanelSize{ImGui::GetContentRegionAvail()};
		viewport_size_ = { viewportPanelSize.x, viewportPanelSize.y };
		uint32_t textureID = framebuffer_->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ viewport_size_.x, viewport_size_.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(Event& e)
	{
		camera_controller_.OnEvent(e);
	}
}
