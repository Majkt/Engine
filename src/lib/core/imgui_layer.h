#ifndef MAJKT_IMGUI_LAYER_H_
#define MAJKT_IMGUI_LAYER_H_

#include "src/lib/core/layer.h"
#include "src/lib/events/event.h"
#include "src/lib/events/key_events.h"
#include "src/lib/events/mouse_events.h"
#include "src/lib/events/application_events.h"


namespace majkt {

	class MAJKT_BASE_EXPORT ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();
	private:
		float time_{0.0};
	};

}

#endif  // MAJKT_IMGUI_LAYER_H_
