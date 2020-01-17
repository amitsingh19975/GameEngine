#if !defined(DK_SHADER_HPP)
#define DK_SHADER_HPP

#include <string>

namespace dk{
    struct Shader {
        Shader( std::string_view vertex, std::string_view fragment);
        ~Shader();

        void BindAttribute(int location, std::string_view name) const noexcept;

        void Bind() const noexcept;
        void UnBind() const noexcept;

        constexpr auto GetRenderID() const noexcept{ return m_renderID; }

    private:
        uint32_t m_renderID;
    };
}

#endif // DK_SHADER_HPP