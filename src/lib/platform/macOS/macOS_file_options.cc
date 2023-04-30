#include "src/lib/core/file_options.h"

#include "portable-file-dialogs.h"

#include <GLFW/glfw3.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

#include "src/lib/core/application.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

#if _WIN32
#define DEFAULT_PATH "C:\\"
#else
#define DEFAULT_PATH get_current_dir()
#endif

namespace majkt {

	std::string FileOptions::OpenFile(const char* filter)
	{
        // Set verbosity to true
        pfd::settings::verbose(true);

        // File open
		auto destination = pfd::open_file("Choose files to open", DEFAULT_PATH,
                                  {filter},
                                  pfd::opt::none).result();
		if (destination.size()) return destination.at(0);

		return std::string();
	}

	std::string FileOptions::SaveFile(const char* filter)
	{
        // Set verbosity to true
        pfd::settings::verbose(true);

        // File open
		auto destination = pfd::save_file("Choose files to save", DEFAULT_PATH,
                                  {filter},
                                  pfd::opt::none).result();
		if (destination.size()) return destination;

		return std::string();
	}

}
