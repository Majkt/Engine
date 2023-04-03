#include "src/lib/core/layer_stack.h"

namespace majkt {

	LayerStack::LayerStack()
	{	
	}

	LayerStack::~LayerStack()
	{
		for (Layer* layer : layers_) 
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::PushLayer(Layer* layer)
	{
		layers_.emplace(layers_.begin() + layer_insert_index_, layer);
		layer_insert_index_++;
		layer->OnAttach();
	}

	void LayerStack::PushOverlay(Layer* overlay)
	{
		layers_.emplace_back(overlay);
		overlay->OnAttach();
	}

	void LayerStack::PopLayer(Layer* layer)
	{
		auto it = std::find(layers_.begin(), layers_.end(), layer);
		if (it != layers_.end())
		{
			layers_.erase(it);
			layer_insert_index_--;
			layer->OnDetach();
		}
	}

	void LayerStack::PopOverlay(Layer* overlay)
	{
		auto it = std::find(layers_.begin(), layers_.end(), overlay);
		if (it != layers_.end())
		{
			layers_.erase(it);
			overlay->OnDetach();
		}
	}

} // namespace majkt
