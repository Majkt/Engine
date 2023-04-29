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
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 10000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 16;

		std::shared_ptr<VertexArray> QuadVertexArray;
		std::shared_ptr<VertexBuffer> QuadVertexBuffer;
		std::shared_ptr<Shader> TextureShader;
		std::shared_ptr<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;
		std::array<std::shared_ptr<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;
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
			{ ShaderDataType::Float2, "array_texture_coord_" },
			{ ShaderDataType::Float,  "array_texture_index_" },
			{ ShaderDataType::Float,  "array_tiling_factor_" }
		});
		data_.QuadVertexArray->AddVertexBuffer(data_.QuadVertexBuffer);

		data_.QuadVertexBufferBase = new QuadVertex[data_.MaxVertices];

		uint32_t* quadIndices = new uint32_t[data_.MaxIndices];

		uint32_t offset = 0;
		for (uint32_t i{0}; i < data_.MaxIndices; i += 6)
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

		int32_t samplers[data_.MaxTextureSlots];
		for (uint32_t i{0}; i < data_.MaxTextureSlots; i++)
			samplers[i] = i;

        data_.TextureShader = Shader::Create(get_current_dir() + "/src/sandbox/assets/shaders/Texture.glsl");
		data_.TextureShader->Bind();
		data_.TextureShader->SetIntArray("uniform_textures_", samplers, data_.MaxTextureSlots);

		// Set first texture slot to 0
		data_.TextureSlots[0] = data_.WhiteTexture;

		data_.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		data_.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
		data_.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
		data_.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }

	void Renderer2D::Shutdown()
	{
		MAJKT_PROFILE_FUNCTION();

		delete[] data_.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		MAJKT_PROFILE_FUNCTION();
		data_.TextureShader->Bind();
		data_.TextureShader->SetMat4("view_projection_", camera.GetViewProjectionMatrix());

		data_.QuadIndexCount = 0;
		data_.QuadVertexBufferPtr = data_.QuadVertexBufferBase;

		data_.TextureSlotIndex = 1;
    }

	void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
	{
		MAJKT_PROFILE_FUNCTION();

		glm::mat4 viewProj = camera.GetProjection() * glm::inverse(transform);

		data_.TextureShader->Bind();
		data_.TextureShader->SetMat4("view_projection_", viewProj);

		data_.QuadIndexCount = 0;
		data_.QuadVertexBufferPtr = data_.QuadVertexBufferBase;

		data_.TextureSlotIndex = 1;
	}

	void Renderer2D::EndScene()
	{
		MAJKT_PROFILE_FUNCTION();
		uint32_t dataSize = (uint32_t)((uint8_t*)data_.QuadVertexBufferPtr - (uint8_t*)data_.QuadVertexBufferBase );
		data_.QuadVertexBuffer->SetData(data_.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{
		if (data_.QuadIndexCount == 0)
			return; 
			
		for (uint32_t i{0}; i < data_.TextureSlotIndex; ++i)
			data_.TextureSlots[i]->Bind(i);

		RenderCommand::DrawIndexed(data_.QuadVertexArray, data_.QuadIndexCount);
		data_.Stats.DrawCalls++;
	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		data_.QuadIndexCount = 0;
		data_.QuadVertexBufferPtr = data_.QuadVertexBufferBase;

		data_.TextureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{
		MAJKT_PROFILE_FUNCTION();
		
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		MAJKT_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
	{
		MAJKT_PROFILE_FUNCTION();
		
		constexpr size_t quadVertexCount = 4;

		const float textureIndex = 0.0f; // White Texture
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
		const float tilingFactor = 1.0f;

		if (data_.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		for (size_t i{0}; i < quadVertexCount; i++)
		{
			data_.QuadVertexBufferPtr->Position = transform * data_.QuadVertexPositions[i];
			data_.QuadVertexBufferPtr->Color = color;
			data_.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			data_.QuadVertexBufferPtr->TexIndex = textureIndex;
			data_.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			data_.QuadVertexBufferPtr++;
		}

		data_.QuadIndexCount += 6;

		data_.Stats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::mat4& transform, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		MAJKT_PROFILE_FUNCTION();

		constexpr size_t quadVertexCount = 4;
		constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

		if (data_.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		float textureIndex = 0.0f;
		for (uint32_t i{1}; i < data_.TextureSlotIndex; ++i)
		{
			if (*data_.TextureSlots[i] == *texture)
			{
				textureIndex = (float)i;
				break;
			}
		}

		if (textureIndex == 0.0f)
		{
			if (data_.TextureSlotIndex >= Renderer2DData::MaxTextureSlots)
				FlushAndReset();

			textureIndex = (float)data_.TextureSlotIndex;
			data_.TextureSlots[data_.TextureSlotIndex] = texture;
			data_.TextureSlotIndex++;
		}

		for (size_t i{0}; i < quadVertexCount; i++)
		{
			data_.QuadVertexBufferPtr->Position = transform * data_.QuadVertexPositions[i];
			data_.QuadVertexBufferPtr->Color = tintColor;
			data_.QuadVertexBufferPtr->TexCoord = textureCoords[i];
			data_.QuadVertexBufferPtr->TexIndex = textureIndex;
			data_.QuadVertexBufferPtr->TilingFactor = tilingFactor;
			data_.QuadVertexBufferPtr++;
		}

		data_.QuadIndexCount += 6;

		data_.Stats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
	}
	
	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		MAJKT_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const std::shared_ptr<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		MAJKT_PROFILE_FUNCTION();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		DrawQuad(transform, texture, tilingFactor, tintColor);
	}

	void Renderer2D::ResetStats()
	{
		memset(&data_.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return data_.Stats;
	}

}
