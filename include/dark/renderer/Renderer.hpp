#if !defined(DK_RENDER_HPP)
#define DK_RENDER_HPP

#include "dark/renderer/RendererAPI.hpp"
#include "dark/renderer/OrthographicCamera.hpp"
#include "dark/renderer/Shader.hpp"

namespace dk{
    
    struct Renderer{
        
        Renderer() = default;

        static void Init();
        static void OnWindowResize(uint32_t width, uint32_t height) noexcept;

        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();

        static void Submit( Ref<Shader> const& shader, Ref<VertexArray> const& vertexArray, glm::mat4 const& transform = glm::mat4(1.f) );

        inline static RendererAPI::API GetAPI() noexcept { return RendererAPI::GetAPI(); }

    private:
        struct SceneData{
            glm::mat4 viewProjectionMatrix;
        };

        static Ref<SceneData> s_sceneData;
    };
    
}

#endif // DK_RENDER_HPP