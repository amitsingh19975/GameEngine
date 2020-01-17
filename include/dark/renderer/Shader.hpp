#if !defined(DK_SHADER_HPP)
#define DK_SHADER_HPP

#include <string>
#include "glm/glm.hpp"

namespace dk{
    struct Shader {
        Shader( std::string_view vertex, std::string_view fragment);
        ~Shader();

        void BindAttribute(int location, std::string_view name) const noexcept;

        void Bind() const noexcept;
        void UnBind() const noexcept;

        void UploadUniformMat4(std::string_view name, glm::mat4 const& uniform) const noexcept;

        constexpr auto GetRenderID() const noexcept{ return m_renderID; }

    private:
        uint32_t m_renderID;
    };
}

#endif // DK_SHADER_HPP