#include "dark/platform/WindowsInput.hpp"
#include "dark/core/windows.hpp"
#include "dark/DarkApp.hpp"

namespace dk{
    bool WindowsInput::IsKeyPressedImpl( KeyCode key ) const noexcept{
        auto* state = SDL_GetKeyboardState(nullptr);
        return state[DKKeyCodeToSDLKeyCode(key)]; 
    }

    bool WindowsInput::IsMouseButtonPressedImpl( MouseCode button ) const noexcept{
        auto state = SDL_GetMouseState(nullptr,nullptr);
        return DKButton(state) == button; 
    }

    Input::mouse_position_type WindowsInput::GetMousePositionImpl() const noexcept{
        int x, y;
        SDL_GetMouseState(&x,&y);
        return {static_cast<float>(x),static_cast<float>(y)}; 
    }

    float WindowsInput::GetMouseXImpl() const noexcept{
        auto [x, _] = GetMousePosition();
        return x;
    }

    float WindowsInput::GetMouseYImpl() const noexcept{
        auto [_, y] = GetMousePosition();
        return y;
    }
}