#include "dark/platform/openGL/OpenGLShader.hpp"
#include "dark/core/Core.hpp"
#include <fstream>
#include <filesystem>

namespace dk{

    static GLenum ShaderTypeFromString(std::string_view type){
        if( type == "vertex" ) return GL_VERTEX_SHADER;
        else if ( type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;
        else{
            CoreAssert(false,"ShaderTypeFromString: unknown shader type");
            return 0;
        }
    }

    OpenGLShader::OpenGLShader( std::string_view path )
        : m_name( std::filesystem::path(path).stem() )
    {
        std::ifstream file(path.data(), std::ios::binary);
        if( file.bad() ){
            CoreLog::Error("OpenGLShader::OpenGLShader: file ( {0} ) not found", path);
        }else{
            std::stringstream ss;
            ss << file.rdbuf();
            file.close();
            auto shaders = PreProcess(ss);
            Compile(shaders);
        }   
    }

    OpenGLShader::OpenGLShader( std::string_view name, std::string_view path )
        : m_name( name )
    {
        std::ifstream file(path.data(), std::ios::binary);
        if( file.bad() ){
            CoreLog::Error("OpenGLShader::OpenGLShader: file ( {0} ) not found", path);
        }else{
            std::stringstream ss;
            ss << file.rdbuf();
            file.close();
            auto shaders = PreProcess(ss);
            Compile(shaders);
        }   
    }

    OpenGLShader::OpenGLShader(std::string_view name, std::string_view vertex, std::string_view fragment)
        : m_name(name)
    {
        Compile({
            {GL_VERTEX_SHADER, std::string(vertex)}, 
            {GL_FRAGMENT_SHADER, std::string(fragment)}
        });
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_renderID);
    }

    void OpenGLShader::Bind() const noexcept{
        glUseProgram(m_renderID);
    }

    void OpenGLShader::UnBind() const noexcept{
        glUseProgram(0);   
    }

    void OpenGLShader::BindAttribute(int location, std::string_view name) const noexcept{
        glBindAttribLocation(m_renderID,location,name.data());
    }

    std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(std::stringstream& ss ){
        std::unordered_map<GLenum, std::string> ret;
        std::string data = ss.str();
        char const typeToken[] = "#type";
        auto typeTokenLength = sizeof(typeToken) - 1;
        auto pos = data.find(typeToken,0);
        
        while(pos != std::string::npos){
            auto eol = data.find_first_of("\r\n",pos);

            CoreAssert(eol != std::string::npos, "OpenGLShader::PreProcess: Syntax Error");
            
            auto beg = pos + typeTokenLength + 1;

            auto type = data.substr(beg, eol - beg);
            
            CoreAssert(type == "vertex" || type == "pixel" || type == "fragment", "OpenGLShader::PreProcess: shader not support");

            auto nextLinePos = data.find_first_not_of("\r\n",eol);
            
            pos = data.find(typeToken, nextLinePos);

            ret[ShaderTypeFromString(type)] = (pos == std::string::npos) ? 
                data.substr(nextLinePos) 
                : data.substr(nextLinePos, pos - nextLinePos);
        }
        return ret;
    }
    
    void OpenGLShader::Compile( std::unordered_map<GLenum, std::string> const& shaders ){
        auto check_shader = []( auto ShaderID, std::string_view type ){
            auto isCompiled = 0;
            glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &isCompiled);
            if( !isCompiled ){
                int max_len = 0;
                glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &max_len);

                std::string info(' ',max_len);

                glGetShaderInfoLog(ShaderID, max_len, &max_len, &info[0]);

                glDeleteShader(ShaderID);

                CoreLog::Error("Unable to Compile {0} OpenGLShader\n{1}",type,info);
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

        std::vector<uint32_t> shaderIDs;

        for( auto const& [type, shaderString] : shaders ){
            uint32_t shaderID{glCreateShader(type)};
            std::string name;

            if( type == GL_VERTEX_SHADER ){
                name = "Vertex";
            }else if ( type == GL_FRAGMENT_SHADER ){
                name = "Fragment";
            }

            shaderIDs.push_back(shaderID);

            char const* src = shaderString.c_str();
            int shaderSize = shaderString.size();

            glShaderSource(shaderID,1, &src, &shaderSize);

            glCompileShader(shaderID);

            if( !check_shader(shaderID,name) ){
                exit(1);
            }

            CoreLog::Info("{0} OpenGLShader Compiled Successfully",name);
        }

        m_renderID = glCreateProgram();

        for(auto const& id : shaderIDs ){
            glAttachShader(m_renderID,id);
        }
        
        glLinkProgram(m_renderID);

        if( !check_program( m_renderID ) ){
            for(auto const& id : shaderIDs ){
                glDeleteShader(id);
            }
            exit(2);
        }
        

        CoreLog::Info("Program Linked Successfully");

        for(auto const& id : shaderIDs ){
            glDetachShader(m_renderID, id);
        }
    }

}