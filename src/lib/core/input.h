#ifndef MAJKT_CORE_INPUT_H_
#define MAJKT_CORE_INPUT_H_

#include "src/lib/core/base_export.h"
#include "src/lib/core/key_codes.h"
#include "src/lib/core/mouse_button_codes.h"

#include <glm/glm.hpp>
#include <utility>

namespace majkt
{
    // Defines the interface for input, which should be implemented for each platform.
	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

} // namespace majkt

#endif  // MAJKT_CORE_INPUT_H_

