#include "src/lib/core/uuid.h"

#include <random>
#include <unordered_map>
#include <cstdint>

namespace majkt {

	Uuid::Uuid()
		: uuid_(generate_uuid())
	{
	}

	Uuid::Uuid(uint64_t uuid)
		: uuid_(uuid)
	{
	}

    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    static std::uniform_int_distribution<uint64_t> dis;

    uint64_t Uuid::generate_uuid() {
        // https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
        // Generate random bytes using a secure random number generator
        uint64_t uuid = dis(gen);

        // Set the version and variant bits
        uuid = (uuid & 0xFFFFFFFFFFFFFF0F) | 0x0000000000000040; // Version 4
        uuid = (uuid & 0x3FFFFFFFFFFFFFFF) | 0x8000000000000000; // Variant 1

        return uuid;
    }

} // namespace majkt
