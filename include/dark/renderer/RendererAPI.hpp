#if !defined(DK_RENDERER_API_HPP)
#define DK_RENDERER_API_HPP

#include "glm/glm.hpp"
#include "dark/core/Core.hpp"

namespace dk {

    struct VertexArray;

    struct RendererAPI{
        enum class API{
            None = 0, OpenGL
        };


        virtual ~RendererAPI() {}

        virtual void Init() = 0;
        
        virtual void SetClearColor( glm::vec4 const& color) noexcept = 0;
        virtual void Clear() noexcept = 0;

        virtual void DrawIndexed( Ref<VertexArray> const& vertexArray) noexcept = 0;

        inline static API GetAPI() noexcept { return s_API;}
    private:
        static API s_API;
    };
}

#endif // DK_RENDERER_API_HPP
