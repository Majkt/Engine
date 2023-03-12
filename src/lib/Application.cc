#include "src/lib/application.h"
#include "src/lib/events/application_events.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt
{
    Application::Application()
    {
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        WindowResizeEvent e(1280, 720);
        if (e.IsInCategory(kEventCategoryApplication))
		{
            LOG(INFO) << e;
		}
		if (e.IsInCategory(kEventCategoryInput))
		{
            LOG(INFO) << e;
		}

        while (true);
    }

} // namespace Majkt