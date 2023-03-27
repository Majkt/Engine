#ifndef MAJKT_KEY_EVENTS_H_
#define MAJKT_KEY_EVENTS_H_

#include "event.h"
#include <sstream>

namespace majkt {
class MAJKT_BASE_EXPORT KeyEvent : public Event
{
    public:
        inline int GetKeyCode() const { return key_code_; }

        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryKeyboard | EventCategory::kEventCategoryInput)
    protected:
        KeyEvent(int keycode)
            : key_code_(keycode) {}

        int key_code_;
};

class MAJKT_BASE_EXPORT KeyPressedEvent : public KeyEvent
{
    public:
        KeyPressedEvent(int keycode, int repeatCount)
            : KeyEvent(keycode), repeat_count_(repeatCount) {}

        inline int GetRepeatCount() const { return repeat_count_; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << key_code_ << " (" << repeat_count_ << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(kKeyPressed)
    private:
        int repeat_count_;
};

class MAJKT_BASE_EXPORT KeyReleasedEvent : public KeyEvent
{
    public:
        KeyReleasedEvent(int keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << key_code_;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kKeyReleased)
};

class MAJKT_BASE_EXPORT KeyTypedEvent : public KeyEvent
{
public:
    KeyTypedEvent(int keycode)
        : KeyEvent(keycode) {}

    std::string ToString() const override
    {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << key_code_;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyTyped)
};
} // namespace majkt

#endif  // MAJKT_KEY_EVENTS_H_
