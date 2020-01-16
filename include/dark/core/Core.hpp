#if !defined(DK_CORE_HPP)
#define DK_CORE_HPP

#include <string>
#include <sstream>
#include <memory>
#include <array>
#include <algorithm>
#include <vector>
#include <functional>
#include <ostream>
#include <utility>
#include "glad/glad.h"
#include <SDL2/SDL.h>
#include "dark/core/Config.hpp"
#include "dark/core/KeyCode.hpp"
#include "dark/core/MouseCode.hpp"

namespace dk {
    
    template<typename T>
    using Scope = std::unique_ptr<T>;
    
    template<typename T>
    using Ref = std::shared_ptr<T>;

    constexpr int bit( int p ){
        return 1 << p;
    }

    template<typename T, typename... Args>
    constexpr Scope<T> CreateScope(Args&&... args){
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    constexpr Ref<T> CreateRef(Args&&... args){
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    constexpr KeyCode SDLKeyCodeToDKKeyCode(SDL_Scancode k) noexcept{
        return static_cast<KeyCode>(k);
    }

    constexpr SDL_Scancode DKKeyCodeToSDLKeyCode(KeyCode k) noexcept{
        return static_cast<SDL_Scancode>(k);
    }

    constexpr MouseCode SDLMouseCodeToDKMouseCode(uint8_t b) noexcept{
        return static_cast<MouseCode>(b);
    }

    constexpr uint8_t DKMouseCodeToSDLMouseCode(MouseCode b) noexcept{
        return static_cast<uint8_t>(b);
    }

    constexpr MouseCode DKButton(MouseCode b){
        return SDLMouseCodeToDKMouseCode(SDL_BUTTON(DKMouseCodeToSDLMouseCode(b)));
    }

    constexpr MouseCode DKButton(uint8_t b){
        return SDLMouseCodeToDKMouseCode(SDL_BUTTON(b));
    }

    template<typename...Args>
    void DKGenVertexArrays(Args&&... args){
        if constexpr( Config::os == OS::MACOS ){
            glGenVertexArraysAPPLE(std::forward<Args>(args)...);
        }else{
            glGenVertexArrays(std::forward<Args>(args)...);
        }
    }

    template<typename...Args>
    void DKBindVertexArray(Args&&... args){
        if constexpr( Config::os == OS::MACOS ){
            glBindVertexArrayAPPLE(std::forward<Args>(args)...);
        }else{
            glBindVertexArray(std::forward<Args>(args)...);
        }
    }

    template<typename...Args>
    void DKDeleteVertexBuffer(Args&&... args){
        if constexpr( Config::os == OS::MACOS ){
            glDeleteVertexArraysAPPLE(std::forward<Args>(args)...);
        }else{
            glDeleteVertexArrays(std::forward<Args>(args)...);
        }
    }
}

#endif // DK_CORE_HPP
