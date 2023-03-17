#include "src/lib/platform/macOS/macOS_window.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

#include <GLFW/glfw3.h>

namespace majkt {

	static bool glfw_initialized_{false};

	// std::unique_ptr<Window> Window::Create(const WindowProps& props)
	// {
	// 	return std::make_unique<MacOSWindow>(props);
	// }

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

			glfw_initialized_ = true;
		}

		window_ = glfwCreateWindow((int)props.width_, (int)props.height_, data_.title_.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window_);
		glfwSetWindowUserPointer(window_, &data_);
		SetVSync(true);
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
