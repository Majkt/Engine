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
#include <unordered_map>

namespace majkt {

	class Uuid
	{
	public:
		uint64_t generate_uuid();  
	
		Uuid();
		Uuid(uint64_t uuid);
		Uuid(const Uuid&) = default;
        
		operator uint64_t() const { return uuid_; }
	private:		      
        uint64_t uuid_;
	};

} // namespace majkt

namespace std {

	template<>
	struct hash<majkt::Uuid>
	{
		std::size_t operator()(const majkt::Uuid& uuid) const
		{
			return hash<uint64_t>()((uint64_t)uuid);
		}
	};

}

#endif  // MAJKT_CORE_UUID_H_

