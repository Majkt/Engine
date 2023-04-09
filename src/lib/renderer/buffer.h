#ifndef MAJKT_PLATFORM_RENDERER_BUFFER_H_
#define MAJKT_PLATFORM_RENDERER_BUFFER_H_

#include <stdint.h>

namespace majkt {

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size);
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_BUFFER_H_
