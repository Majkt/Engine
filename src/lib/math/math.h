#ifndef MAJKT_MATH_H_
#define MAJKT_MATH_H_

#include <glm/glm.hpp>

namespace majkt
{
	namespace math
	{
		bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale);
	} // namespace math
} // namespace majkt

#endif  // MAJKT_MATH_H_

