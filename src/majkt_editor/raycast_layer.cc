// #include "src/majkt_editor/raycast_layer.h"

// #include <glm/gtc/matrix_transform.hpp>
// #include <glm/gtc/type_ptr.hpp>

// RayCastLayer::RayCastLayer()
// 	: Layer("RayCastLayer"), camera_controller_(1280.0f / 720.0f, true)
// {
// }

// void RayCastLayer::OnAttach()
// {
// 	MAJKT_PROFILE_FUNCTION();
// 	checker_board_texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/sandbox/assets/textures/Checkerboard.png");
// 	style_texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/sandbox/assets/textures/style.png");
// }

// void RayCastLayer::OnDetach()
// {
// 	MAJKT_PROFILE_FUNCTION();
// }

// void RayCastLayer::OnUpdate(majkt::Timestep ts)
// {
// 	MAJKT_PROFILE_FUNCTION();

// 	// Update
// 	// camera_controller_.OnUpdate(ts);

// 	// Render
// 	majkt::Renderer2D::ResetStats();
// 	{
// 		MAJKT_PROFILE_SCOPE("Renderer Prep");

// 		majkt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
// 		majkt::RenderCommand::Clear();
// 	}

// 	{
// 		static float rotation{0.0f};
// 		rotation += ts * 50.0f;

// 		MAJKT_PROFILE_SCOPE("Renderer Draw");
// 		// majkt::Renderer2D::BeginScene(camera_controller_.GetCamera());
// 		// majkt::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, -45.0f, { 0.8f, 0.2f, 0.3f, 1.0f });
// 		// majkt::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, left_square_color_);
// 		// majkt::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, right_square_color_);
// 		// majkt::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, checker_board_texture_, 10.0f);
// 		// majkt::Renderer2D::DrawRotatedQuad({ -2.0f, 0.0f, 0.0f }, { 1.0f, 1.0f }, rotation, style_texture_, 20.0f);
// 		// majkt::Renderer2D::EndScene();

// 		// majkt::Renderer2D::BeginScene(camera_controller_.GetCamera());
// 		// for (float y = -5.0f; y < 5.0f; y += 0.5f)
// 		// {
// 		// 	for (float x = -5.0f; x < 5.0f; x += 0.5f)
// 		// 	{
// 		// 		glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
// 		// 		majkt::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, color);
// 		// 	}
// 		// }
// 		// majkt::Renderer2D::EndScene();

// 	}
// }

// void RayCastLayer::OnImGuiRender()
// {
// 	MAJKT_PROFILE_FUNCTION();

// 	ImGui::Begin("Settings");

// 	auto stats = majkt::Renderer2D::GetStats();
// 	ImGui::Text("Renderer2D Stats:");
// 	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
// 	ImGui::Text("Quads: %d", stats.QuadCount);
// 	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
// 	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

// 	ImGui::ColorEdit4("Square Color", glm::value_ptr(left_square_color_));
// 	ImGui::End();

// }

// void RayCastLayer::OnEvent(majkt::Event& e)
// {
// 	camera_controller_.OnEvent(e);
// }