#ifndef MAJKT_CORE_FILE_OPTIONS_H_
#define MAJKT_CORE_FILE_OPTIONS_H_

#include <string>

namespace majkt
{
	class FileOptions
	{
	public:
		// These return empty strings if cancelled
		static std::string OpenFile(const char* filter);
		static std::string SaveFile(const char* filter);
	};
} // namespace majkt

#endif  // MAJKT_CORE_FILE_OPTIONS_H_

