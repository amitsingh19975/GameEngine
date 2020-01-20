#if !defined(DK_RENDERER_2D_HPP)
#define DK_RENDERER_2D_HPP

#include "dark/core/Core.hpp"
#include "dark/renderer/OrthographicCamera.hpp"
#include "glm/glm.hpp"
#include "dark/renderer/Texture.hpp"

namespace dk{

    struct Renderer2D{

        static void Init();
        static void ShutDown();

        static void BeginScene( OrthographicCamera const& camera );
        static void EndScene();

        static void SetShaderPath(std::string_view path);
        static void SetTextureShaderPath(std::string_view path);

        static void DrawQuad( glm::vec2 const& position, glm::vec2 const& size, glm::vec4 const& color);
        static void DrawQuad( glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color);
        
        static void DrawQuad( glm::vec2 const& position, glm::vec2 const& size, Ref<Texture2D> const& texture);
        static void DrawQuad( glm::vec3 const& position, glm::vec2 const& size, Ref<Texture2D> const& texture);
    };

}

#endif // DK_RENDERER_2D_HPP
