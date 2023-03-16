#ifndef MAJKT_ENGINE_APLICATION_H_
#define MAJKT_ENGINE_APLICATION_H_

#include "src/lib/core/base_export.h"
#include "src/lib/events/event.h"
#include "src/lib/core/window.h"

#include <memory>

namespace majkt 
{
	class MAJKT_BASE_EXPORT Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> window_;
		bool running_{true};
    };

	// To be defined in CLIENT
	Application* CreateApplication();

} // namespace Majkt

#endif  // MAJKT_ENGINE_APLICATION_H_
