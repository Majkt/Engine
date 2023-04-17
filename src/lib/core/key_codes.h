#ifndef MAJKT_CORE_KEY_CODES_H_
#define MAJKT_CORE_KEY_CODES_H_

#include <iostream>

namespace majkt
{
	typedef enum class KeyCode : uint16_t
	{
		// From glfw3.h
		Space               = 32,
		Apostrophe          = 39, /* ' */
		Comma               = 44, /* , */
		Minus               = 45, /* - */
		Period              = 46, /* . */
		Slash               = 47, /* / */

		D0                  = 48, /* 0 */
		D1                  = 49, /* 1 */
		D2                  = 50, /* 2 */
		D3                  = 51, /* 3 */
		D4                  = 52, /* 4 */
		D5                  = 53, /* 5 */
		D6                  = 54, /* 6 */
		D7                  = 55, /* 7 */
		D8                  = 56, /* 8 */
		D9                  = 57, /* 9 */

		Semicolon           = 59, /* ; */
		Equal               = 61, /* = */

		A                   = 65,
		B                   = 66,
		C                   = 67,
		D                   = 68,
		E                   = 69,
		F                   = 70,
		G                   = 71,
		H                   = 72,
		I                   = 73,
		J                   = 74,
		K                   = 75,
		L                   = 76,
		M                   = 77,
		N                   = 78,
		O                   = 79,
		P                   = 80,
		Q                   = 81,
		R                   = 82,
		S                   = 83,
		T                   = 84,
		U                   = 85,
		V                   = 86,
		W                   = 87,
		X                   = 88,
		Y                   = 89,
		Z                   = 90,

		LeftBracket         = 91,  /* [ */
		Backslash           = 92,  /* \ */
		RightBracket        = 93,  /* ] */
		GraveAccent         = 96,  /* ` */

		World1              = 161, /* non-US #1 */
		World2              = 162, /* non-US #2 */

		/* Function keys */
		Escape              = 256,
		Enter               = 257,
		Tab                 = 258,
		Backspace           = 259,
		Insert              = 260,
		Delete              = 261,
		Right               = 262,
		Left                = 263,
		Down                = 264,
		Up                  = 265,
		PageUp              = 266,
		PageDown            = 267,
		Home                = 268,
		End                 = 269,
		CapsLock            = 280,
		ScrollLock          = 281,
		NumLock             = 282,
		PrintScreen         = 283,
		Pause               = 284,
		F1                  = 290,
		F2                  = 291,
		F3                  = 292,
		F4                  = 293,
		F5                  = 294,
		F6                  = 295,
		F7                  = 296,
		F8                  = 297,
		F9                  = 298,
		F10                 = 299,
		F11                 = 300,
		F12                 = 301,
		F13                 = 302,
		F14                 = 303,
		F15                 = 304,
		F16                 = 305,
		F17                 = 306,
		F18                 = 307,
		F19                 = 308,
		F20                 = 309,
		F21                 = 310,
		F22                 = 311,
		F23                 = 312,
		F24                 = 313,
		F25                 = 314,

		/* Keypad */
		KP0                 = 320,
		KP1                 = 321,
		KP2                 = 322,
		KP3                 = 323,
		KP4                 = 324,
		KP5                 = 325,
		KP6                 = 326,
		KP7                 = 327,
		KP8                 = 328,
		KP9                 = 329,
		KPDecimal           = 330,
		KPDivide            = 331,
		KPMultiply          = 332,
		KPSubtract          = 333,
		KPAdd               = 334,
		KPEnter             = 335,
		KPEqual             = 336,

		LeftShift           = 340,
		LeftControl         = 341,
		LeftAlt             = 342,
		LeftSuper           = 343,
		RightShift          = 344,
		RightControl        = 345,
		RightAlt            = 346,
		RightSuper          = 347,
		Menu                = 348
	} Key;

	inline std::ostream& operator<<(std::ostream& os, KeyCode keyCode)
	{
		os << static_cast<int32_t>(keyCode);
		return os;
	}
}

