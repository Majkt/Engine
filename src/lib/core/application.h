#ifndef MAJKT_ENGINE_APLICATION_H_
#define MAJKT_ENGINE_APLICATION_H_

#include "src/lib/core/base_export.h"
#include "src/lib/core/layer_stack.h"
#include "src/lib/core/window.h"
#include "src/lib/core/imgui_layer.h"

#include <memory>

int main(int argc, char** argv);

namespace majkt 
{
	class Application
	{
	public:
		Application(const std::string& name = "Majkt App");
		virtual ~Application();

		void Close();
		void OnEvent(Event& e);
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		inline Window& GetWindow() { return *window_; }
		inline static Application& Get() { return *instance_; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);

		std::unique_ptr<Window> window_;
		ImGuiLayer* imgui_layer_;
		bool running_{true};
		bool minimized_{false};
		LayerStack layer_stack_;
		float last_frame_time_{0.0f};
		
	private:
		static Application* instance_;
		friend int ::main(int argc, char** argv);
    };

	// To be defined in CLIENT
	Application* CreateApplication();

} // namespace majkt

#endif  // MAJKT_ENGINE_APLICATION_H_
