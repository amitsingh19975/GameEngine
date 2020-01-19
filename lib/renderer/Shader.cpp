#include "dark/renderer/Shader.hpp"
#include "dark/core/Core.hpp"
#include "dark/core/Log.hpp"
#include "dark/platform/openGL/OpenGLShader.hpp"
#include "dark/renderer/Renderer.hpp"

namespace dk{

    Ref<Shader> Shader::Create(std::string_view vertex, std::string_view fragment) {
        switch (Renderer::GetAPI()){
            case RendererAPI::API::None: CoreAssert(false,"Shader::Create : RendererAPI::None is currently not supported");
            case RendererAPI::API::OpenGL : return CreateRef<OpenGLShader>(vertex,fragment);
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
}