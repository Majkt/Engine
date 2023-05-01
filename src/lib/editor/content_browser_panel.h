#ifndef MAJKT_PLATFORM_EDITOR_CONTENT_BROWSER_PANEL_H_
#define MAJKT_PLATFORM_EDITOR_CONTENT_BROWSER_PANEL_H_

#include <filesystem>
#include "src/lib/renderer/texture.h"

namespace majkt {

	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

		void OnImGuiRender();
	private:
		std::filesystem::path current_directory_;
        std::shared_ptr<Texture2D> directory_icon_;
		std::shared_ptr<Texture2D> file_icon_;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_EDITOR_CONTENT_BROWSER_PANEL_H_
