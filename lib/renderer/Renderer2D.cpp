#include "dark/renderer/Renderer2D.hpp"
#include "dark/renderer/RenderCommand.hpp"
#include "dark/renderer/Buffer.hpp"
#include "dark/renderer/Shader.hpp"
#include "dark/renderer/VertexArray.hpp"
#include "dark/platform/openGL/OpenGLShader.hpp"

namespace dk{

    struct Renderer2DStorage{
        Ref<VertexArray>    QuadVertexArray;
        Ref<Shader>         QuadShader;
        Ref<Shader>         TextureShader;
        std::string         ShaderPath{"../assets/shaders/DefaultShader.glsl"};
        std::string         TextureShaderPath{"../assets/shaders/Texture.glsl"};
    };

    static Renderer2DStorage* s_Renderer2DStorageData = nullptr;

    void Renderer2D::Init(){

        s_Renderer2DStorageData = new Renderer2DStorage();

        typename VertexBuffer::value_type vertices[] = {
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            1.f,  0.0f, 0.0f, 1.0f, 0.0f,
            1.f,  1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f
        };

        auto vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));

        {
            BufferLayout lay = {
                {ShaderDataType::Float3, "a_Pos"},
                {ShaderDataType::Float2, "a_TextCoord"},
            };
            Deref(vertexBuffer).SetLayout(lay);
        }

        Deref(s_Renderer2DStorageData).QuadShader = Shader::Create(Deref(s_Renderer2DStorageData).ShaderPath);
        Deref(s_Renderer2DStorageData).TextureShader = Shader::Create(Deref(s_Renderer2DStorageData).TextureShaderPath);

        ClientLog::Info("Shader Compiled");

        typename IndexBuffer::value_type indices[] = {
            0,1,2,2,3,0
        };
        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices)/ sizeof(typename IndexBuffer::value_type));
        
        Deref(s_Renderer2DStorageData).QuadVertexArray = VertexArray::Create();
        Deref(Deref(s_Renderer2DStorageData).QuadVertexArray).AddVertexBuffer(vertexBuffer);
        Deref(Deref(s_Renderer2DStorageData).QuadVertexArray).SetIndexBuffer(indexBuffer);
        
        Deref( Deref(s_Renderer2DStorageData).TextureShader ).Bind();
        Deref( Deref(s_Renderer2DStorageData).TextureShader ).SetInt("u_Texture",0);
    }

    void Renderer2D::ShutDown(){
        delete s_Renderer2DStorageData;
    }

    void Renderer2D::BeginScene( OrthographicCamera const& camera ){
        Deref( Deref( s_Renderer2DStorageData ).QuadShader ).Bind();
        Deref( Deref( s_Renderer2DStorageData ).QuadShader ).SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix() );
        
        Deref( Deref( s_Renderer2DStorageData ).TextureShader ).Bind();
        Deref( Deref( s_Renderer2DStorageData ).TextureShader ).SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix() );
    }

    void Renderer2D::EndScene(){

    }

    void Renderer2D::SetShaderPath(std::string_view path){
        Deref(s_Renderer2DStorageData).ShaderPath = std::string(path);
    }

    void Renderer2D::SetTextureShaderPath(std::string_view path){
        Deref(s_Renderer2DStorageData).TextureShaderPath = std::string(path);
    }

    void Renderer2D::DrawQuad( glm::vec2 const& position, glm::vec2 const& size, Ref<Texture2D> const& texture){
        DrawQuad({position.x, position.y, 0.f}, size, texture);
    }

    void Renderer2D::DrawQuad( glm::vec3 const& position, glm::vec2 const& size, Ref<Texture2D> const& texture){
        Deref( Deref( s_Renderer2DStorageData ).TextureShader ).Bind();

        glm::mat4 transform = 
            glm::translate(glm::mat4(1.f), position) * 
            glm::scale(glm::mat4(1.f), { size.x, size.y, 1.0f });
            
        Deref( Deref( s_Renderer2DStorageData ).QuadShader ).SetMat4("u_Transform", transform );

        Deref( texture ).Bind();

        Deref( Deref( s_Renderer2DStorageData ).QuadVertexArray ).Bind();
        RenderCommand::DrawIndexed( Deref( s_Renderer2DStorageData ).QuadVertexArray );
    }

    void Renderer2D::DrawQuad( glm::vec2 const& position, glm::vec2 const& size, glm::vec4 const& color){
        DrawQuad({position.x, position.y, 0.f}, size, color);
    }

    void Renderer2D::DrawQuad( glm::vec3 const& position, glm::vec2 const& size, glm::vec4 const& color){
        Deref( Deref( s_Renderer2DStorageData ).QuadShader ).Bind();
        Deref( Deref( s_Renderer2DStorageData ).QuadShader ).SetFloat4("u_Color",color);

        glm::mat4 transform = 
            glm::translate(glm::mat4(1.f), position) * 
            glm::scale(glm::mat4(1.f), { size.x, size.y, 1.0f });

        Deref( Deref( s_Renderer2DStorageData ).QuadShader ).SetMat4("u_Transform", transform );

        Deref( Deref( s_Renderer2DStorageData ).QuadVertexArray ).Bind();
        RenderCommand::DrawIndexed( Deref( s_Renderer2DStorageData ).QuadVertexArray );
    }

}