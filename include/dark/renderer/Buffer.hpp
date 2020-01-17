#if !defined(DK_BUFFERS_HPP)
#define DK_BUFFERS_HPP

#include "dark/core/Core.hpp"
#include "dark/core/Log.hpp"

namespace dk{

    enum class ShaderDataType{
        None = 0,
        Float, Float2, Float3, Float4,
        Mat2, Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };

    constexpr static uint32_t ShaderDataTypeSize( ShaderDataType type ) noexcept {

        switch ( type ){
            case ShaderDataType::Float  : return 4;
            case ShaderDataType::Float2 : return 4 * 2;
            case ShaderDataType::Float3 : return 4 * 3;
            case ShaderDataType::Float4 : return 4 * 4;
            case ShaderDataType::Mat2   : return 4 * 2 * 2;
            case ShaderDataType::Mat3   : return 4 * 3 * 3;
            case ShaderDataType::Mat4   : return 4 * 4 * 4;
            case ShaderDataType::Int    : return 4;
            case ShaderDataType::Int2   : return 4 * 2;
            case ShaderDataType::Int3   : return 4 * 3;
            case ShaderDataType::Int4   : return 4 * 4;
            case ShaderDataType::Bool   : return 1;
            default : {
                CoreAssert(false, "Unknown Data Type");
                return 0;
            }
        }
    }

    struct BufferElements{
        using offset_type = uint32_t;
        using size_type = uint32_t;
        using count_type = uint32_t;
        using name_type = std::string;

        name_type       name;
        ShaderDataType  type;
        offset_type     offset;
        size_type       size;
        bool            normalized{false};

        BufferElements() = default;

        BufferElements( ShaderDataType type, std::string_view name, bool normalized = false )
            : name(name), type(type), offset(0), size(ShaderDataTypeSize(type)), normalized(normalized)
        {}

        count_type GetComponentCount() const noexcept {
            switch ( type ){
                case ShaderDataType::Float  : 
                case ShaderDataType::Int    : return 1;
                case ShaderDataType::Float2 : 
                case ShaderDataType::Int2   : return 2;
                case ShaderDataType::Float3 : 
                case ShaderDataType::Int3   : return 3;
                case ShaderDataType::Float4 : 
                case ShaderDataType::Mat2   : return 2 * 2;
                case ShaderDataType::Mat3   : return 3 * 3;
                case ShaderDataType::Mat4   : return 4 * 4;
                case ShaderDataType::Int4   : return 4;
                case ShaderDataType::Bool   : return 1;
                default : {
                    CoreAssert(false, "Unknown Data Type");
                    return 0;
                }
            }
        }
    };

    struct BufferLayout{
        using value_type = BufferElements;
        using base_type = std::vector<BufferElements>;
        using offset_type = float;
        using size_type = uint32_t;
        using count_type = uint32_t;
        using name_type = std::string;
        using iterator = typename base_type::iterator;
        using const_iterator = typename base_type::const_iterator;
        using reverse_iterator = typename base_type::reverse_iterator;
        using const_reverse_iterator = typename base_type::const_reverse_iterator;
        
        BufferLayout() = default;

        BufferLayout( std::initializer_list<value_type> const& li) 
            : m_elements(std::move(li)) 
        {
            CalculateOffsetAndStride();
        }

        constexpr base_type const& GetElements() const noexcept { return m_elements; }
        constexpr size_type GetStride() const noexcept { return m_stride; }
        iterator begin() { return m_elements.begin(); }
        iterator end() { return m_elements.end(); }
        reverse_iterator rbegin() { return m_elements.rbegin(); }
        reverse_iterator rend() { return m_elements.rend(); }
        
        const_iterator begin() const { return m_elements.begin(); }
        const_iterator end() const { return m_elements.end(); }
        const_reverse_iterator rbegin() const { return m_elements.rbegin(); }
        const_reverse_iterator rend() const { return m_elements.rend(); }

        constexpr auto empty() const noexcept { return m_elements.empty(); }

    private:
        void CalculateOffsetAndStride() noexcept{
            offset_type offset = 0;
            m_stride = 0;
            for( auto & el : m_elements ){
                el.offset = offset;
                offset += el.size;
                m_stride += el.size;
            }
        }
    private:
        base_type m_elements;
        size_type m_stride{0};
    };

    struct VertexBuffer{
        using value_type = float;
        using size_type = uint32_t;
        using renderer_id_type = uint32_t;

        constexpr static auto value_size = sizeof(value_type);

        virtual ~VertexBuffer() {}

        virtual void Bind() const noexcept = 0;
        virtual void UnBind() const noexcept = 0;

        virtual BufferLayout const& GetLayout() const noexcept= 0;
        virtual void SetLayout( BufferLayout const& layout) noexcept= 0;

        static Ref<VertexBuffer> Create( float* vertices, uint32_t size );

    };

    struct IndexBuffer{
        using value_type = uint32_t;
        using count_type = uint32_t;
        using renderer_id_type = uint32_t;
        
        constexpr static auto value_size = sizeof(value_type);

        virtual ~IndexBuffer() {}

        virtual void Bind() const noexcept = 0;
        virtual void UnBind() const noexcept = 0;

        virtual value_type GetCount() const noexcept = 0;
        
        static Ref<IndexBuffer> Create( value_type* indices, count_type count );
    };
}

#endif // DK_BUFFERS_HPP
