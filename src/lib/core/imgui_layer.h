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

		void SetIniPath(bool flush = false, std::string path = "", std::string project_uuid = "");

		void OnAttach() override;
		void OnDetach() override;
		virtual void OnEvent(Event& e) override;
		
		void Begin();
		void End();
		void BlockEvents(bool block) { block_events_ = block; }

		void SetDarkThemeColors();
	private:
		std::string ini_file_path_;
		struct InitData
		{
			std::string project_uuid_;
			bool flush_;
			std::string path_;

			InitData(const std::string& project_uuid = "",
						bool flush = false,
						const std::string& path = "")
				: project_uuid_(project_uuid), flush_(flush), path_(path)
			{}
		};
		InitData init_data_;
		
		void FlushIniToDisk();
		void SetDefaultIniPath(bool flush, std::string path);
		void SetProjectIniPath(const std::string &project_uuid, bool flush);
		bool block_events_{true};
		float time_{0.0};
	};

}

#endif  // MAJKT_IMGUI_LAYER_H_
