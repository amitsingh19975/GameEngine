#if !defined(DK_OPENGL_SHADER_HPP)
#define DK_OPENGL_SHADER_HPP
#include "dark/renderer/Shader.hpp"
#include "dark/core/Log.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <type_traits>
#include <sstream>

namespace dk{
    struct OpenGLShader : Shader{
        
        OpenGLShader( std::string_view path );

        OpenGLShader( std::string_view name, std::string_view vertex, std::string_view fragment );
        
        OpenGLShader( std::string_view name, std::string_view path );
        
        virtual ~OpenGLShader();

        void BindAttribute(int location, std::string_view name) const noexcept;

        void Bind() const noexcept override;
        void UnBind() const noexcept override;

        inline std::string const& GetName() const noexcept override {
            return m_name;
        }

        template<typename T>
        void UploadUniform( std::string_view name, T const& uniformData) noexcept{
            
            auto location = GetLocation(name);
            
            if constexpr( std::is_same_v<T,glm::mat4> ){
                glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr( uniformData ) );
            }else if constexpr( std::is_same_v<T, glm::mat3> ){
                glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr( uniformData ) );
            }else if constexpr( std::is_same_v<T, glm::mat2> ){
                glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr( uniformData ) );
            }else if constexpr( std::is_same_v<T, glm::vec4> ){
                glUniform4f(location, uniformData.x, uniformData.y, uniformData.z, uniformData.w);
            }else if constexpr( std::is_same_v<T, glm::vec3> ){
                glUniform3f(location, uniformData.x, uniformData.y, uniformData.z);
            }else if constexpr( std::is_same_v<T, glm::vec2> ){
                glUniform2f(location, uniformData.x, uniformData.y);
            }else if constexpr( std::is_same_v<T, float> ){
                glUniform1f(location, uniformData);
            }else if constexpr( std::is_same_v<T, int> ){
                glUniform1f(location, uniformData);
            }else{
                CoreAssert(false, "OpenGLShader::UploadUniform : Invalid Type");
            }
        }

        constexpr auto GetRenderID() const noexcept{ return m_renderID; }
    private:
        inline uint32_t GetLocation( std::string_view name ) noexcept{
            std::string temp(name);
            uint32_t location;
            if( m_location.find(temp) != m_location.end() ){
                location = m_location[temp];
            }else{
                location = glGetUniformLocation(m_renderID, name.data());
                m_location[temp] = location;
            }
            return location;
        }
    
    std::unordered_map<GLenum, std::string> PreProcess(std::stringstream& ss );
    
    void Compile( std::unordered_map<GLenum, std::string> const& shaders );

    private:
        uint32_t                                    m_renderID;
        std::unordered_map<std::string, uint32_t>   m_location;
        std::string                                 m_name;
    };
}

#endif // DK_OPENGL_SHADER_HPP
