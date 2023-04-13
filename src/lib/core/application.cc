#include "src/lib/core/application.h"
#include "src/lib/renderer/renderer.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

#include "absl/functional/bind_front.h"

#include "GLFW/glfw3.h"

namespace majkt
{
	Application* Application::instance_ = nullptr;

    Application::Application()
    {
		if (instance_){
			LOG(WARNING) << instance_ <<  " Application already exists!";
		}
		instance_ = this;
        window_ = std::unique_ptr<Window>(Window::Create());
        window_->SetEventCallback(absl::bind_front(&Application::OnEvent, this));
		
		Renderer::Init();

		imgui_layer_ = new ImGuiLayer();
		PushOverlay(imgui_layer_);
	}

    void Application::Run()
    {
        while (running_){
			float time = (float)glfwGetTime();
			Timestep timestep = time - last_frame_time_;
			last_frame_time_ = time;

			for (Layer* layer : layer_stack_)
				layer->OnUpdate(timestep);

			imgui_layer_->Begin();
			for (Layer* layer : layer_stack_)
				layer->OnImGuiRender();
			imgui_layer_->End();

			window_->OnUpdate();
        }
    }

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(absl::bind_front(&Application::OnWindowClose, this));

		for (auto it = layer_stack_.end(); it != layer_stack_.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled_)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layer_stack_.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layer_stack_.PushOverlay(layer);
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;
	}

} // namespace majkt
