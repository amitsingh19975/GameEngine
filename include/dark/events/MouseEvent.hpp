#if !defined(DK_MOUSE_EVENT_HPP)
#define DK_MOUSE_EVENT_HPP

#include "Event.hpp"

namespace dk {

    struct MouseMovedEvent 
        : Event<EventType::MouseMoved, EventCategoryBitwiseOr(EventCategory::Mouse, EventCategory::Input)>{
        
        MouseMovedEvent( float x, float y ):
            m_mouseX(x), m_mouseY(y) {}
        
        constexpr auto GetX() const noexcept { return m_mouseX; }
        constexpr auto GetY() const noexcept { return m_mouseY; }

        std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetX() << ", " << GetY();
			return ss.str();
		}

    private:
        float m_mouseX;
        float m_mouseY;
    };

    struct MouseScrolledEvent 
        : Event<EventType::MouseScrolled, EventCategoryBitwiseOr(EventCategory::Mouse, EventCategory::Input)>{
        
        MouseScrolledEvent( float off_x, float off_y ):
            m_XOffset(off_x), m_YOffset(off_y) {}
        
        constexpr auto GetXOffset() const noexcept { return m_XOffset; }
        constexpr auto GetYOffset() const noexcept { return m_YOffset; }

        std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

    private:
        float m_XOffset;
        float m_YOffset;
    };

    template<EventType type>
    struct MouseButtonEvent 
        : Event<type, EventCategoryBitwiseOr(EventCategory::Mouse, EventCategory::Input)>{
        
        constexpr MouseCode GetMouseButton() const { return m_button; }
        
    protected:
        MouseButtonEvent( MouseCode bt )
            : m_button(bt){}

        MouseCode m_button;
    };


    struct MouseButtonPressedEvent 
        : MouseButtonEvent<EventType::MouseButtonPressed>{
        
        MouseButtonPressedEvent( MouseCode bt )
            : MouseButtonEvent(bt){}

        std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_button;
			return ss.str();
		}
    };

    struct MouseButtonReleasedEvent 
        : MouseButtonEvent<EventType::MouseButtonReleased>{
        
        MouseButtonReleasedEvent( MouseCode bt )
            : MouseButtonEvent(bt){}

        std::string ToString() const override{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_button;
			return ss.str();
		}
    };


}


#endif // DK_MOUSE_EVENT_HPP
