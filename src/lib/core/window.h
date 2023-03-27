#ifndef MAJKT_CORE_WINDOW_H
#define MAJKT_CORE_WINDOW_H

#include "src/lib/core/base_export.h"
#include "src/lib/events/event.h"

#include <functional>
#include <string>

namespace majkt {

	struct WindowProps
	{
		std::string title_;
		uint32_t width_;
		uint32_t height_;

		WindowProps(const std::string& title = "Majkt Engine",
			        uint32_t width = 1280,
			        uint32_t height = 720)
			: title_(title), width_(width), height_(height)
		{}
	};

	// Interface representing a desktop system based Window
	class MAJKT_BASE_EXPORT Window
	{
	    public:
            using EventCallbackFn = std::function<void(Event&)>;

            virtual ~Window() {}

            virtual void OnUpdate() = 0;

            virtual uint32_t GetWidth() const = 0;
            virtual uint32_t GetHeight() const = 0;

            // Window attributes
            virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
            virtual void SetVSync(bool enabled) = 0;
            virtual bool IsVSync() const = 0;

			virtual void* GetNativeWindow() const = 0;

            static std::unique_ptr<Window> Create(const WindowProps& props = WindowProps());
	};
} // namespace majkt

#endif  // MAJKT_CORE_WINDOW_H
