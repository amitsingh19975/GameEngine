#if !defined(DK_KEYBOARD_EVENT_HPP)
#define DK_KEYBOARD_EVENT_HPP

#include "Event.hpp"

namespace dk{
    template<EventType type>
    struct KeyEvent 
        : Event<type, EventCategoryBitwiseOr(EventCategory::Keyboard,EventCategory::Input)>{
        
        constexpr KeyCode GetKeyCode() const noexcept { return m_keyCode; }

    protected:
        KeyEvent( KeyCode k ) : m_keyCode(k) {}
        KeyCode m_keyCode;
    };

    struct KeyPressedEvent : KeyEvent<EventType::KeyPressed> {

        KeyPressedEvent( KeyCode kc, int count )
            : KeyEvent(kc), m_repeatCount(count){}
        constexpr auto GetRepeatCount() const noexcept { return m_repeatCount; }
    private:
        int m_repeatCount;
    };

    struct KeyReleasedEvent : KeyEvent<EventType::KeyReleased> {

        KeyReleasedEvent( KeyCode kc)
            : KeyEvent(kc){}
        
        std::string ToString() const override{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_keyCode;
			return ss.str();
		}

    };

    struct KeyTypedEvent : KeyEvent<EventType::KeyTyped> {

        KeyTypedEvent( std::string_view data )
            : KeyEvent(SDL_SCANCODE_UNKNOWN),m_data(data){;
            }
        
        char const* GetData() const noexcept {
            return m_data.c_str();
        }

        std::string ToString() const override{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_keyCode;
			return ss.str();
		}
    private:
        std::string m_data;
    };
}

#endif // DK_KEYBOARD_EVENT_HPP
