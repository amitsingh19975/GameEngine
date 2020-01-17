#include "dark/renderer/Buffer.hpp"
#include "dark/renderer/Renderer.hpp"
#include "dark/core/Log.hpp"
#include "dark/platform/openGL/OpenGLBuffer.hpp"
#include "dark/renderer/Buffer.hpp"

namespace dk{
    
    Ref<VertexBuffer> VertexBuffer::Create( value_type* vertices, size_type size ){
        switch (Renderer::GetAPI()){
            case RendererAPI::None: CoreAssert(false,"VertexBuffer::Create : RendererAPI::None is currently not supported");
            case RendererAPI::OpenGL : return CreateRef<OpenGLVertexBuffer>(vertices,size);
            default : CoreAssert(false,"VertexBuffer::Create : Unknown RendererAPI"); 
        }
    }   

    Ref<IndexBuffer> IndexBuffer::Create( value_type* indices, count_type count ){
        switch (Renderer::GetAPI()){
            case RendererAPI::None: CoreAssert(false,"VertexBuffer::Create : RendererAPI::None is currently not supported");
            case RendererAPI::OpenGL : return CreateRef<OpenGLIndexBuffer>(indices,count);
            default : CoreAssert(false,"VertexBuffer::Create : Unknown RendererAPI"); 
        }
    }
}