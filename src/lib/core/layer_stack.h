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

		auto begin() { return layers_.begin(); }
		auto end() { return layers_.end(); }
		auto rbegin() { return layers_.rbegin(); }
		auto rend() { return layers_.rend(); }

		auto begin() const { return layers_.begin(); }
		auto end() const { return layers_.end(); }
		auto rbegin() const { return layers_.rbegin(); }
		auto rend() const { return layers_.rend(); }
		
	private:
		std::vector<Layer*> layers_;
		unsigned int layer_insert_index_{0};
	};

} // namespace majkt

#endif  // MAJKT_ENGINE_LAYER_STACK_H_
