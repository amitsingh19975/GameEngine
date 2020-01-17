#include "dark/DarkApp.hpp"
#include "dark/platform/WindowsInput.hpp"

namespace dk{

    Dark* Dark::s_instance = nullptr;

    Dark::Dark(): m_window(Window::Create()), m_imGuiLayer(new ImGuiLayer()){
        CoreAssert(s_instance == nullptr,"Application is already initialized");
        s_instance = this;
        Deref(m_window).SetEventCallback(std::bind(&Dark::onEvent,this,std::placeholders::_1));
        PushOverlay(m_imGuiLayer);
        
        std::string vertexSrc = R"(
            attribute vec3 a_Pos;
            attribute vec4 a_Col;
            varying vec4 v_Col;
            void main(){
                v_Col = a_Col;
                gl_Position = vec4(a_Pos ,1.0);
            }
        )";

        std::string fragmentSrc = R"(
            varying vec4 v_Col;
            void main(){
                gl_FragColor = v_Col;
            }
        )";

        typename VertexBuffer::value_type vertices[] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.f,
             0.5f, -0.5f, 0.0f, 0.5f, 0.8f, 0.2f, 1.f,
             0.0f,  0.5f, 0.0f, 0.2f, 0.3f, 0.6f, 1.f
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
            0,1,2
        };
        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / IndexBuffer::value_size);
        
        m_vertexArray = VertexArray::Create();
        Deref(m_vertexArray).AddVertexBuffer(vertexBuffer);
        Deref(m_vertexArray).SetIndexBuffer(indexBuffer);
        Deref(m_vertexArray).BindAttribute(m_shader);


    }
    
    Dark::~Dark(){}

    void Dark::onEvent( EventBase& e ){
        EventDispatcher disp(e);
        CoreLog::Info(e);
        
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
        while(m_running){
            float time = SDL_GetTicks()/ 1000.f;
            Timestep ts = time - m_lastFrame;
            m_lastFrame = time;
            Deref(m_shader).Bind();
            glClearColor(0.1f,.1f,.1f, 1.f);
            glClear( GL_COLOR_BUFFER_BIT );
            Deref(m_vertexArray).Bind();
            glDrawElements(GL_TRIANGLES, Deref( Deref(m_vertexArray).GetIndexBuffer() ).GetCount(), GL_UNSIGNED_INT, nullptr);

            for( auto& layer : m_layerStack ){
                Deref(layer).OnUpdate(ts);
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