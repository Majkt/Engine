#include "src/lib/renderer/opengl_context.h"
#include "src/lib/debug/instrumentor.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: window_handle_(windowHandle)
	{
		if (windowHandle == nullptr)
			LOG(FATAL) << "Window handle is null!";
		// LOG(INFO) << windowHandle;
	}

	void OpenGLContext::Init()
	{
		MAJKT_PROFILE_FUNCTION();
		glfwMakeContextCurrent(window_handle_);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!status)
			LOG(FATAL) << "Failed to initialize Glad!";
		// else
			// LOG(INFO) << status;

		LOG(INFO) << "OpenGL Info:";
		LOG(INFO) << "  Vendor: " << glGetString(GL_VENDOR);
		LOG(INFO) << "  Renderer: " << glGetString(GL_RENDERER);
		LOG(INFO) << "  Version: " << glGetString(GL_VERSION);
		LOG(INFO) << "  GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
	}

	void OpenGLContext::SwapBuffers()
	{
		MAJKT_PROFILE_FUNCTION();
		glfwSwapBuffers(window_handle_);
	}

}
