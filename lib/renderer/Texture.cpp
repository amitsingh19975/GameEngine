#include "dark/renderer/Texture.hpp"
#include "dark/renderer/Renderer.hpp"
#include "dark/platform/openGL/OpenGLTexture.hpp"

namespace dk{
    Ref<Texture2D> Texture2D::Create( std::string_view path ) noexcept{
        switch (Renderer::GetAPI()){
            case RendererAPI::API::None: CoreAssert(false,"VertexBuffer::Create : RendererAPI::None is currently not supported");
            case RendererAPI::API::OpenGL : return CreateRef<OpenGLTexture2D>(path);
            default : CoreAssert(false,"VertexBuffer::Create : Unknown RendererAPI"); 
        }
    }
}