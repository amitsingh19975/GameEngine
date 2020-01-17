#include <Dark.hpp>
 
struct ExLayer : dk::Layer{
    ExLayer() 
        : Layer("ExLayer")
        , m_camera(-1.f, 1.f, -.7f, .7f)
    {
        std::string vertexSrc = R"(
            attribute vec3 a_Pos;
            attribute vec4 a_Col;
            varying vec4 v_Col;

            uniform mat4 u_ViewProjection;

            void main(){
                v_Col = a_Col;
                gl_Position = u_ViewProjection * vec4(a_Pos ,1.0);
            }
        )";

        std::string fragmentSrc = R"(
            varying vec4 v_Col;
            void main(){
                gl_FragColor = v_Col;
            }
        )";

        typename dk::VertexBuffer::value_type vertices[4 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.f,
             0.5f, -0.5f, 0.0f, 0.5f, 0.8f, 0.2f, 1.f,
             0.5f,  0.5f, 0.0f, 0.2f, 0.3f, 0.6f, 1.f,
            -0.5f,  0.5f, 0.0f, 0.5f, 0.3f, 0.6f, 1.f
        };

        auto vertexBuffer = dk::VertexBuffer::Create(vertices,sizeof(vertices));
        {
            dk::BufferLayout lay = {
                {dk::ShaderDataType::Float3, "a_Pos"},
                {dk::ShaderDataType::Float4, "a_Color"}
            };
            Deref(vertexBuffer).SetLayout(lay);
        }

        m_shader = dk::CreateScope<dk::Shader>(vertexSrc, fragmentSrc);

        dk::CoreLog::Info("Shader Compiled");

        typename dk::IndexBuffer::value_type indices[] = {
            0,1,2,2,3,0
        };
        auto indexBuffer = dk::IndexBuffer::Create(indices, sizeof(indices) / dk::IndexBuffer::value_size);
        
        m_vertexArray = dk::VertexArray::Create();
        Deref(m_vertexArray).AddVertexBuffer(vertexBuffer);
        Deref(m_vertexArray).SetIndexBuffer(indexBuffer);
        // Deref(m_vertexArray).BindAttribute(m_shader);

    }

    void OnUpdate( dk::Timestep ts ) override{

        dk::RenderCommand::SetClearColor(0.1f,.1f,.1f, 1.f);
        dk::RenderCommand::Clear();

        if( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_W) ){
            m_pos[1] -= 0.1 * ts; 
        }else if ( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_A) ){
            m_pos[0] += 0.1 * ts; 
        }else if ( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_S) ){
            m_pos[1] += 0.1 * ts;
        }else if (dk::WindowsInput::IsKeyPressed(dk::DK_KEY_D)){
            m_pos[0] -= 0.1 * ts;
        }else if( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_R) ){
            m_rotate += 1 * ts;
        }else if (dk::WindowsInput::IsKeyPressed(dk::DK_KEY_L)){
            m_rotate -= 1 * ts;
        }

        m_camera.SetPostion(m_pos);
        m_camera.SetRotation(m_rotate);

        dk::Renderer::BeginScene(m_camera);

            dk::Renderer::Submit(m_shader,m_vertexArray);

        dk::Renderer::EndScene();

    }

    void OnEvent( dk::EventBase& ) override{
        
    }

private:
    glm::vec3                   m_pos{0,0,0};
    float                       m_rotate{0};
    dk::Ref<dk::VertexArray>    m_vertexArray;
    dk::Ref<dk::Shader>         m_shader;
    dk::OrthographicCamera      m_camera;
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