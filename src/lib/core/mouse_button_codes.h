#ifndef MAJKT_CORE_MOUSE_BUTTON_CODES_H_
#define MAJKT_CORE_MOUSE_BUTTON_CODES_H_

#include <iostream>
#include <memory>

namespace majkt
{
	using MouseCode = uint16_t;

	namespace Mouse
	{
		enum : MouseCode
		{
			// From glfw3.h
			Button0                = 0,
			Button1                = 1,
			Button2                = 2,
			Button3                = 3,
			Button4                = 4,
			Button5                = 5,
			Button6                = 6,
			Button7                = 7,

			ButtonLast             = Button7,
			ButtonLeft             = Button0,
			ButtonRight            = Button1,
			ButtonMiddle           = Button2
		};
	} // namespace Mouse

} // namespace majkt

#endif  // MAJKT_CORE_MOUSE_BUTTON_CODES_H_
