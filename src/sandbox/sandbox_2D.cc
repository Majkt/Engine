#include "src/sandbox/sandbox_2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), camera_controller_(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
	MAJKT_PROFILE_FUNCTION();
	checker_board_texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/sandbox/assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	MAJKT_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(majkt::Timestep ts)
{
	MAJKT_PROFILE_FUNCTION();

	// Update
	camera_controller_.OnUpdate(ts);

	// Render
	{
		MAJKT_PROFILE_SCOPE("Renderer Prep");
		majkt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		majkt::RenderCommand::Clear();
	}

	{
		MAJKT_PROFILE_SCOPE("Renderer Draw");
		majkt::Renderer2D::BeginScene(camera_controller_.GetCamera());
		majkt::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), left_square_color_);
		majkt::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, right_square_color_);
		majkt::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, checker_board_texture_, 10.0f);
		majkt::Renderer2D::EndScene();
	}}

void Sandbox2D::OnImGuiRender()
{
	MAJKT_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Left Square Color", glm::value_ptr(left_square_color_));
	ImGui::ColorEdit4("Right Square Color", glm::value_ptr(right_square_color_));

	ImGui::End();
}

void Sandbox2D::OnEvent(majkt::Event& e)
{
	camera_controller_.OnEvent(e);
}