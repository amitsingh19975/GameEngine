#include "dark/DarkApp.hpp"
#include "dark/platform/WindowsInput.hpp"
#include "dark/renderer/Renderer.hpp"
#include "dark/renderer/RenderCommand.hpp"
namespace dk{

    Dark* Dark::s_instance = nullptr;

    Dark::Dark()
        : m_window(Window::Create())
        , m_imGuiLayer(new ImGuiLayer())
        , m_camera(-1.f, 1.f, -.7f, .7f)
    {
        CoreAssert(s_instance == nullptr,"Application is already initialized");
        s_instance = this;
        Deref(m_window).SetEventCallback(std::bind(&Dark::onEvent,this,std::placeholders::_1));
        PushOverlay(m_imGuiLayer);
        
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

        typename VertexBuffer::value_type vertices[4 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.f,
             0.5f, -0.5f, 0.0f, 0.5f, 0.8f, 0.2f, 1.f,
             0.5f,  0.5f, 0.0f, 0.2f, 0.3f, 0.6f, 1.f,
            -0.5f,  0.5f, 0.0f, 0.5f, 0.3f, 0.6f, 1.f
        };

        auto vertexBuffer = VertexBuffer::Create(vertices,sizeof(vertices));
        {
            BufferLayout lay = {
                {ShaderDataType::Float3, "a_Pos"},
                {ShaderDataType::Float4, "a_Color"}
            };
            Deref(vertexBuffer).SetLayout(lay);
        }

        m_shader = CreateScope<Shader>(vertexSrc, fragmentSrc);

        CoreLog::Info("Shader Compiled");

        typename IndexBuffer::value_type indices[] = {
            0,1,2,2,3,0
        };
        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / IndexBuffer::value_size);
        
        m_vertexArray = VertexArray::Create();
        Deref(m_vertexArray).AddVertexBuffer(vertexBuffer);
        Deref(m_vertexArray).SetIndexBuffer(indexBuffer);
        // Deref(m_vertexArray).BindAttribute(m_shader);


    }
    
    Dark::~Dark(){}

    void Dark::onEvent( EventBase& e ){
        EventDispatcher disp(e);
        // CoreLog::Info(e);
        
        disp.Dispatch<WindowCloseEvent>(
            std::bind(&Dark::onWindowClose,this,std::placeholders::_1)
        );
        
        std::for_each(m_layerStack.rbegin(), m_layerStack.rend(),[&e]( auto& layer) {
            Deref(layer).OnEvent(e);
            if( e.Handled ) return;
        });
    }

    void Dark::Run(){
        CoreLog::Info("Starting Window");
        
        glm::vec3 pos(0,0,0);
        float rotate = 0;

        while(m_running){
            // float time = SDL_GetTicks()/ 1000.f;
            // Timestep ts = time - m_lastFrame;
            // m_lastFrame = time;

            RenderCommand::SetClearColor(0.1f,.1f,.1f, 1.f);
            RenderCommand::Clear();

            if( WindowsInput::IsKeyPressed(DK_KEY_W) ){
                pos[1] -= 0.1; 
            }else if ( WindowsInput::IsKeyPressed(DK_KEY_A) ){
                pos[0] += 0.1; 
            }else if ( WindowsInput::IsKeyPressed(DK_KEY_S) ){
                pos[1] += 0.1;
            }else if (WindowsInput::IsKeyPressed(DK_KEY_D)){
                pos[0] -= 0.1;
            }else if( WindowsInput::IsKeyPressed(DK_KEY_R) ){
                rotate += 1;
            }else if (WindowsInput::IsKeyPressed(DK_KEY_L)){
                rotate -= 1;
            }

            m_camera.SetPostion(pos);
            m_camera.SetRotation(rotate);

            Renderer::BeginScene(m_camera);

                Renderer::Submit(m_shader,m_vertexArray);

            Renderer::EndScene();

            for( auto& layer : m_layerStack ){
                Deref(layer).OnUpdate(Timestep{});
            }

            Deref(m_imGuiLayer).Begin();
            for( auto& layer : m_layerStack ){
                Deref(layer).ImGuiRenderer();
            }
            Deref(m_imGuiLayer).End();
            Deref(m_window).OnUpdate();
        }
        CoreLog::Error("Window Closed");
    }

    bool Dark::onWindowClose(WindowCloseEvent&){
        m_running = false;
        return true;
    }

    void Dark::PushLayer( Ref<Layer> layer ){
        m_layerStack.PushLayer(layer);
        Deref(layer).OnAttach();
        CoreLog::Info("{0} Layer has been attached",Deref(layer).GetName());
    }

    void Dark::PushOverlay( Ref<Layer> overlay ){
        m_layerStack.PushLayer(overlay);
        Deref(overlay).OnAttach();
    }
}