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

		majkt::FramebufferSpecification fbSpec;
		fbSpec.Width = 1280;
		fbSpec.Height = 720;
		frame_buffer_ = majkt::Framebuffer::Create(fbSpec);
	}

	void EditorLayer::OnDetach()
	{
		MAJKT_PROFILE_FUNCTION();
	}

	void EditorLayer::OnUpdate(majkt::Timestep ts)
	{
		MAJKT_PROFILE_FUNCTION();

		// Update
		camera_controller_.OnUpdate(ts);

		// Render
		majkt::Renderer2D::ResetStats();
		{
			MAJKT_PROFILE_SCOPE("Renderer Prep");
			frame_buffer_->Bind();
			majkt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			majkt::RenderCommand::Clear();
		}

		{
			static float rotation = 0.0f;
			rotation += ts * 50.0f;

			MAJKT_PROFILE_SCOPE("Renderer Draw");
			majkt::Renderer2D::BeginScene(camera_controller_.GetCamera());
			majkt::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
			majkt::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
			majkt::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, square_color_);
			majkt::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, checker_board_texture_, 10.0f);
			majkt::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, style_texture_, 20.0f);
			majkt::Renderer2D::EndScene();

			// majkt::Renderer2D::BeginScene(camera_controller_.GetCamera());
			// for (float y = -5.0f; y < 5.0f; y += 0.5f)
			// {
			// 	for (float x = -5.0f; x < 5.0f; x += 0.5f)
			// 	{
			// 		glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
			// 		majkt::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
			// 	}
			// }
			// majkt::Renderer2D::EndScene();
			frame_buffer_->Unbind();
		}
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

				if (ImGui::MenuItem("Exit")) majkt::Application::Get().Close();
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		ImGui::Begin("Settings");

		auto stats = majkt::Renderer2D::GetStats();
		ImGui::Text("Renderer2D Stats:");
		ImGui::Text("Draw Calls: %d", stats.DrawCalls);
		ImGui::Text("Quads: %d", stats.QuadCount);
		ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
		ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

		ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));

		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport");
		ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
		if (viewport_size_ != *((glm::vec2*)&viewportPanelSize))
		{
			frame_buffer_->Resize((uint32_t)viewportPanelSize.x, (uint32_t)viewportPanelSize.y);
			viewport_size_ = { viewportPanelSize.x, viewportPanelSize.y };

			camera_controller_.OnResize(viewportPanelSize.x, viewportPanelSize.y);
		}
		uint32_t textureID = frame_buffer_->GetColorAttachmentRendererID();
		ImGui::Image((void*)textureID, ImVec2{ viewport_size_.x, viewport_size_.y }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::End();
	}

	void EditorLayer::OnEvent(majkt::Event& e)
	{
		camera_controller_.OnEvent(e);
	}
}
