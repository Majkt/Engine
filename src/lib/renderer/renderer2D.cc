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

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
	};

	struct Renderer2DData
	{
		const uint32_t MaxQuads = 10000;
		const uint32_t MaxVertices = MaxQuads * 4;
		const uint32_t MaxIndices = MaxQuads * 6;

		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<VertexBuffer> QuadVertexBuffer;
		std::shared_ptr<Shader> TextureShader;
		std::shared_ptr<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
	};

	static Renderer2DData data_;

	void Renderer2D::Init()
	{
		MAJKT_PROFILE_FUNCTION();

		data_.QuadVertexArray = VertexArray::Create();
		data_.QuadVertexBuffer = VertexBuffer::Create(data_.MaxVertices * sizeof(QuadVertex));
		data_.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "array_position_" },
			{ ShaderDataType::Float4, "array_color_" },
			{ ShaderDataType::Float2, "array_texture_coord_" }
		});
		data_.QuadVertexArray->AddVertexBuffer(data_.QuadVertexBuffer);

		data_.QuadVertexBufferBase = new QuadVertex[data_.MaxVertices];

		uint32_t* quadIndices = new uint32_t[data_.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i = 0; i < data_.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;

			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		
		std::shared_ptr<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, data_.MaxIndices);
		data_.QuadVertexArray->SetIndexBuffer(quadIB);
		delete[] quadIndices;

		data_.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		data_.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

        data_.TextureShader = Shader::Create(get_current_dir() + "/src/sandbox/assets/shaders/Texture.glsl");
		data_.TextureShader->Bind();
		data_.TextureShader->SetInt("texture_", 0);
    }

	void Renderer2D::Shutdown()
	{
		MAJKT_PROFILE_FUNCTION();
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		MAJKT_PROFILE_FUNCTION();
		data_.TextureShader->Bind();
		data_.TextureShader->SetMat4("view_projection_", camera.GetViewProjectionMatrix());

		data_.QuadIndexCount = 0;
		data_.QuadVertexBufferPtr = data_.QuadVertexBufferBase;
    }

	void Renderer2D::EndScene()
	{
		MAJKT_PROFILE_FUNCTION();
		uint32_t dataSize = (uint8_t*)data_.QuadVertexBufferPtr - (uint8_t*)data_.QuadVertexBufferBase;
		data_.QuadVertexBuffer->SetData(data_.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		RenderCommand::DrawIndexed(data_.QuadVertexArray, data_.QuadIndexCount);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		MAJKT_PROFILE_FUNCTION();

		data_.QuadVertexBufferPtr->Position = position;
		data_.QuadVertexBufferPtr->Color = color;
		data_.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
		data_.QuadVertexBufferPtr++;

		data_.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, 0.0f };
		data_.QuadVertexBufferPtr->Color = color;
		data_.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
		data_.QuadVertexBufferPtr++;

		data_.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, 0.0f };
		data_.QuadVertexBufferPtr->Color = color;
		data_.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
		data_.QuadVertexBufferPtr++;

		data_.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, 0.0f };
		data_.QuadVertexBufferPtr->Color = color;
		data_.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
		data_.QuadVertexBufferPtr++;

		data_.QuadIndexCount += 6;

		/*data_.TextureShader->SetFloat("uniform_tiling_factor__", 1.0f);
		data_.WhiteTexture->Bind();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_.TextureShader->SetMat4("transform_", transform);
		data_.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(data_.QuadVertexArray);*/
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		MAJKT_PROFILE_FUNCTION();
		data_.TextureShader->SetFloat4("uniform_color_", tintColor);
		data_.TextureShader->SetFloat("uniform_tiling_factor_", tilingFactor);
		texture->Bind();
        
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_.TextureShader->SetMat4("transform_", transform);

		data_.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(data_.QuadVertexArray);
		}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		MAJKT_PROFILE_FUNCTION();

		data_.TextureShader->SetFloat4("uniform_color_", color);
		data_.TextureShader->SetFloat("uniform_tiling_factor_", 1.0f);
		data_.WhiteTexture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_.TextureShader->SetMat4("transform_", transform);
		data_.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(data_.QuadVertexArray);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		MAJKT_PROFILE_FUNCTION();

		data_.TextureShader->SetFloat4("uniform_color_", tintColor);
		data_.TextureShader->SetFloat("uniform_tiling_factor_", tilingFactor);
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_.TextureShader->SetMat4("transform_", transform);

		data_.QuadVertexArray->Bind();
		RenderCommand::DrawIndexed(data_.QuadVertexArray);
	}

}
