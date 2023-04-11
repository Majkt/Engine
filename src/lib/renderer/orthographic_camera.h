#ifndef MAJKT_RENDERER_ORTHOGRAPHIC_CAMERA_H_
#define MAJKT_RENDERER_ORTHOGRAPHIC_CAMERA_H_

#include <glm/glm.hpp>

namespace majkt {

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return position_; }
		void SetPosition(const glm::vec3& position) { position_ = position; RecalculateViewMatrix(); }

		float GetRotation() const { return rotation_; }
		void SetRotation(float rotation) { rotation_ = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return projection_matrix_; }
		const glm::mat4& GetViewMatrix() const { return view_matrix_; }
		const glm::mat4& GetViewProjectionMatrix() const { return view_projection_matrix_; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 projection_matrix_;
		glm::mat4 view_matrix_;
		glm::mat4 view_projection_matrix_;

		glm::vec3 position_ = { 0.0f, 0.0f, 0.0f };
		float rotation_ = 0.0f;
	};

} // namespace majkt

#endif  // MAJKT_RENDERER_ORTHOGRAPHIC_CAMERA_H_
