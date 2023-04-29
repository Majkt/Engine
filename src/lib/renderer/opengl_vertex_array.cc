#include "src/lib/renderer/opengl_vertex_array.h"
#include "src/lib/renderer/vertex_array.h"
#include "src/lib/debug/instrumentor.h"

#include <glad/glad.h>

namespace majkt {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:    return GL_FLOAT;
			case ShaderDataType::Float2:   return GL_FLOAT;
			case ShaderDataType::Float3:   return GL_FLOAT;
			case ShaderDataType::Float4:   return GL_FLOAT;
			case ShaderDataType::Mat3:     return GL_FLOAT;
			case ShaderDataType::Mat4:     return GL_FLOAT;
			case ShaderDataType::Int:      return GL_INT;
			case ShaderDataType::Int2:     return GL_INT;
			case ShaderDataType::Int3:     return GL_INT;
			case ShaderDataType::Int4:     return GL_INT;
			case ShaderDataType::Bool:     return GL_BOOL;
			default: 							  break;
		}

		LOG(WARNING) << "Unknown ShaderDataType!";
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		MAJKT_PROFILE_FUNCTION();
		glGenVertexArrays(1, &renderer_id_);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		MAJKT_PROFILE_FUNCTION();
		glDeleteVertexArrays(1, &renderer_id_);
	}

	void OpenGLVertexArray::Bind() const
	{
		MAJKT_PROFILE_FUNCTION();
		glBindVertexArray(renderer_id_);
	}

	void OpenGLVertexArray::Unbind() const
	{
		MAJKT_PROFILE_FUNCTION();
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		MAJKT_PROFILE_FUNCTION();
		glBindVertexArray(renderer_id_);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			switch (element.Type)
			{
				case ShaderDataType::Float:
				case ShaderDataType::Float2:
				case ShaderDataType::Float3:
				case ShaderDataType::Float4:
				case ShaderDataType::Int:
				case ShaderDataType::Int2:
				case ShaderDataType::Int3:
				case ShaderDataType::Int4:
				case ShaderDataType::Bool:
				{
					glEnableVertexAttribArray(vertex_buffer_index_);
					glVertexAttribPointer(vertex_buffer_index_,
						element.GetComponentCount(),
						ShaderDataTypeToOpenGLBaseType(element.Type),
						element.Normalized ? GL_TRUE : GL_FALSE,
						layout.GetStride(),
						(const void*)element.Offset);
					vertex_buffer_index_++;
					break;
				}
				case ShaderDataType::Mat3:
				case ShaderDataType::Mat4:
				{
					uint8_t count = element.GetComponentCount();
					for (uint8_t i = 0; i < count; i++)
					{
						glEnableVertexAttribArray(vertex_buffer_index_);
						glVertexAttribPointer(vertex_buffer_index_,
							count,
							ShaderDataTypeToOpenGLBaseType(element.Type),
							element.Normalized ? GL_TRUE : GL_FALSE,
							layout.GetStride(),
							(const void*)(element.Offset + sizeof(float) * count * i));
						glVertexAttribDivisor(vertex_buffer_index_, 1);
						vertex_buffer_index_++;
					}
					break;
				}
				default:
					LOG(WARNING) << "Unknown ShaderDataType!";
			}
		}
		vertex_buffers_.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		MAJKT_PROFILE_FUNCTION();
		glBindVertexArray(renderer_id_);
		indexBuffer->Bind();

		index_buffer_ = indexBuffer;
	}

}
