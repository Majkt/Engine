#ifndef SANDBOX_EXAMPLE_LAYER_H
#define SANDBOX_EXAMPLE_LAYER_H

#include "src/lib/majkt_export.h"

class RayCastLayer : public majkt::Layer
{
public:
	RayCastLayer();
	virtual ~RayCastLayer() = default;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnUpdate(majkt::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(majkt::Event& e) override;
private:
	majkt::PerspectiveCameraController camera_controller_;

	std::shared_ptr<majkt::VertexArray> square_va_;
	std::shared_ptr<majkt::Shader> flat_color_shader_;
	std::shared_ptr<majkt::Texture2D> checker_board_texture_;
	std::shared_ptr<majkt::Texture2D> style_texture_;
	glm::vec4 left_square_color_ = { 0.2f, 0.3f, 0.8f, 1.0f };
	glm::vec4 right_square_color_ = { 0.8f, 0.2f, 0.3f, 1.0f };
};

#endif // SANDBOX_EXAMPLE_LAYER_H
