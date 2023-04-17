#ifndef MAJKT_PLATFORM_OPENGL_BUFFER_H_
#define MAJKT_PLATFORM_OPENGL_BUFFER_H_

#include "src/lib/renderer/buffer.h"
#include <stdint.h>

namespace majkt {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout& GetLayout() const override { return layout_; }
		virtual void SetLayout(const BufferLayout& layout) override { layout_ = layout; }
	private:
		uint32_t renderer_id_;
		BufferLayout layout_;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const;
		virtual void Unbind() const;

		virtual uint32_t GetCount() const { return count_; }
	private:
		uint32_t renderer_id_;
		uint32_t count_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_OPENGL_BUFFER_H_
