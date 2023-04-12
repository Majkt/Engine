#include "src/lib/majkt_export.h"
#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public majkt::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), camera_(-1.6f, 1.6f, -0.9f, 0.9f), camera_position_(0.0f)
	{
		vertex_array_.reset(majkt::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		std::shared_ptr<majkt::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(majkt::VertexBuffer::Create(vertices, sizeof(vertices)));
		majkt::BufferLayout layout = {
			{ majkt::ShaderDataType::Float3, "position_" },
			{ majkt::ShaderDataType::Float4, "color_" }
		};
		vertexBuffer->SetLayout(layout);
		vertex_array_->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<majkt::IndexBuffer> indexBuffer;
		indexBuffer.reset(majkt::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		vertex_array_->SetIndexBuffer(indexBuffer);

		square_va_.reset(majkt::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		
		std::shared_ptr<majkt::VertexBuffer> squareVB;
		squareVB.reset(majkt::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ majkt::ShaderDataType::Float3, "position_" }
		});
		square_va_->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<majkt::IndexBuffer> squareIB;
		squareIB.reset(majkt::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		square_va_->SetIndexBuffer(squareIB);

		std::string vertex_src = R"(
			#version 410 core
			
			layout(location = 0) in vec3 array_position_;
			layout(location = 1) in vec4 array_color_;

			uniform mat4 view_projection_;
			uniform mat4 transform_;

			out vec3 vertex_position_;
			out vec4 vertex_color_;
			void main()
			{
				vertex_position_ = array_position_;
				vertex_color_ = array_color_;
				gl_Position = view_projection_ * transform_ * vec4(array_position_, 1.0);	
			}
		)";

		std::string fragment_src = R"(
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

		shader_.reset(new majkt::Shader(vertex_src, fragment_src));

		std::string blue_shader_vertex_src_ = R"(
			#version 410 core
			
			layout(location = 0) in vec3 array_position_;
			uniform mat4 view_projection_;
			uniform mat4 transform_;

			out vec3 vertex_position_;
			void main()
			{
				vertex_position_ = array_position_;
				gl_Position = view_projection_ * transform_ * vec4(array_position_, 1.0);	
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

		blue_shader_.reset(new majkt::Shader(blue_shader_vertex_src_, blue_shader_fragment_src_));
	}
	void OnUpdate(majkt::Timestep timestep) override
	{
		if (majkt::Input::IsKeyPressed(MAJKT_KEY_LEFT))
			camera_position_.x -= camera_move_speed_ * timestep;
		else if (majkt::Input::IsKeyPressed(MAJKT_KEY_RIGHT))
			camera_position_.x += camera_move_speed_ * timestep;

		if (majkt::Input::IsKeyPressed(MAJKT_KEY_UP))
			camera_position_.y += camera_move_speed_ * timestep;
		else if (majkt::Input::IsKeyPressed(MAJKT_KEY_DOWN))
			camera_position_.y -= camera_move_speed_ * timestep;

		if (majkt::Input::IsKeyPressed(MAJKT_KEY_A))
			camera_rotation_ += camera_rotation_speed_ * timestep;
		if (majkt::Input::IsKeyPressed(MAJKT_KEY_D))
			camera_rotation_ -= camera_rotation_speed_ * timestep;

		majkt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		majkt::RenderCommand::Clear();

		camera_.SetPosition(camera_position_);
		camera_.SetRotation(camera_rotation_);

		majkt::Renderer::BeginScene(camera_);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				majkt::Renderer::Submit(blue_shader_, square_va_, transform);
			}
		}
		majkt::Renderer::Submit(shader_, vertex_array_);

		majkt::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
	}

	void OnEvent(majkt::Event& event) override
	{
	}
private:
	std::shared_ptr<majkt::Shader> shader_;
	std::shared_ptr<majkt::VertexArray> vertex_array_;

	std::shared_ptr<majkt::Shader> blue_shader_;
	std::shared_ptr<majkt::VertexArray> square_va_;

	majkt::OrthographicCamera camera_;
	glm::vec3 camera_position_;
	float camera_move_speed_{5.0f};
	float camera_rotation_{0.0f};
	float camera_rotation_speed_{180.0f};
};

class Sandbox : public majkt::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{
	}
};

majkt::Application* majkt::CreateApplication()
{
	return new Sandbox();
}
