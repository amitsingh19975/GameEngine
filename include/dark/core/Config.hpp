#if !defined(DK_CONFIG_HPP)
#define DK_CONFIG_HPP

namespace dk{

    enum class OS{
        WINDOWS,
        MACOS,
        LINUX,
        FREEBSD,
        ANDROID,
        None
    };

    struct Config{
        
        #if defined(DEBUG)
            static constexpr auto is_debug = true;
        #else
            static constexpr auto is_debug = false;
        #endif
        
        #if defined(_Win32) || defined(_Win64)
            static constexpr auto os = OS::WINDOWS;
        #endif

        #if defined(linux) || defined(__linux) || defined(__linux__)
            static constexpr auto os = OS::LINUX;
        #endif

        #if defined(__FreeBSD__)
            static constexpr auto os = OS::FREEBSD;
        #endif

        #if defined(__ANDROID__)
            static constexpr auto os = OS::ANDROID;
        #endif

        #if defined(__APPLE__) || defined(__MACH__)
            static constexpr auto os = OS::MACOS;
        #endif

        constexpr static auto frameScale = 2; //
    };

}

#endif // DK_CONFIG_HPP
