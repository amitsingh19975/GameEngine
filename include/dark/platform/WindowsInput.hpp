#if !defined(DK_WINDOWS_INPUT_HPP)
#define DK_WINDOWS_INPUT_HPP

#include "dark/core/Input.hpp"

namespace dk{
    struct WindowsInput : Input{
        using Input::GetMousePosition;
        using Input::GetMouseX;
        using Input::GetMouseY;
        using Input::IsKeyPressed;
        using Input::IsMouseButtonPressed;
    protected:
        virtual bool IsKeyPressedImpl(KeyCode key) const noexcept override;
        virtual bool IsMouseButtonPressedImpl(MouseCode button) const noexcept override;
        virtual mouse_position_type GetMousePositionImpl() const noexcept override;
        virtual float GetMouseXImpl() const noexcept override;
        virtual float GetMouseYImpl() const noexcept override;
    };
}

#endif // DK_WINDOWS_INPUT_HPP
