#ifndef MAJKT_APPICATION_EVENTS_H_
#define MAJKT_APPICATION_EVENTS_H_

#include "event.h"

#include <sstream>

namespace majkt {

class MAJKT_BASE_EXPORT WindowResizeEvent : public Event
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

class MAJKT_BASE_EXPORT WindowCloseEvent : public Event
{
    public:
        WindowCloseEvent() {}

        EVENT_CLASS_TYPE(kWindowClose)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryApplication)
};

class MAJKT_BASE_EXPORT AppTickEvent : public Event
{
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(kAppTick)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryApplication)
};

class MAJKT_BASE_EXPORT AppUpdateEvent : public Event
{
    public:
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(kAppUpdate)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryApplication)
};

class MAJKT_BASE_EXPORT AppRenderEvent : public Event
{
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(kAppRender)
        EVENT_CLASS_CATEGORY(EventCategory::kEventCategoryApplication)
};

} // namespace majkt

#endif  // MAJKT_APPICATION_EVENTS_H_
