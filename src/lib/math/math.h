#ifndef MAJKT_MATH_H_
#define MAJKT_MATH_H_

#include <glm/glm.hpp>

namespace majkt
{
	namespace math
	{
		bool DecomposeTransform(const glm::mat4& transform, glm::vec3& outTranslation, glm::vec3& outRotation, glm::vec3& outScale);
	} // namespace math
} // namespace majkt

#endif  // MAJKT_MATH_H_

