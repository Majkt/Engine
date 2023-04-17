#ifndef MAJKT_RENDERER_PERSPECTIVE_CAMERA_CONTROLLER_H_
#define MAJKT_RENDERER_PERSPECTIVE_CAMERA_CONTROLLER_H_

#include "src/lib/renderer/perspective_camera.h"
#include "src/lib/core/timestep.h"

#include "src/lib/events/application_events.h"
#include "src/lib/events/mouse_events.h"

namespace majkt {
	class PerspectiveCameraController
	{
	public:
		PerspectiveCameraController(float aspectRatio, bool rotation = false);

		void OnUpdate(Timestep ts);
		void OnEvent(Event& e);

		void OnResize(float width, float height);
		PerspectiveCamera& GetCamera() { return camera_; }
		const PerspectiveCamera& GetCamera() const { return camera_; }
	private:
		float GetZoomLevel() const { return zoom_level_; }
		void SetZoomLevel(float level) { zoom_level_ = level; }
		bool OnMouseScrolled(MouseScrolledEvent& e);
		bool OnWindowResized(WindowResizeEvent& e);
	private:
        float aspect_ratio_;
		float zoom_level_ = 1.0f;
		PerspectiveCamera camera_;

		bool rotation_;

		glm::vec3 camera_position_ = { 0.0f, 0.0f, 3.0f };
		float camera_rotation_ = 0.0f;
		float camera_translation_speed_ = 5.0f, camera_rotation_speed_ = 180.0f;
	};

} // namespace majkt

#endif  // MAJKT_RENDERER_PERSPECTIVE_CAMERA_CONTROLLER_H_
