#include "src/lib/scene/scene_camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace majkt {

	SceneCamera::SceneCamera()
	{
		RecalculateProjection();
	}

	void SceneCamera::SetOrthographic(float size, float nearClip, float farClip)
	{
		orthographic_size_ = size;
		orthographic_near_ = nearClip;
		orthographic_far_ = farClip;
		RecalculateProjection();
	}

	void SceneCamera::SetViewportSize(uint32_t width, uint32_t height)
	{
		aspect_ratio_ = (float)width / (float)height;
		RecalculateProjection();
	}

	void SceneCamera::RecalculateProjection()
	{
		float orthoLeft = -orthographic_size_ * aspect_ratio_ * 0.5f;
		float orthoRight = orthographic_size_ * aspect_ratio_ * 0.5f;
		float orthoBottom = -orthographic_size_ * 0.5f;
		float orthoTop = orthographic_size_ * 0.5f;

		projection_ = glm::ortho(orthoLeft, orthoRight,
			orthoBottom, orthoTop, orthographic_near_, orthographic_far_);
	}

} // namespace majkt
