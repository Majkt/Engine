#ifndef MAJKT_PLATFORM_RENDERER_VERTEX_ARRAY_H_
#define MAJKT_PLATFORM_RENDERER_VERTEX_ARRAY_H_

#include <memory>
#include "src/lib/renderer/buffer.h"

namespace majkt {

	class VertexArray
	{
	public:
		virtual ~VertexArray() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

		static std::shared_ptr<VertexArray> Create();
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_VERTEX_ARRAY_H_

