#if !defined(DK_VERTEX_ARRAY_HPP)
#define DK_VERTEX_ARRAY_HPP

#include "dark/core/Core.hpp"
#include "dark/renderer/Buffer.hpp"
#include "dark/renderer/Shader.hpp"

namespace dk{
    struct VertexArray{
        using size_type = size_t;
        using vertex_buffer_type = std::vector< Ref<VertexBuffer> >;
        using index_buffer_type = Ref<IndexBuffer>;

        virtual ~VertexArray() {}

        virtual void Bind() const noexcept = 0;
        virtual void UnBind() const noexcept = 0;

        virtual void AddVertexBuffer(Ref<VertexBuffer> const& vertexBuffer) noexcept = 0;
        virtual void SetIndexBuffer(Ref<IndexBuffer> const& indexBuffer) noexcept = 0;
        virtual vertex_buffer_type const& GetVertexBuffer() const noexcept = 0;
        virtual index_buffer_type const& GetIndexBuffer() const noexcept = 0;
        virtual void BindAttribute( Ref<Shader> const& ) const noexcept {}
        virtual void BindAttribute( size_type,  Ref<Shader> const& ) const noexcept{}
        static Scope<VertexArray> Create();

    };
}

#endif // DK_VERTEX_ARRAY_HPP
