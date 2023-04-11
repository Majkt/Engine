#ifndef MAJKT_ENGINE_APLICATION_H_
#define MAJKT_ENGINE_APLICATION_H_

#include "src/lib/core/base_export.h"
#include "src/lib/core/layer_stack.h"
#include "src/lib/core/window.h"
#include "src/lib/core/timestep.h"
#include "src/lib/core/imgui_layer.h"

#include <memory>

namespace majkt 
{
	class Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void Run();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() { return *window_; }
		inline static Application& Get() { return *instance_; }

	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window_;
		ImGuiLayer* imgui_layer_;
		bool running_{true};
		LayerStack layer_stack_;
		float last_frame_time_{0.0f};
		
	private:
		static Application* instance_;
    };

	// To be defined in CLIENT
	Application* CreateApplication();

} // namespace majkt

#endif  // MAJKT_ENGINE_APLICATION_H_
