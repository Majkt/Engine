#include "src/lib/core/layer.h"
#include <string>

namespace majkt {

	Layer::Layer(const std::string& debugName)
		: debug_name_(debugName)
	{
	}

	Layer::~Layer()
	{
	}

} // namespace majkt
