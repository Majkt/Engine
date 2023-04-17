#ifndef MAJKT_PLATFORM_RENDERER_GRAPHICS_CONTEXT_H_
#define MAJKT_PLATFORM_RENDERER_GRAPHICS_CONTEXT_H_

#include <memory>

namespace majkt {

	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static std::unique_ptr<GraphicsContext> Create(void* window);
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_GRAPHICS_CONTEXT_H_
