#ifndef MAJKT_ENGINE_LAYER_STACK_H_
#define MAJKT_ENGINE_LAYER_STACK_H_

#include "src/lib/core/base_export.h"
#include "src/lib/core/layer.h"
#include <vector>

namespace majkt 
{
	class LayerStack
	{
	public:
		LayerStack() = default;
		~LayerStack();

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* overlay);
		void PopLayer(Layer* layer);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return layers_.begin(); }
		std::vector<Layer*>::iterator end() { return layers_.end(); }
	private:
		std::vector<Layer*> layers_;
		unsigned int layer_insert_index_{0};
	};

} // namespace majkt

#endif  // MAJKT_ENGINE_LAYER_STACK_H_
