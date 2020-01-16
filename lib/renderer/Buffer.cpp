#include "dark/renderer/Buffer.hpp"
#include "dark/renderer/Renderer.hpp"
#include "dark/core/Log.hpp"
#include "dark/platform/openGL/OpenGLBuffer.hpp"
#include "dark/renderer/Buffer.hpp"

namespace dk{
    
    Scope<VertexBuffer> VertexBuffer::Create( value_type* vertices, size_type size ){
        switch (Renderer::GetAPI()){
            case RendererAPI::None: CoreAssert(false,"VertexBuffer::Create : RendererAPI::None is currently not supported");
            case RendererAPI::OpenGL : return CreateScope<OpenGLVertexBuffer>(vertices,size);
            default : CoreAssert(false,"VertexBuffer::Create : Unknown RendererAPI"); 
        }
    }   

    Scope<IndexBuffer> IndexBuffer::Create( value_type* indices, count_type count ){
        switch (Renderer::GetAPI()){
            case RendererAPI::None: CoreAssert(false,"VertexBuffer::Create : RendererAPI::None is currently not supported");
            case RendererAPI::OpenGL : return CreateScope<OpenGLIndexBuffer>(indices,count);
            default : CoreAssert(false,"VertexBuffer::Create : Unknown RendererAPI"); 
        }
    }
}