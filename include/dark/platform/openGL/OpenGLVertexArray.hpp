#if !defined(DK_OPENGL_VERTEX_ARRAY)
#define DK_OPENGL_VERTEX_ARRAY

#include "dark/renderer/VertexArray.hpp"

namespace dk{
    struct OpenGLVertexArray : VertexArray {
        using renderer_id_type = uint32_t;
        using vertex_buffer_type = typename VertexArray::vertex_buffer_type;
        using index_buffer_type = typename VertexArray::index_buffer_type;
        using size_type = size_t;


        OpenGLVertexArray();
        virtual ~OpenGLVertexArray() {}

        void Bind() const noexcept override;
        void UnBind() const noexcept override;

        void AddVertexBuffer(Ref<VertexBuffer> const& vertexBuffer) noexcept override;
        void SetIndexBuffer(Ref<IndexBuffer> const& indexBuffer) noexcept override;
        void BindAttribute( Ref<Shader> const& shader ) const noexcept override;
        void BindAttribute( size_type idx,  Ref<Shader> const& shader ) const noexcept override;
        inline vertex_buffer_type const& GetVertexBuffer() const noexcept override { return m_vertexBuffer;}
        inline index_buffer_type const& GetIndexBuffer() const noexcept override { return m_indexBuffer;}
    private:
        vertex_buffer_type m_vertexBuffer;
        Ref<IndexBuffer> m_indexBuffer;
        renderer_id_type m_rendererID;
    };
}

#endif // DK_OPENGL_VERTEX_ARRAY
