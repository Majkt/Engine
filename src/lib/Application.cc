#include "src/lib/application.h"
#include "src/lib/events/application_events.h"
#include "src/lib/core/window.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

#include <GLFW/glfw3.h>

namespace majkt
{
    Application::Application()
    {
        window_ = std::unique_ptr<Window>(Window::Create());
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (running_){
			glClearColor(0.3, 0.6, 0.7, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window_->OnUpdate();
        }
    }

} // namespace Majkt
