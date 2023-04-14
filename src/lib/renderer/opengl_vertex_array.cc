#include "src/lib/renderer/opengl_vertex_array.h"
#include "src/lib/renderer/vertex_array.h"

#include <glad/glad.h>

namespace majkt {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case majkt::ShaderDataType::Float:    return GL_FLOAT;
			case majkt::ShaderDataType::Float2:   return GL_FLOAT;
			case majkt::ShaderDataType::Float3:   return GL_FLOAT;
			case majkt::ShaderDataType::Float4:   return GL_FLOAT;
			case majkt::ShaderDataType::Mat3:     return GL_FLOAT;
			case majkt::ShaderDataType::Mat4:     return GL_FLOAT;
			case majkt::ShaderDataType::Int:      return GL_INT;
			case majkt::ShaderDataType::Int2:     return GL_INT;
			case majkt::ShaderDataType::Int3:     return GL_INT;
			case majkt::ShaderDataType::Int4:     return GL_INT;
			case majkt::ShaderDataType::Bool:     return GL_BOOL;
			default: 							  break;
		}

		LOG(WARNING) << "Unknown ShaderDataType!";
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &renderer_id_);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &renderer_id_);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(renderer_id_);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		glBindVertexArray(renderer_id_);
		vertexBuffer->Bind();

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(vertex_buffer_index_);
			glVertexAttribPointer(vertex_buffer_index_,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(const void*)(intptr_t)element.Offset);
			vertex_buffer_index_++;
		}
		vertex_buffers_.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(renderer_id_);
		indexBuffer->Bind();

		index_buffer_ = indexBuffer;
	}

}
