#ifndef MAJKT_PLATFORM_RENDERER_EDITOR_CAMERA_H_
#define MAJKT_PLATFORM_RENDERER_EDITOR_CAMERA_H_

#include "src/lib/renderer/camera.h"
#include "src/lib/events/event.h"
#include "src/lib/core/timestep.h"
#include "src/lib/events/mouse_events.h"

#include <utility>

namespace majkt {

	class EditorCamera : public Camera
	{
	public:
		EditorCamera() = default;
		EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		inline float GetDistance() const { return distance_; }
		inline void SetDistance(float distance) { distance_ = distance; }

		inline void SetViewportSize(float width, float height) { viewport_width_ = width; viewport_height_ = height; UpdateProjection(); }

		const glm::mat4& GetViewMatrix() const { return view_matrix_; }
		glm::mat4 GetViewProjection() const { return projection_ * view_matrix_; }

		glm::vec3 GetUpDirection() const;
		glm::vec3 GetRightDirection() const;
		glm::vec3 GetForwardDirection() const;
		const glm::vec3& GetPosition() const { return position_; }
		glm::quat GetOrientation() const;

		float GetPitch() const { return pitch_; }
		float GetYaw() const { return yaw_; }
	private:
		void UpdateProjection();
		void UpdateView();

		bool OnMouseScroll(MouseScrolledEvent& e);

		void MousePan(const glm::vec2& delta);
		void MouseRotate(const glm::vec2& delta);
		void MouseZoom(float delta);

		glm::vec3 CalculatePosition() const;

		std::pair<float, float> PanSpeed() const;
		float RotationSpeed() const;
		float ZoomSpeed() const;
	private:
		float FOV_{45.0}, aspect_ratio_{1.778}, near_clip_{0.1}, far_clip_{1000};

		glm::mat4 view_matrix_;
		glm::vec3 position_ = { 0.0f, 0.0f, 0.0f };
		glm::vec3 focal_point_ = { 0.0f, 0.0f, 0.0f };

		glm::vec2 initial_mouse_position_ = { 0.0f, 0.0f };

		float distance_{10.0};
		float pitch_{0.0}, yaw_{0.0f};

		float viewport_width_ = 1280, viewport_height_ = 720;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_EDITOR_CAMERA_H_
