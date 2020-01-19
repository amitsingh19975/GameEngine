#include <Dark.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include "dark/platform/openGL/OpenGLShader.hpp"
#include "dark/platform/openGL/OpenGLBuffer.hpp"
// #include "dark/platform/openGL/OpenGLTexture.hpp"
 
struct ExLayer : dk::Layer{
    ExLayer() 
        : Layer("ExLayer")
        , m_camera(-1.6f, 1.6f, -1.f, 1.f)
    {
       


        typename dk::VertexBuffer::value_type vertices[5 * 4] = {
            0.0f, 0.0f, 0.0f, 0,0,
            1.f,  0.0f, 0.0f, 1,0,
            1.f,  1.0f, 0.0f, 1,1,
            0.0f, 1.0f, 0.0f, 0,1
        };

        auto vertexBuffer = dk::OpenGLVertexBuffer::Create(vertices);

        {
            dk::BufferLayout lay = {
                {dk::ShaderDataType::Float3, "a_Pos"},
                {dk::ShaderDataType::Float2, "a_TextCoord"}
            };
            Deref(vertexBuffer).SetLayout(lay);
        }

        m_shaderLibrary.LoadFolder("../assets/shaders");
        
        auto Tshader = m_shaderLibrary.Get("Texture");
        auto SqShader = m_shaderLibrary.Get("SquareShader");

        dk::ClientLog::Info("Shader Compiled");

        typename dk::IndexBuffer::value_type indices[] = {
            0,1,2,2,3,0
        };
        auto indexBuffer = dk::OpenGLIndexBuffer::Create(indices);
        
        typename dk::IndexBuffer::value_type Tindices[] = {
            0,1,2
        };
        auto TindexBuffer = dk::OpenGLIndexBuffer::Create(Tindices);
        
        m_vertexArray = dk::VertexArray::Create();
        Deref(m_vertexArray).AddVertexBuffer(vertexBuffer);
        Deref(m_vertexArray).SetIndexBuffer(indexBuffer);

        // m_TvertexArray = dk::VertexArray::Create();
        // Deref(m_TvertexArray).AddVertexBuffer(vertexBuffer);
        // Deref(m_TvertexArray).SetIndexBuffer(TindexBuffer);
        dk::ClientLog::Info("vertex array is initialization is completed");
        
        m_texture1 = dk::Texture2D::Create("../assets/textures/checker_board.png");
        m_texture2 = dk::Texture2D::Create("../assets/textures/space_ship.png");
        
        dk::Deref(Tshader).Bind();
        dk::Deref(Tshader).GetShader<dk::OpenGLShader>().UploadUniform("u_Texture",0);
        // Deref(m_vertexArray).BindAttribute(SqShader);

    }

