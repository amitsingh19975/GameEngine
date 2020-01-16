#include "dark/DarkApp.hpp"
#include "dark/platform/WindowsInput.hpp"

namespace dk{

    Dark* Dark::s_instance = nullptr;

    Dark::Dark(): m_window(Window::Create()), m_imGuiLayer(new ImGuiLayer()){
        CoreAssert(s_instance == nullptr,"Application is already initialized");
        s_instance = this;
        m_window->SetEventCallback(std::bind(&Dark::onEvent,this,std::placeholders::_1));
        PushOverlay(m_imGuiLayer);
        
        std::string vertexSrc = R"(
            attribute vec3 a_Pos;
            void main(){
                gl_Position = vec4(a_Pos,1.0);
            }
        )";

        std::string fragmentSrc = R"(
            void main(){
                gl_FragColor = vec4(1,0.2,0.3,1.0);
            }
        )";

        DKGenVertexArrays(1,&m_vertexArray);
        DKBindVertexArray(m_vertexArray);
        
        glGenBuffers(1,&m_vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER,m_vertexBuffer);

        float vertices[] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1,&m_indexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_indexBuffer);

        uint32_t indices[] = {
            0,1,2
        };

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        m_shader = CreateScope<Shader>(vertexSrc, fragmentSrc);
        m_shader->BindAttribute(0,"a_Pos");
    }
    
    Dark::~Dark(){}

    void Dark::onEvent( EventBase& e ){
        EventDispatcher disp(e);
        CoreLog::Info(e);
        
        disp.Dispatch<WindowCloseEvent>(
            std::bind(&Dark::onWindowClose,this,std::placeholders::_1)
        );
        
        std::for_each(m_layerStack.rbegin(), m_layerStack.rend(),[&e]( auto& layer) {
            layer->OnEvent(e);
            if( e.Handled ) return;
        });
    }

    void Dark::Run(){
        CoreLog::Info("Starting Window");
        while(m_running){
            float time = SDL_GetTicks()/ 1000.f;
            Timestep ts = time - m_lastFrame;
            m_lastFrame = time;
            m_shader->Bind();
            glClearColor(0.1f,.1f,.1f, 1.f);
            glClear( GL_COLOR_BUFFER_BIT );
            // glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            // glEnableClientState(GL_NORMAL_ARRAY);
            // glVertexPointer(3,GL_FLOAT, sizeof(GLfloat) * 3, nullptr );
            DKBindVertexArray(m_vertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for( auto& layer : m_layerStack ){
                layer->OnUpdate(ts);
            }

            m_imGuiLayer->Begin();
            for( auto& layer : m_layerStack ){
                layer->ImGuiRenderer();
            }
            m_imGuiLayer->End();
            m_window->OnUpdate();

            // glDisableClientState(GL_NORMAL_ARRAY);
            // glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        }
        CoreLog::Error("Window Closed");
    }

    bool Dark::onWindowClose(WindowCloseEvent&){
        m_running = false;
        return true;
    }

    void Dark::PushLayer( Ref<Layer> layer ){
        m_layerStack.PushLayer(layer);
        layer->OnAttach();
        CoreLog::Info("{0} Layer has been attached",layer->GetName());
    }

    void Dark::PushOverlay( Ref<Layer> overlay ){
        m_layerStack.PushLayer(overlay);
        overlay->OnAttach();
    }
}