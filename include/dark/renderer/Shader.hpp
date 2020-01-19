#if !defined(DK_SHADER_HPP)
#define DK_SHADER_HPP

#include "dark/core/Core.hpp"
#include "glm/glm.hpp"

namespace dk{
    struct Shader {
        
        virtual ~Shader(){}

        virtual void Bind() const noexcept = 0;
        virtual void UnBind() const noexcept = 0;

        template< typename T>
        constexpr auto& GetShader() noexcept{
            return static_cast<T&>(*this);
        }
        template< typename T>
        constexpr auto const& GetShader() const noexcept{
            return static_cast<T const&>(*this);
        }

        static Ref<Shader> Create(std::string_view vertex, std::string_view fragment);
        static Ref<Shader> Create(std::string_view path );
    };
}

#endif // DK_SHADER_HPP