// From glfw3.h
#define MAJKT_KEY_SPACE           ::majkt::Key::Space
#define MAJKT_KEY_APOSTROPHE      ::majkt::Key::Apostrophe    /* ' */
#define MAJKT_KEY_COMMA           ::majkt::Key::Comma         /* , */
#define MAJKT_KEY_MINUS           ::majkt::Key::Minus         /* - */
#define MAJKT_KEY_PERIOD          ::majkt::Key::Period        /* . */
#define MAJKT_KEY_SLASH           ::majkt::Key::Slash         /* / */
#define MAJKT_KEY_0               ::majkt::Key::D0
#define MAJKT_KEY_1               ::majkt::Key::D1
#define MAJKT_KEY_2               ::majkt::Key::D2
#define MAJKT_KEY_3               ::majkt::Key::D3
#define MAJKT_KEY_4               ::majkt::Key::D4
#define MAJKT_KEY_5               ::majkt::Key::D5
#define MAJKT_KEY_6               ::majkt::Key::D6
#define MAJKT_KEY_7               ::majkt::Key::D7
#define MAJKT_KEY_8               ::majkt::Key::D8
#define MAJKT_KEY_9               ::majkt::Key::D9
#define MAJKT_KEY_SEMICOLON       ::majkt::Key::Semicolon     /* ; */
#define MAJKT_KEY_EQUAL           ::majkt::Key::Equal         /* = */
#define MAJKT_KEY_A               ::majkt::Key::A
#define MAJKT_KEY_B               ::majkt::Key::B
#define MAJKT_KEY_C               ::majkt::Key::C
#define MAJKT_KEY_D               ::majkt::Key::D
#define MAJKT_KEY_E               ::majkt::Key::E
#define MAJKT_KEY_F               ::majkt::Key::F
#define MAJKT_KEY_G               ::majkt::Key::G
#define MAJKT_KEY_H               ::majkt::Key::H
#define MAJKT_KEY_I               ::majkt::Key::I
#define MAJKT_KEY_J               ::majkt::Key::J
#define MAJKT_KEY_K               ::majkt::Key::K
#define MAJKT_KEY_L               ::majkt::Key::L
#define MAJKT_KEY_M               ::majkt::Key::M
#define MAJKT_KEY_N               ::majkt::Key::N
#define MAJKT_KEY_O               ::majkt::Key::O
#define MAJKT_KEY_P               ::majkt::Key::P
#define MAJKT_KEY_Q               ::majkt::Key::Q
#define MAJKT_KEY_R               ::majkt::Key::R
#define MAJKT_KEY_S               ::majkt::Key::S
#define MAJKT_KEY_T               ::majkt::Key::T
#define MAJKT_KEY_U               ::majkt::Key::U
#define MAJKT_KEY_V               ::majkt::Key::V
#define MAJKT_KEY_W               ::majkt::Key::W
#define MAJKT_KEY_X               ::majkt::Key::X
#define MAJKT_KEY_Y               ::majkt::Key::Y
#define MAJKT_KEY_Z               ::majkt::Key::Z
#define MAJKT_KEY_LEFT_BRACKET    ::majkt::Key::LeftBracket   /* [ */
#define MAJKT_KEY_BACKSLASH       ::majkt::Key::Backslash     /* \ */
#define MAJKT_KEY_RIGHT_BRACKET   ::majkt::Key::RightBracket  /* ] */
#define MAJKT_KEY_GRAVE_ACCENT    ::majkt::Key::GraveAccent   /* ` */
#define MAJKT_KEY_WORLD_1         ::majkt::Key::World1        /* non-US #1 */
#define MAJKT_KEY_WORLD_2         ::majkt::Key::World2        /* non-US #2 */

