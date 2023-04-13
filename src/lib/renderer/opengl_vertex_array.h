#ifndef MAJKT_PLATFORM_OPENGL_VERTEX_ARRAY_H_
#define MAJKT_PLATFORM_OPENGL_VERTEX_ARRAY_H_

#include "src/lib/renderer/vertex_array.h"

namespace majkt {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return vertex_buffers_; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return index_buffer_; }
	private:
		uint32_t renderer_id_;
		uint32_t vertex_buffer_index_{0};
		std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers_;
		std::shared_ptr<IndexBuffer> index_buffer_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_OPENGL_VERTEX_ARRAY_H_
