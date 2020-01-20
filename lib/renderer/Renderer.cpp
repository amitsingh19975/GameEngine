#include "dark/renderer/Renderer.hpp"
#include "dark/renderer/Renderer2D.hpp"
#include "dark/renderer/RenderCommand.hpp"
#include "dark/core/Core.hpp"
#include "dark/renderer/VertexArray.hpp"
#include "dark/platform/openGL/OpenGLShader.hpp"

namespace dk{
    Ref<Renderer::SceneData> Renderer::s_sceneData = CreateRef<Renderer::SceneData>();

    void Renderer::Init(){
        RenderCommand::Init();
        Renderer2D::Init();
    }

    void Renderer::BeginScene(OrthographicCamera& camera){
        Deref( s_sceneData ).viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene(){

    }

    void Renderer::Submit( Ref<Shader> const& shader, Ref<VertexArray> const& vertexArray, glm::mat4 const& transform ){
        
        Deref(shader).Bind();
        Deref(shader).StaticCast<OpenGLShader>().UploadUniform("u_ViewProjection", Deref(s_sceneData).viewProjectionMatrix );
        Deref(shader).StaticCast<OpenGLShader>().UploadUniform("u_Transform",transform);

        Deref( vertexArray ).Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) noexcept{
        RenderCommand::SetViewport(0,0,width,height);
    }

}