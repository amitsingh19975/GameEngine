#if !defined(DK_OPENGL_RENDERER_API)
#define DK_OPENGL_RENDERER_API

#include "dark/renderer/RendererAPI.hpp"

namespace dk{
    struct OpenGLRendererAPI : RendererAPI{
        OpenGLRendererAPI() = default;
        virtual ~OpenGLRendererAPI(){}

        void Init() override;
        void SetClearColor( glm::vec4 const& color) noexcept override;
        void Clear() noexcept override;
        void DrawIndexed( Ref<VertexArray> const& vertexArray) noexcept override;
        void SetViewport( uint32_t x, uint32_t y, uint32_t width, uint32_t height ) const noexcept override;
    };
}

#endif // DK_OPENGL_RENDERER_API
