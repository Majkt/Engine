#ifndef MAJKT_APPICATION_EVENTS_H_
#define MAJKT_APPICATION_EVENTS_H_

#include "event.h"

#include <sstream>

namespace majkt {

class WindowResizeEvent : public Event
{
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
            : width_(width), height_(height) {}

        inline unsigned int GetWidth() const { return width_; }
        inline unsigned int GetHeight() const { return height_; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: " << width_ << ", " << height_;
            return ss.str();
        }

        EVENT_CLASS_TYPE(kWindowResize)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryApplication)
    private:
        unsigned int width_, height_;
};

class WindowCloseEvent : public Event
{
    public:
		WindowCloseEvent() = default;

        EVENT_CLASS_TYPE(kWindowClose)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryApplication)
};

class AppTickEvent : public Event
{
    public:
        AppTickEvent() = default;

        EVENT_CLASS_TYPE(kAppTick)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryApplication)
};

class AppUpdateEvent : public Event
{
    public:
        AppUpdateEvent() = default;

        EVENT_CLASS_TYPE(kAppUpdate)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryApplication)
};

class AppRenderEvent : public Event
{
    public:
        AppRenderEvent() = default;

        EVENT_CLASS_TYPE(kAppRender)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryApplication)
};

} // namespace majkt

#endif  // MAJKT_APPICATION_EVENTS_H_
