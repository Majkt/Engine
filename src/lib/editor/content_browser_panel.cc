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

		// Set the number of columns for layout using ImGui
		ImGui::Columns(columnCount, 0, false);

		// Iterate through each directory entry in the current directory
		for (auto& directoryEntry : std::filesystem::directory_iterator(current_directory_))
		{
			// Extract the path and relative path from the directory entry
			const auto& path = directoryEntry.path();
			auto relativePath = std::filesystem::relative(path, asset_path_);
			
			std::string filenameString = relativePath.filename().string();
			
			// Push an identifier for ImGui using the filename string
			ImGui::PushID(filenameString.c_str());
			
			// Determine the appropriate icon based on whether the entry is a directory or file
			std::shared_ptr<Texture2D> icon = directoryEntry.is_directory() ? directory_icon_ : file_icon_;
			
			// Customize the button style to have no background color
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
			
			// Display an image button with the icon texture and specified thumbnail size
			ImGui::ImageButton((ImTextureID)icon->GetRendererID(), { thumbnailSize, thumbnailSize }, { 0, 1 }, { 1, 0 });
			
			if (ImGui::BeginDragDropSource())
			{
				std::wstring wideFilePath = relativePath.wstring();
				const wchar_t* itemPath = wideFilePath.c_str();
				
				// Set the drag and drop payload with the item path
				ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", itemPath, (wcslen(itemPath) + 1) * sizeof(wchar_t));
				ImGui::EndDragDropSource();
			}
			
			// Restore the button style color
			ImGui::PopStyleColor();
			
			// Check if the item is hovered and left mouse button is clicked
			if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			{
				if (directoryEntry.is_directory())
				{
					current_directory_ /= path.filename();
				}
			}
			
			ImGui::TextWrapped(filenameString.c_str());
			
			// Move to the next column for layout
			ImGui::NextColumn();
			
			ImGui::PopID();
		}

		// Reset the columns to a single column for subsequent content
		ImGui::Columns(1);

		// ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		// ImGui::SliderFloat("Padding", &padding, 0, 32);

		ImGui::End();
	}

} // namespace majkt