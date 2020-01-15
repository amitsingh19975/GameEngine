#if !defined(DK_GRAPHICS_CONTEXT_HPP)
#define DK_GRAPHICS_CONTEXT_HPP

#include "dark/core/Core.hpp"

namespace dk{
    struct GraphicsContext{
        
        virtual ~GraphicsContext(){}
        
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        // template<typename T>
        // static Scope<GraphicsContext> Create( detail::WindowBase<T>* window );
    };
}

#endif // DK_GRAPHICS_CONTEXT_HPP
