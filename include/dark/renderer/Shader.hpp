#if !defined(DK_SHADER_HPP)
#define DK_SHADER_HPP

#include "dark/core/Core.hpp"
#include "glm/glm.hpp"

namespace dk{
    struct Shader {
        
        virtual ~Shader(){}

        virtual void Bind() const noexcept = 0;
        virtual void UnBind() const noexcept = 0;
        virtual void SetInt(std::string_view name, int) = 0;
        virtual void SetFloat4(std::string_view name, glm::vec4 const&) = 0;
        virtual void SetFloat3(std::string_view name, glm::vec3 const&) = 0;
        virtual void SetFloat2(std::string_view name, glm::vec2 const&) = 0;
        virtual void SetMat4(std::string_view name, glm::mat4 const&) = 0;

        virtual std::string const& GetName() const noexcept = 0;

        template< typename T>
        constexpr auto& StaticCast() noexcept{
            return static_cast<T&>(*this);
        }
        template< typename T>
        constexpr auto const& StaticCast() const noexcept{
            return static_cast<T const&>(*this);
        }

        static Ref<Shader> Create(std::string_view name, std::string_view vertex, std::string_view fragment);
        static Ref<Shader> Create(std::string_view path );
        static Ref<Shader> Create(std::string_view name, std::string_view path );
    };

    struct ShaderLibrary{
        
        bool Add(Ref< Shader > const& shader);
        Ref<Shader> Load(std::string_view filePath);
        Ref<Shader> Load(std::string_view name, std::string_view filePath);
        void LoadFolder(std::string_view filePath);

        Ref<Shader> Get(std::string_view name);
        template<typename... Args>
        Ref<Shader> EmplaceShader(std::string_view name, Args&&... args){
            if( Exist(name) ){
                CoreLog::Error("ShaderLibrary::EmplaceShader: shader already exists");
                return m_shader[std::string(name)];
            }else{
                return m_shader[std::string(name)] = Shader::Create(name, std::forward<Args>(args)...);
            }
        }

        bool Exist(std::string_view name) const noexcept;

    private:
        std::unordered_map<std::string, Ref< Shader > > m_shader;
    };
}

#endif // DK_SHADER_HPP