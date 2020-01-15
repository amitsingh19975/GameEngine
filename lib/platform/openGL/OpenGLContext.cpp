#include "dark/platform/openGL/OpenGLContext.hpp"
#include "dark/core/Log.hpp"

namespace dk{
    
    OpenGLContext<SDL_Window>::OpenGLContext( base_type win,  context_type ctx) 
        : m_window(win), m_ctx(ctx){
            
        CoreAssert(m_window != nullptr, "OpenGLContext::OpenGLContext() : Window handle is null ");
    } 

    void OpenGLContext<SDL_Window>::Init(){
        CoreAssert( gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress), "Init Failed", "Failed to initialize the OpenGL context: " );
    }

    void OpenGLContext<SDL_Window>::SwapBuffers() {
        SDL_GL_SwapWindow(m_window.get());
    }

}