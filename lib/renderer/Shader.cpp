#include "dark/renderer/Shader.hpp"
#include "dark/core/Core.hpp"
#include "dark/core/Log.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace dk{
    Shader::Shader(std::string_view vertex, std::string_view fragment){
        
        auto check_shader = []( auto ShaderID, std::string_view type ){
            auto isCompiled = 0;
            glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &isCompiled);
            if( !isCompiled ){
                int max_len = 0;
                glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &max_len);

                std::string info(' ',max_len);

                glGetShaderInfoLog(ShaderID, max_len, &max_len, &info[0]);

                glDeleteShader(ShaderID);

                CoreLog::Error("Unable to Compile {0} Shader\n{1}",type,info);
                return false;
            }
            return true;
        };
        auto check_program = []( auto program ){
            auto isLinked = 0;
            glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
            if( !isLinked ){
                int max_len = 0;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_len);

                std::string info(' ',max_len);

                glGetProgramInfoLog(program, max_len, &max_len, &info[0]);

                glDeleteProgram(program);

                CoreLog::Error("Unable to Link Program\n{1}",info);
                return false;
            }
            return true;
        };
        
        auto vertexShader = glCreateShader(GL_VERTEX_SHADER);
        
        int vsz = vertex.size();
        int fsz = fragment.size();
        char const* src = vertex.data();
        glShaderSource(vertexShader,1, &src, &vsz);
        glCompileShader(vertexShader);

        if( !check_shader(vertexShader,"Vertex") ){
            exit(1);
        }
        CoreLog::Info("Vertex Shader Compiled Successfully");
        auto fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        src = fragment.data();
        glShaderSource(fragmentShader,1, &src, &fsz);
        glCompileShader(fragmentShader);

        if( !check_shader(fragmentShader, "Fragment") ){
            glDeleteShader(vertexShader);
            exit(2);
        }
        CoreLog::Info("Fragment Shader Compiled Successfully");

        m_renderID = glCreateProgram();
        glAttachShader(m_renderID,vertexShader);
        glAttachShader(m_renderID,fragmentShader);
        glLinkProgram(m_renderID);

        if( !check_program( m_renderID ) ){
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);
            exit(3);
        }
        
        CoreLog::Info("Program Linked Successfully");

        glDetachShader(m_renderID, vertexShader);
        glDetachShader(m_renderID, fragmentShader);
    }

    Shader::~Shader() {
        glDeleteProgram(m_renderID);
    }

    void Shader::Bind() const noexcept{
        glUseProgram(m_renderID);
    }

    void Shader::UnBind() const noexcept{
        glUseProgram(0);   
    }

    void Shader::BindAttribute(int location, std::string_view name) const noexcept{
        glBindAttribLocation(m_renderID,location,name.data());
    }

    void Shader::UploadUniformMat4(std::string_view name, glm::mat4 const& uniform) const noexcept{
        auto location = glGetUniformLocation(m_renderID, name.data());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr( uniform ) );
    }

}