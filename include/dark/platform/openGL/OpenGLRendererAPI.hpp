#if !defined(DK_OPENGL_RENDERER_API)
#define DK_OPENGL_RENDERER_API

#include "dark/renderer/RendererAPI.hpp"

namespace dk{
    struct OpenGLRendererAPI : RendererAPI{
        OpenGLRendererAPI() = default;
        virtual ~OpenGLRendererAPI(){}
        void SetClearColor( glm::vec4 const& color) noexcept override;
        void Clear() noexcept override;
        void DrawIndexed( Ref<VertexArray> const& vertexArray) noexcept override;
    };
}

#endif // DK_OPENGL_RENDERER_API
