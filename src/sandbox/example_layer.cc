#include "src/sandbox/example_layer.h"
#include "src/lib/renderer/opengl_shader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

ExampleLayer::ExampleLayer()
	: Layer("Example"), camera_controller_(1280.0f / 720.0f, true)
{
	vertex_array_ = majkt::VertexArray::Create();

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

	square_va_ = majkt::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
	};

	std::shared_ptr<majkt::VertexBuffer> squareVB;
	squareVB.reset(majkt::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ majkt::ShaderDataType::Float3, "position_" },
		{ majkt::ShaderDataType::Float2, "texture_coord_" }
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

	shader_ = majkt::Shader::Create("vertex_position_color", vertex_src, fragment_src);

	std::string flat_color_shader_vertex_src = R"(
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

	std::string flat_color_shader_fragment_src = R"(
		#version 410 core
		
		layout(location = 0) out vec4 color;
		in vec3 vertex_position_;
			uniform vec3 color_;
		void main()
		{
			color = vec4(color_, 1.0);
		}
	)";

	flat_color_shader_ = majkt::Shader::Create("flat_color", flat_color_shader_vertex_src, flat_color_shader_fragment_src);
		
	auto texture_shader = shader_library_.Load(get_current_dir() + "/src/sandbox/assets/shaders/Texture.glsl");

	texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/sandbox/assets/textures/style.png");
	blended_texture_ = majkt::Texture2D::Create(get_current_dir() + "/src/sandbox/assets/textures/crown.png");
	
	std::dynamic_pointer_cast<majkt::OpenGLShader>(texture_shader)->Bind();
	std::dynamic_pointer_cast<majkt::OpenGLShader>(texture_shader)->UploadUniformInt("texture_", 0);
}

void ExampleLayer::OnAttach()
{
}

void ExampleLayer::OnDetach()
{
}

void ExampleLayer::OnUpdate(majkt::Timestep timestep)
{
	camera_controller_.OnUpdate(timestep);

	majkt::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	majkt::RenderCommand::Clear();

	majkt::Renderer::BeginScene(camera_controller_.GetCamera());

	glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

	std::dynamic_pointer_cast<majkt::OpenGLShader>(flat_color_shader_)->Bind();
	std::dynamic_pointer_cast<majkt::OpenGLShader>(flat_color_shader_)->UploadUniformFloat3("color_", square_color_);
	
	for (int y = 0; y < 20; y++)
	{
		for (int x = 0; x < 20; x++)
		{
			glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
			majkt::Renderer::Submit(flat_color_shader_, square_va_, transform);
		}
	}
	
	auto textureShader = shader_library_.Get("Texture");

	texture_->Bind();
	majkt::Renderer::Submit(textureShader, square_va_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
	
	blended_texture_->Bind();
	majkt::Renderer::Submit(textureShader, square_va_, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	// Triangle
	// majkt::Renderer::Submit(shader_, vertex_array_);

	majkt::Renderer::EndScene();
}

void ExampleLayer::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit3("Square Color", glm::value_ptr(square_color_));
	ImGui::End();
}

void ExampleLayer::OnEvent(majkt::Event& e) 
{
	camera_controller_.OnEvent(e);
}
