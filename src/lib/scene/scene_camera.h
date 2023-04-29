#ifndef MAJKT_SCENE_SCENECAMERA_H_
#define MAJKT_SCENE_SCENECAMERA_H_

#include "src/lib/renderer/camera.h"

namespace majkt {

	class SceneCamera : public Camera
	{
	public:
		enum class ProjectionType { Perspective = 0, Orthographic = 1 };
		
		SceneCamera();
		virtual ~SceneCamera() = default;

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetPerspective(float verticalFOV, float nearClip, float farClip);
		void SetViewportSize(uint32_t width, uint32_t height);

		float GetPerspectiveVerticalFOV() const { return perspective_FOV_; }
		void SetPerspectiveVerticalFOV(float verticalFov) { perspective_FOV_ = verticalFov; RecalculateProjection(); }
		float GetPerspectiveNearClip() const { return perspective_near_; }
		void SetPerspectiveNearClip(float nearClip) { perspective_near_ = nearClip; RecalculateProjection(); }
		float GetPerspectiveFarClip() const { return perspective_far_; }
		void SetPerspectiveFarClip(float farClip) { perspective_far_ = farClip; RecalculateProjection(); }

		float GetOrthographicSize() const { return orthographic_size_; }
		void SetOrthographicSize(float size) { orthographic_size_ = size; RecalculateProjection(); }

		float GetOrthographicNearClip() const { return orthographic_near_; }
		void SetOrthographicNearClip(float nearClip) { orthographic_near_ = nearClip; RecalculateProjection(); }
		float GetOrthographicFarClip() const { return orthographic_far_; }
		void SetOrthographicFarClip(float farClip) { orthographic_far_ = farClip; RecalculateProjection(); }

		ProjectionType GetProjectionType() const { return projection_type_; }
		void SetProjectionType(ProjectionType type) { projection_type_ = type; RecalculateProjection(); }

	private:
		void RecalculateProjection();

		ProjectionType projection_type_ = ProjectionType::Orthographic;

		float perspective_FOV_ = glm::radians(45.0f);
		float perspective_near_ = 0.01f, perspective_far_ = 1000.0f;
		
		float orthographic_size_ = 10.0f;
		float orthographic_near_ = -1.0f, orthographic_far_ = 1.0f;

		float aspect_ratio_ = 0.0f;
	};

} // namespace majkt

#endif  // MAJKT_SCENE_SCENECAMERA_H_
