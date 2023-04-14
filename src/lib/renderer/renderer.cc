#include "src/lib/renderer/renderer.h"
#include "src/lib/renderer/renderer2D.h"
#include "src/lib/renderer/opengl_shader.h"

namespace majkt {

	std::unique_ptr<Renderer::SceneData> Renderer::scene_data_ = std::make_unique<Renderer::SceneData>();
	
	void Renderer::Init()
	{
		RenderCommand::Init();
		Renderer2D::Init();
	}

	void Renderer::Shutdown()
	{
		Renderer2D::Shutdown();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(0, 0, width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		scene_data_->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		shader->SetMat4("view_projection_", scene_data_->ViewProjectionMatrix);
		shader->SetMat4("transform_", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
