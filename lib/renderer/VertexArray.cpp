#include "dark/renderer/VertexArray.hpp"
#include "dark/platform/openGL/OpenGLVertexArray.hpp"
#include "dark/renderer/Renderer.hpp"
namespace dk{
    Ref<VertexArray> VertexArray::Create(){
        switch (Renderer::GetAPI()){
            case RendererAPI::API::None: CoreAssert(false,"VertexBuffer::Create : RendererAPI::None is currently not supported");
            case RendererAPI::API::OpenGL : return CreateRef<OpenGLVertexArray>();
            default : CoreAssert(false,"VertexBuffer::Create : Unknown RendererAPI"); 
        }
    }
}