#if !defined(DK_EVENT_HPP)
#define DK_EVENT_HPP

#include "dark/core.hpp"

namespace dk {
    enum class EventType{
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum class EventCategory{
        None        = 0,
        App         = bit(0),
        Input       = bit(1),
        Keyboard    = bit(2),
        Mouse       = bit(3),
        MouseButton = bit(4)
    };

    namespace detail{
        constexpr std::array<char const*, 16> EventTypeToString = {
            "None",
            "WindowClose", "WindowResize", "WindowFocus", "WindowLostFocus", "WindowMoved",
            "AppTick", "AppUpdate", "AppRender",
            "KeyPressed", "KeyReleased", "KeyTyped",
            "MouseButtonPressed", "MouseButtonReleased", "MouseMoved", "MouseScrolled"
        };
    }

    struct EventBase{
        bool Handled = false;

        virtual EventType GetEventType() const = 0;
        virtual char const* GetName() const = 0;
        virtual EventCategory GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline constexpr auto IsInCategory( EventCategory cat ) const{
            return static_cast<int>( GetCategoryFlags() ) & static_cast<int>(cat);
        }
    };

    struct EventDispatcher{
        EventDispatcher( EventBase& event ): m_event(event){}

        template<typename T, typename P>
        constexpr auto Dispatch( const P& pred ){
            if ( m_event.GetEventType() == T::GetStaticType() ){
                m_event.Handled = pred(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }

    private:
        EventBase& m_event;
    };

    template<EventType type, EventCategory category>
    struct Event: EventBase{
        constexpr static auto GetStaticType() noexcept{ return type; }
        virtual EventType GetEventType() const override{ return GetStaticType(); }
        virtual char const* GetName() const override { return detail::EventTypeToString[static_cast<size_t>(type)];}
        virtual EventCategory GetCategoryFlags() const override { return category; }
    };

    inline auto& operator<<( std::ostream& os, EventBase const& e){
        return os << e.ToString();
    }

    constexpr EventCategory EventCategoryBitwiseOr(EventCategory a, EventCategory b){
        return static_cast<EventCategory>(
            static_cast<int>(a) | static_cast<int>(b)
        );
    }
}  

#endif // DK_EVENT_HPP
