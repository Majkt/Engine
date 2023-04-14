#include "src/sandbox/sandbox_2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), camera_controller_(1280.0f / 720.0f)
{
}

void Sandbox2D::OnAttach()
{
	checker_board_texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/sandbox/assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(majkt::Timestep ts)
{
	// Update
	camera_controller_.OnUpdate(ts);

	// Render
	majkt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	majkt::RenderCommand::Clear();

	majkt::Renderer2D::BeginScene(camera_controller_.GetCamera());
	majkt::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	majkt::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	majkt::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, checker_board_texture_);
	majkt::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(square_color_));
	ImGui::End();
}

void Sandbox2D::OnEvent(majkt::Event& e)
{
	camera_controller_.OnEvent(e);
}