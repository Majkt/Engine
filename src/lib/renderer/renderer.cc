#include "src/lib/renderer/renderer.h"
#include "src/lib/renderer/opengl_shader.h"
namespace majkt {

	Renderer::SceneData* Renderer::scene_data_ = new Renderer::SceneData;

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
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("view_projection_", scene_data_->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("transform_", transform);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}
