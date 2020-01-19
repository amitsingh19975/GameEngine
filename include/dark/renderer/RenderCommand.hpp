#if !defined(DK_RENDER_COMMAND_HPP)
#define DK_RENDER_COMMAND_HPP

#include "dark/core/Core.hpp"
#include "dark/renderer/RendererAPI.hpp"

namespace dk{

    struct RenderCommand{
        
        RenderCommand() = default;
        
        inline static void Init(){
            Deref( s_rendererAPI ).Init();
        }

        inline static void SetClearColor( glm::vec4 const& color) noexcept{
            Deref( s_rendererAPI ).SetClearColor(color);
        }
        template<typename... Args>
        inline static void SetClearColor( Args&&... args) noexcept{
            Deref( s_rendererAPI ).SetClearColor(glm::vec4{std::forward<Args>(args)...});
        }
        inline static void Clear() noexcept{
            Deref( s_rendererAPI ).Clear();
        }

        inline static void DrawIndexed( Ref<VertexArray> const& vertexArray ) noexcept{
            s_rendererAPI->DrawIndexed(vertexArray);
        }

    private:
        static Scope<RendererAPI> s_rendererAPI;
    };

}

#endif // DK_RENDER_COMMAND_HPP
