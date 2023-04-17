#ifndef MAJKT_PLATFORM_OPENGL_CONTEXT_H_
#define MAJKT_PLATFORM_OPENGL_CONTEXT_H_

#include "src/lib/renderer/graphics_context.h"

struct GLFWwindow;

namespace majkt {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* window_handle_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_OPENGL_CONTEXT_H_
