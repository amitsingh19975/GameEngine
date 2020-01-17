#include "dark/renderer/Renderer.hpp"
#include "dark/renderer/RenderCommand.hpp"
#include "dark/core/Core.hpp"
#include "dark/renderer/VertexArray.hpp"

namespace dk{
    Ref<Renderer::SceneData> Renderer::s_sceneData = CreateRef<Renderer::SceneData>();

    void Renderer::BeginScene(OrthographicCamera& camera){
        Deref( s_sceneData ).viewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene(){

    }

    void Renderer::Submit( Ref<Shader> const& shader, Ref<VertexArray> const& vertexArray ){
        Deref(shader).Bind();
        Deref(shader).UploadUniformMat4("u_ViewProjection", Deref(s_sceneData).viewProjectionMatrix );
        Deref( vertexArray ).Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }


}