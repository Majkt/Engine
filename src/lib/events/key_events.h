#ifndef MAJKT_KEY_EVENTS_H_
#define MAJKT_KEY_EVENTS_H_

#include "src/lib/events/event.h"
#include "src/lib/core/key_codes.h"

#include <sstream>
#include <memory>

namespace majkt {
class KeyEvent : public Event
{
    public:
        KeyCode GetKeyCode() const { return key_code_; }

        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryKeyboard | EventCategory::kEventCategoryInput)
    protected:
        KeyEvent(const KeyCode keycode)
            : key_code_(keycode) {}

        KeyCode key_code_;
};

class KeyPressedEvent : public KeyEvent
{
    public:
        KeyPressedEvent(const KeyCode keycode, const uint16_t repeatCount)
            : KeyEvent(keycode), repeat_count_(repeatCount) {}

        uint16_t GetRepeatCount() const { return repeat_count_; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << key_code_ << " (" << repeat_count_ << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE(kKeyPressed)
    private:
        uint16_t repeat_count_;
};

class KeyReleasedEvent : public KeyEvent
{
    public:
        KeyReleasedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << key_code_;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kKeyReleased)
};

class KeyTypedEvent : public KeyEvent
{
public:
    KeyTypedEvent(const KeyCode keycode)
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
