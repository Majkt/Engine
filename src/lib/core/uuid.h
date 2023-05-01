#ifndef MAJKT_CORE_UUID_H_
#define MAJKT_CORE_UUID_H_

#include <iostream>
#include <iomanip>
#include <random>
#include <chrono>
#include <cstring>
#include <sstream>
#include <cstdint>
#include <cstdio>
#include <cinttypes>

namespace majkt {

	class Uuid
	{
	public:
		Uuid();
		Uuid(uint64_t uuid);
		Uuid(const Uuid&) = default;
        
		operator std::string() { return std::to_string(uuid_); }
	private:
        uint64_t generate_uuid();  
		      
        uint64_t uuid_;
	};

} // namespace majkt

#endif  // MAJKT_CORE_UUID_H_

