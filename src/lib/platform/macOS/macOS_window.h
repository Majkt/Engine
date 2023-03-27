#ifndef MAJKT_PLATFORM_MACOS_WINDOW_H_
#define MAJKT_PLATFORM_MACOS_WINDOW_H_

#include "src/lib/core/window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

namespace majkt {

	class MacOSWindow : public Window
	{
	public:
		explicit MacOSWindow(const WindowProps& props);
		virtual ~MacOSWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return data_.width_; }
		inline unsigned int GetHeight() const override { return data_.height_; }

		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { data_.event_callback_ = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override { return window_; }
	private:
	  	// Used in constructor for initializations
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* window_;

		struct WindowData
		{
			std::string title_;
			unsigned int width_, height_;
			bool v_sync_;

			EventCallbackFn event_callback_;
		};

		WindowData data_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_MACOS_WINDOW_H_
