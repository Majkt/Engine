#include "src/lib/core/application.h"
#include "src/lib/events/application_events.h"
#include "src/lib/core/window.h"
#include "src/lib/core/layer.h"
#include "src/lib/renderer/shader.h"

// #include <glad/glad.h>
// #include "GLFW/glfw3.h"
#include "src/lib/renderer/renderer.h"

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

		vertex_array_.reset(VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};


		std::shared_ptr<VertexBuffer> vertexBuffer;
		vertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "array_position_" },
			{ ShaderDataType::Float4, "array_color_" }
		};
		vertexBuffer->SetLayout(layout);
		vertex_array_->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<IndexBuffer> indexBuffer;
		indexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertex_array_->SetIndexBuffer(indexBuffer);

		square_va_.reset(VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f
		};

		std::shared_ptr<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ ShaderDataType::Float3, "array_position_" }
		});
		square_va_->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		square_va_->SetIndexBuffer(squareIB);

		const std::string vertex_src = R"(
			#version 410 core
			
			layout(location = 0) in vec3 array_position_;
			layout(location = 1) in vec4 array_color_;
			out vec3 vertex_position_;
			out vec4 vertex_color_;
			void main()
			{
				vertex_position_ = array_position_;
				vertex_color_ = array_color_;
				gl_Position = vec4(array_position_, 1.0);	
			}
		)";

		const std::string fragment_src = R"(
			#version 410 core
			
			layout(location = 0) out vec4 color;
			in vec3 vertex_position_;
			in vec4 vertex_color_;
			void main()
			{
				color = vec4(vertex_position_ * 0.5 + 0.5, 1.0);
				color = vertex_color_;
			}
		)";

		shader_.reset(new Shader(vertex_src, fragment_src));

		std::string blue_shader_vertex_src_ = R"(
			#version 410 core
			
			layout(location = 0) in vec3 array_position_;
			out vec3 vertex_position_;
			void main()
			{
				vertex_position_ = array_position_;
				gl_Position = vec4(array_position_, 1.0);	
			}
		)";

		std::string blue_shader_fragment_src_ = R"(
			#version 410 core
			
			layout(location = 0) out vec4 color;
			in vec3 vertex_position_;
			void main()
			{
				color = vec4(0.2, 0.3, 0.8, 1.0);
			}
		)";

		blue_shader_.reset(new Shader(blue_shader_vertex_src_, blue_shader_fragment_src_));
	}

    void Application::Run()
    {
        while (running_){
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			Renderer::BeginScene();

			blue_shader_->Bind();
			Renderer::Submit(square_va_);

			shader_->Bind();
			Renderer::Submit(vertex_array_);

			Renderer::EndScene();

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
