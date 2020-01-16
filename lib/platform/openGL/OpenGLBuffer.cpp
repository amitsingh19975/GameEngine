#include "dark/platform/openGL/OpenGLBuffer.hpp"
#include "dark/core/Log.hpp"

namespace dk{

//-------OpenGLVertexBuffer-----------------------------------//

    OpenGLVertexBuffer::OpenGLVertexBuffer( value_type* vertices, size_type size ){
        glGenBuffers(1, &m_rendererID);
        this->Bind();
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer() {
        glDeleteBuffers(1,&m_rendererID);
    }

    void OpenGLVertexBuffer::Bind() const noexcept {
        glBindBuffer(GL_ARRAY_BUFFER, m_rendererID);
    }

    void OpenGLVertexBuffer::UnBind() const noexcept {
        glBindBuffer(GL_ARRAY_BUFFER,0);
    }
    
//-------IndexBuffer--------------------------------------//

    OpenGLIndexBuffer::OpenGLIndexBuffer( value_type* indices, count_type count )
        : m_count(count) {
        glGenBuffers(1,&m_rendererID);
        this->Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(value_type), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer() {
        glDeleteBuffers(1,&m_rendererID);
    }

    void OpenGLIndexBuffer::Bind() const noexcept {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID);
    }

    void OpenGLIndexBuffer::UnBind() const noexcept {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }

}