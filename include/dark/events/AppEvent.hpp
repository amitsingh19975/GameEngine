#if !defined(DK_APP_EVENT_HPP)
#define DK_APP_EVENT_HPP

#include "Event.hpp"

namespace dk{
    struct WindowResizeEvent 
        : Event< EventType::WindowResize, EventCategory::App >{

        WindowResizeEvent( uint32_t width, uint32_t height )
            : m_width(width), m_height(height){}
        
        constexpr auto GetWidth() const noexcept { return m_width; }
        constexpr auto GetHeight() const noexcept { return m_height; }

        std::string ToString() const override{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

    private:
        uint32_t m_width;
        uint32_t m_height;
    };

    struct WindowCloseEvent
        : Event< EventType::WindowClose, EventCategory::App >{
        WindowCloseEvent() = default;
    };

    struct AppTickEvent
        : Event< EventType::AppTick, EventCategory::App >{
        AppTickEvent() = default;
    };

    struct AppUpdateEvent
        : Event< EventType::AppUpdate, EventCategory::App >{
        AppUpdateEvent() = default;
    };

    struct AppRenderEvent
        : Event< EventType::AppRender, EventCategory::App >{
        AppRenderEvent() = default;
    };

}

#endif // DK_APP_EVENT_HPP
