#if !defined(DK_OPENGL_CONTEXT)
#define DK_OPENGL_CONTEXT

#include "dark/renderer/GraphicsContext.hpp"

namespace dk{
    
    template<typename W> struct OpenGLContext{};
    
    template<>
    struct OpenGLContext<SDL_Window> : GraphicsContext{
        using window_type = SDL_Window;
        using base_type = Ref< window_type >;
        using context_type = SDL_GLContext;
        OpenGLContext( base_type win,  context_type ctx);

        void Init() override;
        void SwapBuffers() override;

        constexpr context_type& GetSDLContext() { return m_ctx;}
        window_type& GetWindow() { return *m_window;}

    private:
        base_type m_window;
        context_type m_ctx;
    };
}

#endif // DK_OPENGL_CONTEXT
