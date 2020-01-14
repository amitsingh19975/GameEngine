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
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include "Config.hpp"


namespace dk {

    using KeyCode = SDL_Keycode;
    using MouseCode = uint32_t;
    
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
}

#endif // DK_CORE_HPP
