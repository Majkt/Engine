#include "src/lib/renderer/orthographic_camera.h"
#include "src/lib/debug/instrumentor.h"

#include <glm/gtc/matrix_transform.hpp>

namespace majkt {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: projection_matrix_(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), view_matrix_(1.0f)
	{
		MAJKT_PROFILE_FUNCTION();
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		MAJKT_PROFILE_FUNCTION();
		projection_matrix_ = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}
	
	void OrthographicCamera::RecalculateViewMatrix()
	{
		MAJKT_PROFILE_FUNCTION();
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position_) *
			glm::rotate(glm::mat4(1.0f), glm::radians(rotation_), glm::vec3(0, 0, 1));

	    view_matrix_ = glm::inverse(transform);
		view_projection_matrix_ = projection_matrix_ * view_matrix_;
	}

} // namespace majkt
