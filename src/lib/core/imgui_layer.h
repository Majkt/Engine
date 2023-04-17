#ifndef MAJKT_IMGUI_LAYER_H_
#define MAJKT_IMGUI_LAYER_H_

#include "src/lib/core/layer.h"
#include "src/lib/events/event.h"
#include "src/lib/events/key_events.h"
#include "src/lib/events/mouse_events.h"
#include "src/lib/events/application_events.h"


namespace majkt {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		
		void Begin();
		void End();
		void BlockEvents(bool block) { block_events_ = block; }
	private:
		bool block_events_{true};
		float time_{0.0};
	};

}

#endif  // MAJKT_IMGUI_LAYER_H_
