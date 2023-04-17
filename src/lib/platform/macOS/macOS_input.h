#ifndef MAJKT_PLATFORM_MACOS_INPUT_H_
#define MAJKT_PLATFORM_MACOS_INPUT_H_

#include "src/lib/core/input.h"

namespace majkt {

	class MacOSInput : public Input
	{
	protected:
		bool IsKeyPressedImpl(int keycode) override;
		bool IsMouseButtonPressedImpl(int button) override;
		std::pair<float, float> GetMousePositionImpl() override;
		float GetMouseXImpl() override;
		float GetMouseYImpl() override;
	};

} // namespace majkt

#endif  // MAJKT_PLATFORM_MACOS_INPUT_H_
