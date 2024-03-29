#ifndef MAJKT_ENGINE_LAYER_H_
#define MAJKT_ENGINE_LAYER_H_

#include "src/lib/core/base_export.h"
#include "src/lib/core/timestep.h"
#include "src/lib/events/event.h"

#include <string>

namespace majkt 
{
	class Layer
	{
	public:
		Layer(const std::string& debugName = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate(Timestep timestep) {}
		virtual void OnImGuiRender() {}
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetName() const { return debug_name_; }
	protected:
		std::string debug_name_;
	};

} // namespace majkt

#endif  // MAJKT_ENGINE_LAYER_H_
