#ifndef MAJKT_ENGINE_LAYER_STACK_H_
#define MAJKT_ENGINE_LAYER_STACK_H_

#include "src/lib/core/base_export.h"
#include "src/lib/core/layer.h"
#include <vector>

namespace majkt 
{
	class MAJKT_BASE_EXPORT LayerStack
	{
	public:
		LayerStack();
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers_.begin(); }
		std::vector<Layer*>::iterator end() { return layers_.end(); }
	private:
		std::vector<Layer*> layers_;
		std::vector<Layer*>::iterator layer_insert_;
	};

} // namespace majkt

#endif  // MAJKT_ENGINE_LAYER_STACK_H_