/* Function keys */
#define MAJKT_KEY_ESCAPE          ::majkt::Key::Escape
#define MAJKT_KEY_ENTER           ::majkt::Key::Enter
#define MAJKT_KEY_TAB             ::majkt::Key::Tab
#define MAJKT_KEY_BACKSPACE       ::majkt::Key::Backspace
#define MAJKT_KEY_INSERT          ::majkt::Key::Insert
#define MAJKT_KEY_DELETE          ::majkt::Key::Delete
#define MAJKT_KEY_RIGHT           ::majkt::Key::Right
#define MAJKT_KEY_LEFT            ::majkt::Key::Left
#define MAJKT_KEY_DOWN            ::majkt::Key::Down
#define MAJKT_KEY_UP              ::majkt::Key::Up
#define MAJKT_KEY_PAGE_UP         ::majkt::Key::PageUp
#define MAJKT_KEY_PAGE_DOWN       ::majkt::Key::PageDown
#define MAJKT_KEY_HOME            ::majkt::Key::Home
#define MAJKT_KEY_END             ::majkt::Key::End
#define MAJKT_KEY_CAPS_LOCK       ::majkt::Key::CapsLock
#define MAJKT_KEY_SCROLL_LOCK     ::majkt::Key::ScrollLock
#define MAJKT_KEY_NUM_LOCK        ::majkt::Key::NumLock
#define MAJKT_KEY_PRINT_SCREEN    ::majkt::Key::PrintScreen
#define MAJKT_KEY_PAUSE           ::majkt::Key::Pause
#define MAJKT_KEY_F1              ::majkt::Key::F1
#define MAJKT_KEY_F2              ::majkt::Key::F2
#define MAJKT_KEY_F3              ::majkt::Key::F3
#define MAJKT_KEY_F4              ::majkt::Key::F4
#define MAJKT_KEY_F5              ::majkt::Key::F5
#define MAJKT_KEY_F6              ::majkt::Key::F6
#define MAJKT_KEY_F7              ::majkt::Key::F7
#define MAJKT_KEY_F8              ::majkt::Key::F8
#define MAJKT_KEY_F9              ::majkt::Key::F9
#define MAJKT_KEY_F10             ::majkt::Key::F10
#define MAJKT_KEY_F11             ::majkt::Key::F11
#define MAJKT_KEY_F12             ::majkt::Key::F12
#define MAJKT_KEY_F13             ::majkt::Key::F13
#define MAJKT_KEY_F14             ::majkt::Key::F14
#define MAJKT_KEY_F15             ::majkt::Key::F15
#define MAJKT_KEY_F16             ::majkt::Key::F16
#define MAJKT_KEY_F17             ::majkt::Key::F17
#define MAJKT_KEY_F18             ::majkt::Key::F18
#define MAJKT_KEY_F19             ::majkt::Key::F19
#define MAJKT_KEY_F20             ::majkt::Key::F20
#define MAJKT_KEY_F21             ::majkt::Key::F21
#define MAJKT_KEY_F22             ::majkt::Key::F22
#define MAJKT_KEY_F23             ::majkt::Key::F23
#define MAJKT_KEY_F24             ::majkt::Key::F24
#define MAJKT_KEY_F25             ::majkt::Key::F25

/* Keypad */
#define MAJKT_KEY_KP_0            ::majkt::Key::KP0
#define MAJKT_KEY_KP_1            ::majkt::Key::KP1
#define MAJKT_KEY_KP_2            ::majkt::Key::KP2
#define MAJKT_KEY_KP_3            ::majkt::Key::KP3
#define MAJKT_KEY_KP_4            ::majkt::Key::KP4
#define MAJKT_KEY_KP_5            ::majkt::Key::KP5
#define MAJKT_KEY_KP_6            ::majkt::Key::KP6
#define MAJKT_KEY_KP_7            ::majkt::Key::KP7
#define MAJKT_KEY_KP_8            ::majkt::Key::KP8
#define MAJKT_KEY_KP_9            ::majkt::Key::KP9
#define MAJKT_KEY_KP_DECIMAL      ::majkt::Key::KPDecimal
#define MAJKT_KEY_KP_DIVIDE       ::majkt::Key::KPDivide
#define MAJKT_KEY_KP_MULTIPLY     ::majkt::Key::KPMultiply
#define MAJKT_KEY_KP_SUBTRACT     ::majkt::Key::KPSubtract
#define MAJKT_KEY_KP_ADD          ::majkt::Key::KPAdd
#define MAJKT_KEY_KP_ENTER        ::majkt::Key::KPEnter
#define MAJKT_KEY_KP_EQUAL        ::majkt::Key::KPEqual

#define MAJKT_KEY_LEFT_SHIFT      ::majkt::Key::LeftShift
#define MAJKT_KEY_LEFT_CONTROL    ::majkt::Key::LeftControl
#define MAJKT_KEY_LEFT_ALT        ::majkt::Key::LeftAlt
#define MAJKT_KEY_LEFT_SUPER      ::majkt::Key::LeftSuper
#define MAJKT_KEY_RIGHT_SHIFT     ::majkt::Key::RightShift
#define MAJKT_KEY_RIGHT_CONTROL   ::majkt::Key::RightControl
#define MAJKT_KEY_RIGHT_ALT       ::majkt::Key::RightAlt
#define MAJKT_KEY_RIGHT_SUPER     ::majkt::Key::RightSuper
#define MAJKT_KEY_MENU            ::majkt::Key::Menu

#endif  // MAJKT_CORE_KEY_CODES_H_
