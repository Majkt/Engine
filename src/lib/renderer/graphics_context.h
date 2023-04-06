#ifndef MAJKT_PLATFORM_RENDERER_GRAPHICS_CONTEXT_H_
#define MAJKT_PLATFORM_RENDERER_GRAPHICS_CONTEXT_H_

namespace majkt {

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_GRAPHICS_CONTEXT_H_
