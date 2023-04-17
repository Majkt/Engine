#include "src/lib/renderer/perspective_camera.h"
#include "src/lib/debug/instrumentor.h"

#include <glm/gtc/matrix_transform.hpp>

namespace majkt {

	PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float nearClip, float farClip)
		: 	fov_(fov),
			aspect_ratio_(aspectRatio),
			near_clip_(nearClip),
			far_clip_(farClip), 
			projection_matrix_(glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip)), view_matrix_(1.0f)
	{
		MAJKT_PROFILE_FUNCTION();
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	void PerspectiveCamera::SetProjection(float fov, float aspectRatio, float nearClip, float farClip)
	{
		MAJKT_PROFILE_FUNCTION();
		projection_matrix_ = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}
	
	void PerspectiveCamera::RecalculateViewMatrix()
	{
		MAJKT_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position_) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0, 0, 1));

	    view_matrix_ = glm::inverse(transform);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

} // namespace majkt
