#ifndef MAJKT_PLATFORM_RENDERER_CAMERA_H_
#define MAJKT_PLATFORM_RENDERER_CAMERA_H_

#include <glm/glm.hpp>

namespace majkt {

	class Camera
	{
	public:
		Camera() = default;
		Camera(const glm::mat4& projection)
			: projection_(projection) {}

		virtual ~Camera() = default;

		const glm::mat4& GetProjection() const { return projection_; }
	protected:
		glm::mat4 projection_{glm::mat4(1.0f)};
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_RENDERER_CAMERA_H_
