#if !defined(DK_INPUT_HPP)
#define DK_INPUT_HPP

#include "dark/core/Core.hpp"
#include "dark/core/Log.hpp"

namespace dk{
    struct Input{
    protected:
        Input() = default;
    public:
        using mouse_position_type = std::pair<float,float>;
        
        Input(Input const&) = delete;
        Input(Input&&) = delete;
        Input& operator=(Input const&) = delete;
        Input& operator=(Input&&) = delete;

        virtual ~Input(){};

        inline static bool IsKeyPressed( KeyCode key ) { 
            CoreAssert(s_instance != nullptr, "Input instance is initialized");
            return Deref(s_instance).IsKeyPressedImpl(key); 
        }
        inline static bool IsMouseButtonPressed( MouseCode button ) { 
            CoreAssert(s_instance != nullptr, "Input instance is initialized");
            return Deref(s_instance).IsMouseButtonPressedImpl(button); 
        }
        inline static mouse_position_type GetMousePosition() { 
            CoreAssert(s_instance != nullptr, "Input instance is initialized");
            return Deref(s_instance).GetMousePositionImpl(); 
        }
        inline static float GetMouseX() { 
            CoreAssert(s_instance != nullptr, "Input instance is initialized");
            return Deref(s_instance).GetMouseXImpl(); 
        }
        inline static float GetMouseY() { 
            CoreAssert(s_instance != nullptr, "Input instance is initialized");
            return Deref(s_instance).GetMouseYImpl(); 
        }

        static Scope<Input> Create();
    protected:
        virtual bool IsKeyPressedImpl(KeyCode key) const noexcept= 0;
        virtual bool IsMouseButtonPressedImpl(MouseCode button) const noexcept= 0;
        virtual mouse_position_type GetMousePositionImpl() const noexcept = 0;
        virtual float GetMouseXImpl() const noexcept = 0;
        virtual float GetMouseYImpl() const noexcept = 0;
    private:
        static Scope<Input> s_instance;
    };
}

#endif // DK_INPUT_HPP
