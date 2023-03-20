#include "src/lib/platform/macOS/macOS_window.h"
#include "src/lib/events/application_events.h"
#include "src/lib/events/mouse_events.h"
#include "src/lib/events/key_events.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

#include <GLFW/glfw3.h>

namespace majkt {

	static bool glfw_initialized_{false};
	
	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG(ERROR) << "GLFW Error: " << error << " " << description;
	}

	MacOSWindow::MacOSWindow(const WindowProps& props)
	{
		Init(props);
	}

	MacOSWindow::~MacOSWindow()
	{
		Shutdown();
	}

	void MacOSWindow::Init(const WindowProps& props)
	{
		data_.title_ = props.title_;
		data_.width_ = props.width_;
		data_.height_ = props.height_;

		LOG(INFO) << "Creating window " << props.title_ << " " << props.width_ << " " << props.height_;

		if (!glfw_initialized_)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
            LOG(INFO) << "glfwInit() = " << success;

			glfwSetErrorCallback(GLFWErrorCallback);
			
			glfw_initialized_ = true;
		}

		window_ = glfwCreateWindow((int)props.width_, (int)props.height_, data_.title_.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window_);
		glfwSetWindowUserPointer(window_, &data_);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(window_, [](GLFWwindow* window, int width, int height)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.width_ = width;
			data.height_ = height;

			WindowResizeEvent event(width, height);
			data.event_callback_(event);
		});

		glfwSetWindowCloseCallback(window_, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.event_callback_(event);
		});

		glfwSetKeyCallback(window_, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.event_callback_(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.event_callback_(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.event_callback_(event);
					break;
				}
			}
		});

		glfwSetMouseButtonCallback(window_, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.event_callback_(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.event_callback_(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(window_, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.event_callback_(event);
		});

		glfwSetCursorPosCallback(window_, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.event_callback_(event);
		});
	}

	void MacOSWindow::Shutdown()
	{
		glfwDestroyWindow(window_);
	}

	void MacOSWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window_);
	}

	void MacOSWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data_.v_sync_ = enabled;
	}

	bool MacOSWindow::IsVSync() const
	{
		return data_.v_sync_;
	}

} // namespace majkt
