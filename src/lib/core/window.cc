#include "src/lib/core/base_export.h"
#include "src/lib/core/window.h"

#ifdef MAJKT_PLATFORM_MACOS
    #include "src/lib/platform/macOS/macOS_window.h"
#endif
#ifdef MAJKT_PLATFORM_WINDOWS
    #include "src/lib/platform/windows/windows_window.h"
#endif

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

namespace majkt {

	std::unique_ptr<Window> Window::Create(const WindowProps& props)
	{
        LOG(WARNING) << "weee!";
        #ifdef MAJKT_PLATFORM_WINDOWS
            return std::make_unique<WindowsWindow>(props);
        #elif defined(MAJKT_PLATFORM_MACOS)
            return std::make_unique<MacOSWindow>(props);
        #else
            LOG(WARNING) << "MAJKT does not run on this platform!";
            return nullptr;
        #endif
	}

} // namespace majkt
