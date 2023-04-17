#ifndef MAJKT_PLATFORM_RENDERER_FRAME_BUFFER_H_
#define MAJKT_PLATFORM_RENDERER_FRAME_BUFFER_H_

#include <glm/glm.hpp>
#include <memory>

namespace majkt {

	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		uint32_t Samples = 1;

		bool SwapChainTarget = false;
	};

	class Framebuffer
	{
	public:
        virtual ~Framebuffer() = default;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void Resize(uint32_t width, uint32_t height) = 0;

		virtual uint32_t GetColorAttachmentRendererID() const = 0;

		virtual const FramebufferSpecification& GetSpecification() const = 0;

		static std::shared_ptr<Framebuffer> Create(const FramebufferSpecification& spec);
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_FRAME_BUFFER_H_