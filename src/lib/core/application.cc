#include "src/lib/core/application.h"
#include "src/lib/renderer/renderer.h"
#include "src/lib/debug/instrumentor.h"

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
		MAJKT_PROFILE_FUNCTION();

		if (instance_){
			LOG(WARNING) << instance_ <<  " Application already exists!";
		}
		instance_ = this;
		window_ = Window::Create();
		window_->SetEventCallback(absl::bind_front(&Application::OnEvent, this));
		
		Renderer::Init();

		imgui_layer_ = new ImGuiLayer();
		PushOverlay(imgui_layer_);
	}

	Application::~Application()
	{
		MAJKT_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}
	
    void Application::Run()
    {
		MAJKT_PROFILE_FUNCTION();

        while (running_){
			MAJKT_PROFILE_SCOPE("RunLoop");
			float time = (float)glfwGetTime();
			Timestep timestep = time - last_frame_time_;
			last_frame_time_ = time;

			if (!minimized_)
			{
				{
					MAJKT_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : layer_stack_)
						layer->OnUpdate(timestep);
				}

				imgui_layer_->Begin();
				{
					MAJKT_PROFILE_SCOPE("LayerStack OnImGuiRender");

					for (Layer* layer : layer_stack_)
						layer->OnImGuiRender();
				}
				imgui_layer_->End();
			}
			window_->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e)
	{
		MAJKT_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(absl::bind_front(&Application::OnWindowClose, this));
		dispatcher.Dispatch<WindowResizeEvent>(absl::bind_front(&Application::OnWindowResize, this));
		for (auto it = layer_stack_.rbegin(); it != layer_stack_.rend(); ++it)
		{
			if (e.handled_)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		MAJKT_PROFILE_FUNCTION();

		layer_stack_.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		MAJKT_PROFILE_FUNCTION();

		layer_stack_.PushOverlay(layer);
		layer->OnAttach();
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		MAJKT_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			minimized_ = true;
			return false;
		}

		minimized_ = false;
		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return false;
	}

} // namespace majkt
