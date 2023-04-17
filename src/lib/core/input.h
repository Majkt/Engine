#ifndef MAJKT_CORE_INPUT_H_
#define MAJKT_CORE_INPUT_H_

#include "src/lib/core/base_export.h"
#include <utility>

namespace majkt
{
    // Defines the interface for input, which should be implemented for each platform.
	class Input
	{
	protected:
		Input() = default;
	public:
		Input(const Input&) = delete;
		Input& operator=(const Input&) = delete;
		
		inline static bool IsKeyPressed(int keycode) { return instance_->IsKeyPressedImpl(keycode); }

		inline static bool IsMouseButtonPressed(int button) { return instance_->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return instance_->GetMousePositionImpl(); }
		inline static float GetMouseX() { return instance_->GetMouseXImpl(); }
		inline static float GetMouseY() { return instance_->GetMouseYImpl(); }
	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;

		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private:
        // The input instance does is owned by this class, instead its a reference to the static instance.
		static std::unique_ptr<Input> instance_;
	};

} // namespace majkt

#endif  // MAJKT_CORE_INPUT_H_

