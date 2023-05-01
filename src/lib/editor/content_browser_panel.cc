#include "src/lib/editor/content_browser_panel.h"

#include "imgui.h"

#ifndef MAJKT_ENGINE_GET_DIR_H_
#define MAJKT_ENGINE_GET_DIR_H_

// For use by Majkt applications
#if defined(MAJKT_PLATFORM_WINDOWS)
	#define GetCurrentDir _getcwd
#else  
	#include <unistd.h>
	#define GetCurrentDir getcwd
#endif

#include <string>

inline std::string get_current_dir() {
    char buff[FILENAME_MAX]; //create string buffer to hold path
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

#endif // MAJKT_ENGINE_GET_DIR_H_

namespace majkt {

	extern const std::filesystem::path asset_path_{get_current_dir() + "/src/majkt_editor/assets/"};

	ContentBrowserPanel::ContentBrowserPanel()
		: current_directory_(asset_path_)
	{
        directory_icon_ = Texture2D::Create(get_current_dir() + "/src/majkt_editor/assets/editor/folder.png");
		file_icon_ = Texture2D::Create(get_current_dir() + "/src/majkt_editor/assets/editor/file.png");
	}

	void ContentBrowserPanel::OnImGuiRender()
	{
		ImGui::Begin("Content Browser", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);

		if (current_directory_ != std::filesystem::path(asset_path_))
		{
			if (ImGui::Button("<-"))
			{
				current_directory_ = current_directory_.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 75.0f;
		float cellSize = thumbnailSize + padding;

		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& directoryEntry : std::filesystem::directory_iterator(current_directory_))
		{
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, asset_path_);
			std::string filenameString = relativePath.filename().string();
			
            ImGui::PushID(filenameString.c_str());
            std::shared_ptr<Texture2D> icon = directoryEntry.is_directory() ? directory_icon_ : file_icon_;
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
            if (ImGui::BeginDragDropSource())
			{
                std::wstring wideFilePath = relativePath.wstring();
                const wchar_t* itemPath = wideFilePath.c_str();

				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}

			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
            {
                if (directoryEntry.is_directory())
                {
                    current_directory_ /= path.filename();
                }
            }  
            ImGui::TextWrapped(filenameString.c_str());
			ImGui::NextColumn(); 
            ImGui::PopID();
		}

		ImGui::Columns(1);

		// ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		// ImGui::SliderFloat("Padding", &padding, 0, 32);

		ImGui::End();
	}

} // namespace majkt