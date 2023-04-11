#include "src/lib/renderer/renderer.h"

namespace majkt {

	Renderer::SceneData* Renderer::scene_data_ = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		scene_data_->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("view_projection_", scene_data_->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
