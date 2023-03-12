#ifndef MAJKT_MOUSE_EVENTS_H_
#define MAJKT_MOUSE_EVENTS_H_

#include "event.h"

#include <sstream>

namespace majkt {
class MAJKT_BASE_EXPORT MouseMovedEvent : public Event
{
    public:
        MouseMovedEvent(float x, float y)
            : m_MouseX(x), m_MouseY(y) {}

        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kMouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryMouse |EventCategory:: kEventCategoryInput)
    private:
        float m_MouseX, m_MouseY;
};

class MAJKT_BASE_EXPORT MouseScrolledEvent : public Event
{
    public:
        MouseScrolledEvent(float xOffset, float yOffset)
            : x_offset_(xOffset), y_offset_(yOffset) {}

        inline float GetXOffset() const { return x_offset_; }
        inline float GetYOffset() const { return y_offset_; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }

        EVENT_CLASS_TYPE(kMouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryMouse | EventCategory::kEventCategoryInput)
    private:
        float x_offset_, y_offset_;
};

class MAJKT_BASE_EXPORT MouseButtonEvent : public Event
{
    public:
        inline int GetMouseButton() const { return button_; }

        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryMouse | EventCategory::kEventCategoryInput)
    protected:
        MouseButtonEvent(int button)
            : button_(button) {}

        int button_;
};

class MAJKT_BASE_EXPORT MouseButtonPressedEvent : public MouseButtonEvent
{
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << button_;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kMouseButtonPressed)
};

class MAJKT_BASE_EXPORT MouseButtonReleasedEvent : public MouseButtonEvent
{
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << button_;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kMouseButtonReleased)
};

} // namespace majkt

#endif  // MAJKT_MOUSE_EVENTS_H_
