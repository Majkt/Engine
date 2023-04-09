#include "src/lib/core/application.h"
#include "src/lib/events/application_events.h"
#include "src/lib/core/window.h"
#include "src/lib/core/layer.h"
#include "src/lib/renderer/shader.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

#include <glog/logging.h>
#include "glog/stl_logging.h"
#include <iostream>

#include "absl/functional/bind_front.h"

namespace majkt
{
	Application* Application::instance_ = nullptr;

    Application::Application()
    {
		if (instance_){
			LOG(WARNING) << instance_ <<  " Application already exists!";
		}
		instance_ = this;
        window_ = std::unique_ptr<Window>(Window::Create());
        window_->SetEventCallback(absl::bind_front(&Application::OnEvent, this));

		imgui_layer_ = new ImGuiLayer();
		PushOverlay(imgui_layer_);

		glGenVertexArrays(1, &vertex_array_);
		glBindVertexArray(vertex_array_);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		vertex_buffer_.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		glEnableVertexAttribArray(0);

		uint32_t indices[3] = { 0, 1, 2 };
		index_buffer_.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		const std::string vertex_src = R"(
			#version 410 core
			
			layout(location = 0) in vec3 array_position_;
			out vec3 vertex_position_;
			void main()
			{
				vertex_position_ = array_position_;
				gl_Position = vec4(array_position_, 1.0);	
			}
		)";

		const std::string fragment_src = R"(
			#version 410 core
			
			layout(location = 0) out vec4 color;
			in vec3 vertex_position_;
			void main()
			{
				color = vec4(vertex_position_ * 0.5 + 0.5, 1.0);
			}
		)";

		shader_.reset(new Shader(vertex_src, fragment_src));
	}

    void Application::Run()
    {
        while (running_){
			// glClearColor(.3, .3, .7, 1);
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			shader_->Bind();	
			glBindVertexArray(vertex_array_);
			glDrawElements(GL_TRIANGLES, index_buffer_->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : layer_stack_)
				layer->OnUpdate();

			imgui_layer_->Begin();
			for (Layer* layer : layer_stack_)
				layer->OnImGuiRender();
			imgui_layer_->End();

			window_->OnUpdate();
        }
    }

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(absl::bind_front(&Application::OnWindowClose, this));

		for (auto it = layer_stack_.end(); it != layer_stack_.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled_)
				break;
		}
	}

	void Application::PushLayer(Layer* layer)
	{
		layer_stack_.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
		layer_stack_.PushOverlay(layer);
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running_ = false;
		return true;
	}

} // namespace majkt
