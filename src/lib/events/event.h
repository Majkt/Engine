#ifndef MAJKT_EVENTS_H_
#define MAJKT_EVENTS_H_

#include "src/lib/core/base_export.h"
#include "src/lib/core/math_util.h"

#include <string>
#include <functional>

namespace majkt {

// Enum defined to filter events based on category.
enum class EventType
{
    kNone = 0,
    kWindowClose, kWindowResize, kWindowFocus, kWindowLostFocus, kWindowMoved,
    kAppTick, kAppUpdate, kAppRender,
    kKeyPressed, kKeyReleased,
    kMouseButtonPressed, kMouseButtonReleased, kMouseMoved, kMouseScrolled,
};

// Enum defined to filter events based on category. Each category is represesnted by a bit field.
enum EventCategory
{
    kNone = 0,
    kEventCategoryApplication    = BIT(0),
    kEventCategoryInput          = BIT(1),
    kEventCategoryKeyboard       = BIT(2),
    kEventCategoryMouse          = BIT(3),
    kEventCategoryMouseButton    = BIT(4),
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
 								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }


class MAJKT_BASE_EXPORT Event
{
    friend class EventDispatcher;
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }
        
        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }
    protected:
        // Check if the event has been handled.
        bool event_handled_ = false;
};

class EventDispatcher
{
    template<typename T>
    using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : event_(event) {}

        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (event_.GetEventType() == T::GetStaticType())
            {
                event_.event_handled_ = func(*(T*)&event_);
                return true;
            }
            return false;
        }
    private:
        Event& event_;
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.ToString();
}

} // namespace majkt

#endif  // MAJKT_EVENTS_H_
