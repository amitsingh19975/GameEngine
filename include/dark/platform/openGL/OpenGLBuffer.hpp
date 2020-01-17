#if !defined(DK_OPENGL_BUFFER_HPP)
#define DK_OPENGL_BUFFER_HPP

#include "dark/renderer/Buffer.hpp"

namespace dk {
    
    struct OpenGLVertexBuffer : VertexBuffer {
        
        using super_type = VertexBuffer;
        using value_type = typename super_type::value_type;
        using size_type = typename super_type::size_type;
        using renderer_id_type = typename super_type::renderer_id_type;
        using super_type::value_size;

        OpenGLVertexBuffer( value_type* vertices, size_type size );

        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const noexcept override;
        virtual void UnBind() const noexcept override;

        inline BufferLayout const& GetLayout() const noexcept override { return m_layout; }
        inline void SetLayout( BufferLayout const& layout) noexcept override { m_layout = layout;}

    private:
        renderer_id_type m_rendererID;
        BufferLayout m_layout;
    };
    
    struct OpenGLIndexBuffer : IndexBuffer {
        
        using super_type = IndexBuffer;
        using value_type = typename super_type::value_type;
        using count_type = typename super_type::count_type;
        using renderer_id_type = typename super_type::renderer_id_type;
        using super_type::value_size;

        OpenGLIndexBuffer( value_type* indices, count_type count );

        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const noexcept override;
        virtual void UnBind() const noexcept override;

        inline uint32_t GetCount() const noexcept override{ return m_count; }

    private:
        renderer_id_type m_rendererID;
        count_type m_count;
    };
}

#endif // DK_OPENGL_BUFFER_HPP