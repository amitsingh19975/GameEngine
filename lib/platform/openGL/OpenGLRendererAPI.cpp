#include "dark/platform/openGL/OpenGLRendererAPI.hpp"
#include "dark/renderer/VertexArray.hpp"

namespace dk{
    
    void OpenGLRendererAPI::SetClearColor( glm::vec4 const& color) noexcept{
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear() noexcept{
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed( Ref<VertexArray> const& vertexArray) noexcept{
        glDrawElements(
            GL_TRIANGLES, 
            Deref( Deref(vertexArray).GetIndexBuffer() ).GetCount(),
            GL_UNSIGNED_INT,
            nullptr
        );
    }

    void OpenGLRendererAPI::Init() {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRendererAPI::SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height ) const noexcept{
        glViewport(x,y,width * Config::frameScale, height * Config::frameScale);
    }

}