#ifndef MAJKT_ENGINE_APLICATION_H_
#define MAJKT_ENGINE_APLICATION_H_

#include "src/lib/core/base_export.h"

namespace Majkt 
{
	class MAJKT_BASE_EXPORT Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
    };

	// To be defined in CLIENT
	Application* CreateApplication();

} // namespace Majkt

#endif  // MAJKT_ENGINE_APLICATION_H_
