#if !defined(DK_RENDER_HPP)
#define DK_RENDER_HPP

#include "dark/renderer/RendererAPI.hpp"
#include "dark/renderer/OrthographicCamera.hpp"
#include "dark/renderer/Shader.hpp"

namespace dk{

    struct Renderer{
        
        Renderer() = default;

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit( Ref<Shader> const& shader, Ref<VertexArray> const& vertexArray );

        inline static RendererAPI::API GetAPI() noexcept { return RendererAPI::GetAPI(); }

    private:
        struct SceneData{
            glm::mat4 viewProjectionMatrix;
        };

        static Ref<SceneData> s_sceneData;
    };
    
}

#endif // DK_RENDER_HPP