#ifndef MAJKT_CORE_BASE_EXPORT_H_
#define MAJKT_CORE_BASE_EXPORT_H_

#include "src/lib/core/platform_detection.h"

#if defined(MAJKT_PLATFORM_WINDOWS)

	#if defined(WIN32)

		#if defined(MAJKT_BASE_IMPLEMENTATION)
			#define MAJKT_BASE_EXPORT __declspec(dllexport)
		#else
			#define MAJKT_BASE_EXPORT __declspec(dllimport)
		#endif  // defined(MAJKT_BASE_IMPLEMENTATION)

	#else  // defined(WIN32)
		#if defined(MAJKT_BASE_IMPLEMENTATION)
			#define MAJKT_BASE_EXPORT __attribute__((visibility("default")))
		#else
			#define MAJKT_BASE_EXPORT
		#endif
	#endif

#elif defined(MAJKT_PLATFORM_MACOS)
	#define MAJKT_BASE_EXPORT

#else  
	#define MAJKT_BASE_EXPORT
#endif

#endif  // MAJKT_CORE_BASE_EXPORT_H_
