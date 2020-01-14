#if !defined(DK_CORE_HPP)
#define DK_CORE_HPP

#include<string>
#include<sstream>
#include<memory>
#include<array>
#include<algorithm>
#include<vector>
#include<functional>
#include<ostream>
#include<glad/glad.hpp>
#include<SDL2/SDL.h>


namespace dk {

    using KeyCode = SDL_Keycode;
    using MouseCode = uint32_t;
    
    template<typename T>
    using Scope = std::unique_ptr<T>;
    
    template<typename T>
    using Ref = std::shared_ptr<T>;

    struct Config{
        #if defined(DEBUG)
            static constexpr auto is_debug = true;
        #else
            static constexpr auto is_debug = false;
        #endif

        #if defined(_Win32) || defined(_Win64)
            static constexpr auto os = "Windows";
        #endif

        #if defined(linux) || defined(__linux) || defined(__linux__)
            static constexpr auto os = "Linux";
        #endif

        #if defined(__FreeBSD__)
            static constexpr auto os = "FreeBSD";
        #endif

        #if defined(__ANDROID__)
            static constexpr auto os = "Android";
        #endif

        #if defined(__APPLE__) || defined(__MACH__)
            static constexpr auto os = "MacOSX";
        #endif

    };

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
