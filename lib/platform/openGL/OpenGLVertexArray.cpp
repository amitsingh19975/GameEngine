#include "dark/platform/openGL/OpenGLVertexArray.hpp" 
#include "dark/platform/openGL/OpenGLShader.hpp" 

namespace dk {

    static GLenum ShaderDataTypeToOpenGLType( ShaderDataType type){
        switch ( type ){
            case ShaderDataType::Float  : 
            case ShaderDataType::Float2 : 
            case ShaderDataType::Float3 : 
            case ShaderDataType::Mat2   : 
            case ShaderDataType::Mat3   : 
            case ShaderDataType::Mat4   : 
            case ShaderDataType::Float4 : return GL_FLOAT;
            case ShaderDataType::Int    : 
            case ShaderDataType::Int2   : 
            case ShaderDataType::Int3   : 
            case ShaderDataType::Int4   : return GL_INT;
            case ShaderDataType::Bool   : return GL_BOOL;
            default : {
                CoreAssert(false, "Unknown Data Type");
                return GL_NONE;
            }
        }
    }

    OpenGLVertexArray::OpenGLVertexArray() {
        DKGenVertexArrays(1,&m_rendererID);
        DKBindVertexArray(m_rendererID);
    }

    void OpenGLVertexArray::Bind() const noexcept{
        DKBindVertexArray(m_rendererID);
    };
    void OpenGLVertexArray::UnBind() const noexcept {
        DKBindVertexArray(0);
    };

    void OpenGLVertexArray::AddVertexBuffer(Ref<VertexBuffer> const& vertexBuffer) noexcept {
        DKBindVertexArray(m_rendererID);
        vertexBuffer->Bind();
        auto idx = 0ul;
        
        auto layout = Deref(vertexBuffer).GetLayout();
        
        CoreAssert(!layout.empty(), "OpenGLVertexArray::AddVertexBuffer: Buffer Layout is Empty");
        
        for(auto const& el : layout ){
            glEnableVertexAttribArray(idx);
            glVertexAttribPointer(idx, el.GetComponentCount() 
                ,ShaderDataTypeToOpenGLType(el.type) 
                ,el.normalized ? GL_TRUE : GL_FALSE 
                , layout.GetStride() 
                ,reinterpret_cast<const void*>(el.offset)
            );
            ++idx;
        }
        m_vertexBuffer.push_back(vertexBuffer);

    };

    void OpenGLVertexArray::SetIndexBuffer(Ref<IndexBuffer> const& indexBuffer) noexcept {
        DKBindVertexArray(m_rendererID);
        Deref(indexBuffer).Bind();
        m_indexBuffer = indexBuffer;
    };

    void OpenGLVertexArray::BindAttribute( Ref<Shader> const& shader ) const noexcept{
        CoreAssert( !m_vertexBuffer.empty(), "OpenGLVertexArray::BindAttribute : No Vertex Buffer exists");
        this->BindAttribute(m_vertexBuffer.size() - 1,shader);
    }

    void OpenGLVertexArray::BindAttribute( size_type idx,  Ref<Shader> const& shader ) const noexcept{
        CoreAssert(idx >= 0 && idx < m_vertexBuffer.size(), "OpenGLVertexArray::BindAttribute : Out of bound access");
        auto layout = Deref(m_vertexBuffer[idx]).GetLayout();
        for( auto const& el :  layout ){
            Deref(shader).GetShader<OpenGLShader>().BindAttribute(el.offset,el.name);
        }
    }

}