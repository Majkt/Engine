#include "src/lib/renderer/renderer2D.h"

#include "src/lib/renderer/vertex_array.h"
#include "src/lib/renderer/shader.h"
#include "src/lib/renderer/render_command.h"

#include "src/lib/debug/instrumentor.h"

#include <glm/gtc/matrix_transform.hpp>

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
        std::shared_ptr<Shader> TextureShader;
        std::shared_ptr<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* data_;

	void Renderer2D::Init()
	{
		MAJKT_PROFILE_FUNCTION();
		data_ = new Renderer2DStorage();
		data_->QuadVertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		std::shared_ptr<VertexBuffer> squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "array_position_" },
			{ ShaderDataType::Float2, "texture_coord_" }
        });
		data_->QuadVertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
		data_->QuadVertexArray->SetIndexBuffer(squareIB);
		
		data_->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData{0xffffffff};
		data_->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        data_->TextureShader = Shader::Create(get_current_dir() + "/src/sandbox/assets/shaders/Texture.glsl");
		data_->TextureShader->Bind();
		data_->TextureShader->SetInt("texture_", 0);
    }

	void Renderer2D::Shutdown()
	{
		MAJKT_PROFILE_FUNCTION();
		delete data_;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		MAJKT_PROFILE_FUNCTION();
		data_->TextureShader->Bind();
		data_->TextureShader->SetMat4("view_projection_", camera.GetViewProjectionMatrix());
    }

	void Renderer2D::EndScene()
	{
		MAJKT_PROFILE_FUNCTION();
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		MAJKT_PROFILE_FUNCTION();
		data_->TextureShader->SetFloat4("uniform_color", color);
		data_->TextureShader->SetFloat("uniform_tiling_factor_", 1.0f);
		data_->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_->TextureShader->SetMat4("transform_", transform);

		data_->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(data_->QuadVertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		MAJKT_PROFILE_FUNCTION();
		data_->TextureShader->SetFloat4("uniform_color", tintColor);
		data_->TextureShader->SetFloat("uniform_tiling_factor", tilingFactor);
		texture->Bind();
        
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_->TextureShader->SetMat4("transform_", transform);

		data_->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(data_->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		MAJKT_PROFILE_FUNCTION();

		data_->TextureShader->SetFloat4("uniform_color", color);
		data_->TextureShader->SetFloat("uniform_tiling_factor", 1.0f);
		data_->WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_->TextureShader->SetMat4("transform_", transform);
		data_->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(data_->QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		MAJKT_PROFILE_FUNCTION();

		data_->TextureShader->SetFloat4("uniform_color", tintColor);
		data_->TextureShader->SetFloat("uniform_tiling_factor", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_->TextureShader->SetMat4("transform_", transform);

		data_->QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(data_->QuadVertexArray);
	}

}
