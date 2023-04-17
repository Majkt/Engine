#ifndef MAJKT_CORE_MOUSE_BUTTON_CODES_H_
#define MAJKT_CORE_MOUSE_BUTTON_CODES_H_

#include <iostream>

namespace majkt
{
	typedef enum class MouseCode : uint16_t
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
	} Mouse;
	
	inline std::ostream& operator<<(std::ostream& os, MouseCode mouseCode)
	{
		os << static_cast<int32_t>(mouseCode);
		return os;
	}
}

#define MAJKT_MOUSE_BUTTON_0      ::majkt::Mouse::Button0
#define MAJKT_MOUSE_BUTTON_1      ::majkt::Mouse::Button1
#define MAJKT_MOUSE_BUTTON_2      ::majkt::Mouse::Button2
#define MAJKT_MOUSE_BUTTON_3      ::majkt::Mouse::Button3
#define MAJKT_MOUSE_BUTTON_4      ::majkt::Mouse::Button4
#define MAJKT_MOUSE_BUTTON_5      ::majkt::Mouse::Button5
#define MAJKT_MOUSE_BUTTON_6      ::majkt::Mouse::Button6
#define MAJKT_MOUSE_BUTTON_7      ::majkt::Mouse::Button7
#define MAJKT_MOUSE_BUTTON_LAST   ::majkt::Mouse::ButtonLast
#define MAJKT_MOUSE_BUTTON_LEFT   ::majkt::Mouse::ButtonLeft
#define MAJKT_MOUSE_BUTTON_RIGHT  ::majkt::Mouse::ButtonRight
#define MAJKT_MOUSE_BUTTON_MIDDLE ::majkt::Mouse::ButtonMiddle

#endif  // MAJKT_CORE_MOUSE_BUTTON_CODES_H_