    void OnUpdate( dk::Timestep ts ) override{
        m_ts = ts;
        dk::RenderCommand::SetClearColor(0.1f,.1f,.1f, 1.f);
        dk::RenderCommand::Clear();

        if( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_S) ){
            m_pos[1] -= m_cameraSpeed * ts; 
        }else if ( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_A) ){
            m_pos[0] += m_cameraSpeed * ts; 
        }else if ( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_W) ){
            m_pos[1] += m_cameraSpeed * ts;
        }else if (dk::WindowsInput::IsKeyPressed(dk::DK_KEY_D)){
            m_pos[0] -= m_cameraSpeed * ts;
        }else if( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_R) ){
            m_rotate += m_rotationSpeed * ts;
        }else if (dk::WindowsInput::IsKeyPressed(dk::DK_KEY_L)){
            m_rotate -= m_rotationSpeed * ts;
        }if( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_UP) ){
            m_Tpos[1] -= m_cameraSpeed * ts; 
        }else if ( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_LEFT) ){
            m_Tpos[0] += m_cameraSpeed * ts; 
        }else if ( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_DOWN) ){
            m_Tpos[1] += m_cameraSpeed * ts;
        }else if (dk::WindowsInput::IsKeyPressed(dk::DK_KEY_RIGHT)){
            m_Tpos[0] -= m_cameraSpeed * ts;
        }

        m_camera.SetPostion(m_pos);
        m_camera.SetRotation(m_rotate);

        // glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
        // glm::vec4 blueColor(0.2f, 0.2f, 0.8f, 1.0f);
        auto Tshader = m_shaderLibrary.Get("Texture");
        auto SqShader = m_shaderLibrary.Get("SquareShader");
        dk::Deref(SqShader).Bind();
        dk::Deref(SqShader).GetShader<dk::OpenGLShader>().UploadUniform("u_Color",m_sq_col);
        dk::Deref(Tshader).GetShader<dk::OpenGLShader>().UploadUniform("u_TPos",m_Tpos);

        dk::Renderer::BeginScene(m_camera);
            glm::mat4 sc = glm::scale(glm::mat4(1.f), glm::vec3(.05f));
            auto sz = 10;
            // bool alter = false;
            for(auto y = 0; y < sz; ++y ){
                for (auto x = 0; x < sz; ++x){
                    glm::vec3 pos(x * .11f, y * .11f, 0.f);
                    glm::mat4 transform = glm::translate(glm::mat4(1.f),pos) * sc;
                    dk::Renderer::Submit(SqShader,m_vertexArray,transform);
                }
            }
            
            dk::Deref( m_texture1 ).Bind();
            
            dk::Renderer::Submit(Tshader,m_vertexArray,
                glm::scale(glm::mat4(1.f), glm::vec3(1.f))
            );

            dk::Deref( m_texture2 ).Bind();

            dk::Renderer::Submit(Tshader,m_vertexArray,
                glm::scale(glm::mat4(1.f), glm::vec3(m_scale)) * 
                glm::translate(glm::mat4(1), glm::vec3(-0.45,-0.25,0))
            );

        dk::Renderer::EndScene();

    }

    void ImGuiRender() override{
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Sqaure Color", glm::value_ptr(m_sq_col) );
        ImGui::SliderFloat2("offet", glm::value_ptr(m_Tpos),0, 1);
        ImGui::SliderFloat("Scale", &m_scale,0,1);
        ImGui::End();
    }

    void OnEvent( dk::EventBase& e) override{
        dk::EventDispatcher dis(e);
        dis.Dispatch<dk::MouseScrolledEvent>([&](dk::MouseScrolledEvent const& evt){
            auto [x,y] = std::make_pair( evt.GetXOffset(), evt.GetYOffset() );
            if( x > 0 ){
                m_pos[0] += m_cameraSpeed * m_ts;
            }else if ( x < 0 ){
                m_pos[0] -= m_cameraSpeed * m_ts;
            }
            
            if( y > 0 ){
                m_pos[1] += m_cameraSpeed * m_ts;
            }else if ( y < 0 ){
                m_pos[1] -= m_cameraSpeed * m_ts;
            }
            return false;
        });
    }

private:
    glm::vec3                   m_pos{0.5,0.5,0};
    glm::vec2                   m_Tpos{1,0};
    float                       m_scale{1};
    float                       m_rotate{0};
    float                       m_ts{0};
    float                       m_cameraSpeed{5};
    float                       m_rotationSpeed{180}; 
    glm::vec3                   m_sq_col{0.2f,0.8f,0.3f};
    dk::OrthographicCamera      m_camera;
    dk::Ref<dk::VertexArray>    m_vertexArray;
    dk::Ref<dk::VertexArray>    m_TvertexArray;
    dk::Ref<dk::Texture2D>      m_texture1;
    dk::Ref<dk::Texture2D>      m_texture2;
    dk::ShaderLibrary           m_shaderLibrary;
};


struct Sandbox : public dk::Dark{
    Sandbox() {
        
        PushLayer(dk::CreateRef<ExLayer>());
    }

    ~Sandbox(){

    }
};

dk::Scope<dk::Dark> dk::CreateApplication(){
    return dk::CreateScope<Sandbox>();
}