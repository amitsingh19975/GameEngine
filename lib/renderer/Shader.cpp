#include "dark/renderer/Shader.hpp"
#include "dark/core/Core.hpp"
#include "dark/core/Log.hpp"
#include "dark/platform/openGL/OpenGLShader.hpp"
#include "dark/renderer/Renderer.hpp"
#include <filesystem>

namespace dk{

    Ref<Shader> Shader::Create(std::string_view name, std::string_view vertex, std::string_view fragment) {
        switch (Renderer::GetAPI()){
            case RendererAPI::API::None: CoreAssert(false,"Shader::Create : RendererAPI::None is currently not supported");
            case RendererAPI::API::OpenGL : return CreateRef<OpenGLShader>(name,vertex,fragment);
            default : CoreAssert(false,"Shader::Create : Unknown RendererAPI"); 
        }
    }

    Ref<Shader> Shader::Create(std::string_view path) {
        switch (Renderer::GetAPI()){
            case RendererAPI::API::None: CoreAssert(false,"Shader::Create : RendererAPI::None is currently not supported");
            case RendererAPI::API::OpenGL : return CreateRef<OpenGLShader>(path);
            default : CoreAssert(false,"Shader::Create : Unknown RendererAPI"); 
        }
    }

    Ref<Shader> Shader::Create(std::string_view name, std::string_view path) {
        switch (Renderer::GetAPI()){
            case RendererAPI::API::None: CoreAssert(false,"Shader::Create : RendererAPI::None is currently not supported");
            case RendererAPI::API::OpenGL : return CreateRef<OpenGLShader>(name, path);
            default : CoreAssert(false,"Shader::Create : Unknown RendererAPI"); 
        }
    }


    bool ShaderLibrary::Add(Ref< Shader > const& shader){
        auto name = Deref(shader).GetName();
        if( m_shader.find(name) != m_shader.end() ){
            CoreLog::Error("ShaderLibrary::Add: shader name already exist");
            return false;
        }else{
            m_shader[name] = shader;
            CoreLog::Info("ShaderLibrary::Add: {0} is successfully added", Deref(shader).GetName());
            return true;
        }
    }

    Ref<Shader> ShaderLibrary::Load(std::string_view filePath){
        auto shader = Shader::Create(filePath);
        if( !Add(shader) ){
            return m_shader[Deref(shader).GetName()];
        }
        CoreLog::Info("ShaderLibrary::Load: {0} is loaded", Deref(shader).GetName());
        return shader;
    }

   void ShaderLibrary::LoadFolder(std::string_view filePath){
        for(auto const& file : std::filesystem::directory_iterator(filePath) ){
            if( Load(file.path().c_str()) == nullptr ){
                CoreLog::Error("ShaderLibrary::LoadFolder: unable to loaded {0}", file.path().c_str());
            }else{
                CoreLog::Info("ShaderLibrary::LoadFolder: {0} is loaded", file.path().c_str());
            }
        }
    }

    Ref<Shader> ShaderLibrary::Load(std::string_view name, std::string_view filePath){
        auto nm = std::string(name);
        if( m_shader.find(nm) != m_shader.end() ){
            CoreLog::Error("ShaderLibrary::Add: shader name already exist");
            return m_shader[nm];
        }else{
            m_shader[nm] = Shader::Create(name, filePath);
            CoreLog::Info("ShaderLibrary::Load: {0} is loaded", Deref(m_shader[nm]).GetName());
            return m_shader[nm];
        }
    }

    Ref<Shader> ShaderLibrary::Get(std::string_view name){
        auto nm = std::string(name);
        if( m_shader.find(nm) != m_shader.end() ){
            return m_shader[nm];
        }else{
            CoreLog::Error("ShaderLibrary::Add: shader does not exist");
            return nullptr;
        }
    }
    
    bool ShaderLibrary::Exist(std::string_view name) const noexcept{
        auto nm = std::string(name);
        return m_shader.find(nm) != m_shader.end();
    }

}