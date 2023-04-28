#include "src/lib/core/application.h"
#include "src/lib/core/imgui_layer.h"
#include "src/lib/debug/instrumentor.h"

#include "imgui.h"
#include "third_party/imgui/backends/imgui_impl_glfw.h"
#include "third_party/imgui/imgui_internal.h"
#include "third_party/imgui/backends/imgui_impl_opengl3.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include "absl/functional/bind_front.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>


namespace majkt {

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	void ImGuiLayer::FlushIniToDisk()
	{
		ImGuiIO &io = ImGui::GetIO();
		ImGui::SaveIniSettingsToDisk(io.IniFilename);
	}

	void ImGuiLayer::SetDefaultIniPath(bool flush, std::string path)
	{
		if (flush) FlushIniToDisk();

		LOG(INFO) << get_current_dir();
		if (!path.empty()) ini_file_path_ = path;
		else ini_file_path_ = get_current_dir() + "/imgui.ini";
		ImGuiIO &io = ImGui::GetIO();
		io.IniFilename = ini_file_path_.c_str();

		ImGui::ClearIniSettings();
		ImGui::LoadIniSettingsFromDisk(io.IniFilename);
	}

	void ImGuiLayer::SetProjectIniPath( const std::string &project_uuid, bool flush )
	{
		if (flush) FlushIniToDisk();

		LOG(INFO) << get_current_dir() ;
		ini_file_path_ = get_current_dir()  + "/"+ project_uuid + ".ini";
		ImGuiIO &io = ImGui::GetIO();
		io.IniFilename = ini_file_path_.c_str();

		ImGui::ClearIniSettings();
		ImGui::LoadIniSettingsFromDisk(io.IniFilename);
	}

	void ImGuiLayer::SetIniPath(bool flush, std::string path, std::string project_uuid)
	{
		init_data_.flush_ = flush;
		init_data_.path_ = path;
		init_data_.project_uuid_ = project_uuid;
		LOG(INFO) << init_data_.project_uuid_ << "   " << init_data_.flush_ << "   " << init_data_.path_;
		if (!init_data_.project_uuid_.empty()) 
		{
			SetProjectIniPath(init_data_.project_uuid_, init_data_.flush_);
		} else 
		{
			SetDefaultIniPath(init_data_.flush_, init_data_.path_);
		}

	}

	void ImGuiLayer::OnAttach()
	{
		MAJKT_PROFILE_FUNCTION();

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
    	ImGuiIO& io = ImGui::GetIO(); (void)io;
	    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;
		
		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		// ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");

		// Load Fonts
		// - If no fonts are loaded, dear imgui will use the default font. You can also load multiple fonts and use ImGui::PushFont()/PopFont() to select them.
		// - AddFontFromFileTTF() will return the ImFont* so you can store it if you need to select the font among multiple.
		// - If the file cannot be loaded, the function will return NULL. Please handle those errors in your application (e.g. use an assertion, or display an error and quit).
		// - The fonts will be rasterized at a given size (w/ oversampling) and stored into a texture when calling ImFontAtlas::Build()/GetTexDataAsXXXX(), which ImGui_ImplXXXX_NewFrame below will call.
		// - Use '#define IMGUI_ENABLE_FREETYPE' in your imconfig file to use Freetype for higher quality font rendering.
		// - Read 'docs/FONTS.md' for more instructions and details.
		// - Remember that in C/C++ if you want to include a backslash \ in a string literal you need to write a double backslash \\ !
		//io.Fonts->AddFontDefault();
		//io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 18.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/DroidSans.ttf", 16.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Roboto-Medium.ttf", 16.0f);
		//io.Fonts->AddFontFromFileTTF("../../misc/fonts/Cousine-Regular.ttf", 15.0f);
		//ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\ArialUni.ttf", 18.0f, NULL, io.Fonts->GetGlyphRangesJapanese());
		//IM_ASSERT(font != NULL);
	}

	void ImGuiLayer::OnDetach()
	{
		MAJKT_PROFILE_FUNCTION();

		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		if (block_events_)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.handled_ |= e.IsInCategory(kEventCategoryMouse) & io.WantCaptureMouse;
			e.handled_ |= e.IsInCategory(kEventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		MAJKT_PROFILE_FUNCTION();
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		MAJKT_PROFILE_FUNCTION();
		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		ImGuiIO& io{ImGui::GetIO()}; (void)io;
		float time{(float)glfwGetTime()};
		io.DeltaTime = time_ > 0.0f ? (time - time_) : (1.0f / 60.0f);
		time_ = time;
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

} // namespace majkt
