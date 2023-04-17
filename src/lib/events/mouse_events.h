#ifndef MAJKT_MOUSE_EVENTS_H_
#define MAJKT_MOUSE_EVENTS_H_

#include "event.h"

#include <sstream>

namespace majkt {
class MouseMovedEvent : public Event
{
    public:
        MouseMovedEvent(float x, float y)
            : mouseX_(x), mouseY_(y) {}

        inline float GetX() const { return mouseX_; }
        inline float GetY() const { return mouseY_; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << mouseX_ << ", " << mouseY_;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kMouseMoved)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryMouse | EventCategory:: kEventCategoryInput)
    private:
        float mouseX_, mouseY_;
};

class MouseScrolledEvent : public Event
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

class MouseButtonEvent : public Event
{
    public:
        inline int GetMouseButton() const { return button_; }

        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryMouse | EventCategory::kEventCategoryInput)
    protected:
        MouseButtonEvent(int button)
            : button_(button) {}

        int button_;
};

class MouseButtonPressedEvent : public MouseButtonEvent
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

class MouseButtonReleasedEvent : public MouseButtonEvent
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
