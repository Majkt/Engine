#include "src/lib/core/orthographic_camera_controller.h"
#include "src/lib/core/input.h"
#include "src/lib/core/key_codes.h"
#include "src/lib/debug/instrumentor.h"

#include "absl/functional/bind_front.h"

namespace majkt {

	OrthographicCameraController::OrthographicCameraController(float aspectRatio, bool rotation)
		: aspect_ratio_(aspectRatio), camera_(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_), rotation_(rotation)
	{
	}

	void OrthographicCameraController::OnUpdate(Timestep ts)
	{
		MAJKT_PROFILE_FUNCTION();
		if (Input::IsKeyPressed(MAJKT_KEY_A))
		{
			camera_position_.x -= cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
			camera_position_.y -= sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
		}
		else if (Input::IsKeyPressed(MAJKT_KEY_D))
		{
			camera_position_.x += cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
			camera_position_.y += sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
		}
		if (Input::IsKeyPressed(MAJKT_KEY_W))
		{
			camera_position_.x += -sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
			camera_position_.y += cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
		}
		else if (Input::IsKeyPressed(MAJKT_KEY_S))
		{
			camera_position_.x -= -sin(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
			camera_position_.y -= cos(glm::radians(camera_rotation_)) * camera_translation_speed_ * ts;
		}

		if (rotation_)
		{
			if (Input::IsKeyPressed(MAJKT_KEY_Q))
				camera_rotation_ += camera_rotation_speed_ * ts;
			if (Input::IsKeyPressed(MAJKT_KEY_E))
				camera_rotation_ -= camera_rotation_speed_ * ts;
			if (camera_rotation_ > 180.0f)
				camera_rotation_ -= 360.0f;
			else if (camera_rotation_ <= -180.0f)
				camera_rotation_ += 360.0f;

			camera_.SetRotation(camera_rotation_);
		}

		camera_.SetPosition(camera_position_);

		camera_translation_speed_ = zoom_level_;
	}

	void OrthographicCameraController::OnEvent(Event& e)
	{
		MAJKT_PROFILE_FUNCTION();
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseScrolledEvent>(absl::bind_front(&OrthographicCameraController::OnMouseScrolled , this));
		dispatcher.Dispatch<WindowResizeEvent>(absl::bind_front(&OrthographicCameraController::OnWindowResized, this));
	}

	void OrthographicCameraController::OnResize(float width, float height)
	{
		aspect_ratio_ = width / height;
		camera_.SetProjection(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
	}

	bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& e)
	{
		MAJKT_PROFILE_FUNCTION();
		zoom_level_ -= e.GetYOffset() * 0.25f;
		zoom_level_ = std::max(zoom_level_, 0.25f);
		camera_.SetProjection(-aspect_ratio_ * zoom_level_, aspect_ratio_ * zoom_level_, -zoom_level_, zoom_level_);
		return false;
	}

	bool OrthographicCameraController::OnWindowResized(WindowResizeEvent& e)
	{
		MAJKT_PROFILE_FUNCTION();

		OnResize((float)e.GetWidth(), (float)e.GetHeight());
		return false;
	}

}
