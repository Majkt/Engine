#include "src/lib/application.h"
#include "src/lib/events/application_events.h"
#include "src/lib/core/window.h"
#include "src/lib/layer.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

#include "absl/functional/bind_front.h"
#include <glad/glad.h>

namespace majkt
{
    
    Application::Application()
    {
        window_ = std::unique_ptr<Window>(Window::Create());
        window_->SetEventCallback(absl::bind_front(&Application::OnEvent, this));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (running_){
			glClearColor(0.3, 0.6, 0.7, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layer_stack_)
				layer->OnUpdate();

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
