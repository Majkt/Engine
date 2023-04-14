#include "src/lib/renderer/renderer2D.h"

#include "src/lib/renderer/vertex_array.h"
#include "src/lib/renderer/shader.h"
#include "src/lib/renderer/render_command.h"

#include "src/lib/renderer/opengl_shader.h"

#ifndef MAJKT_ENGINE_GET_DIR_H_
#define MAJKT_ENGINE_GET_DIR_H_

// For use by Majkt applications
#if defined(MAJKT_PLATFORM_WINDOWS)
	#define GetCurrentDir _getcwd
#else  
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

#include <string>

inline std::string get_current_dir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

#endif // MAJKT_ENGINE_GET_DIR_H_

namespace majkt {

	struct Renderer2DStorage
	{
		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<Shader> FlatColorShader;
	};

	static Renderer2DStorage* data_;

	void Renderer2D::Init()
	{
		data_ = new Renderer2DStorage();
		data_->QuadVertexArray = VertexArray::Create();

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
			{ ShaderDataType::Float3, "array_position_" }
		});
		data_->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        data_->QuadVertexArray->SetIndexBuffer(squareIB);

		data_->FlatColorShader = Shader::Create(get_current_dir() + "/src/sandbox/assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete data_;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(data_->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(data_->FlatColorShader)->UploadUniformMat4("view_projection_", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(data_->FlatColorShader)->UploadUniformMat4("transform_", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(data_->FlatColorShader)->Bind();
		std::dynamic_pointer_cast<majkt::OpenGLShader>(data_->FlatColorShader)->UploadUniformFloat4("uniform_color", color);

		data_->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(data_->QuadVertexArray);
	}

}
