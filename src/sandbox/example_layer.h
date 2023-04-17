#ifndef SANDBOX_EXAMPLE_LAYER_H
#define SANDBOX_EXAMPLE_LAYER_H

#include "src/lib/majkt_export.h"

class ExampleLayer : public majkt::Layer
{
public:
	ExampleLayer();
	virtual ~ExampleLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(majkt::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(majkt::Event& e) override;
private:
	majkt::ShaderLibrary shader_library_;
	std::shared_ptr<majkt::Shader> shader_;
	std::shared_ptr<majkt::VertexArray> vertex_array_;

	std::shared_ptr<majkt::Shader> flat_color_shader_;
	std::shared_ptr<majkt::VertexArray> square_va_;
	std::shared_ptr<majkt::Texture2D> texture_, blended_texture_;

	majkt::OrthographicCameraController camera_controller_;
	glm::vec3 square_color_ = { 0.2f, 0.3f, 0.8f };
};

#endif // SANDBOX_EXAMPLE_LAYER_H
