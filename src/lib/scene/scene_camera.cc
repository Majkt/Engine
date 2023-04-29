#include "src/lib/scene/scene_camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace majkt {

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		projection_type_ = ProjectionType::Orthographic;
		orthographic_size_ = size;
		orthographic_near_ = nearClip;
		orthographic_far_ = farClip;
		RecalculateProjection();
	}


	void SceneCamera::SetPerspective(float verticalFOV, float nearClip, float farClip)
	{
		projection_type_ = ProjectionType::Perspective;
		perspective_FOV_ = verticalFOV;
		perspective_near_ = nearClip;
		perspective_far_ = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		aspect_ratio_ = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		if (projection_type_ == ProjectionType::Perspective)
		{
			projection_ = glm::perspective(perspective_FOV_, aspect_ratio_, perspective_near_, perspective_far_);
		}
		else
		{
			float orthoLeft = -orthographic_size_ * aspect_ratio_ * 0.5f;
			float orthoRight = orthographic_size_ * aspect_ratio_ * 0.5f;
			float orthoBottom = -orthographic_size_ * 0.5f;
			float orthoTop = orthographic_size_ * 0.5f;

			projection_ = glm::ortho(orthoLeft, orthoRight,
				orthoBottom, orthoTop, orthographic_near_, orthographic_far_);
		}
	}

} // namespace majkt
