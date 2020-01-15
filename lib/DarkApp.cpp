#include "dark/DarkApp.hpp"
#include "dark/platform/WindowsInput.hpp"

namespace dk{

    Dark* Dark::s_instance = nullptr;

    Dark::Dark(): m_window(Window::Create()), m_imGuiLayer(new ImGuiLayer()){
        CoreAssert(s_instance == nullptr,"Application is already initialized");
        s_instance = this;
        m_window->SetEventCallback(std::bind(&Dark::onEvent,this,std::placeholders::_1));
        PushOverlay(m_imGuiLayer);
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
            
            glClearColor(1.0f,1.0f,1.0f, 1.f);
            glClear( GL_COLOR_BUFFER_BIT );

            for( auto& layer : m_layerStack ){
                layer->OnUpdate(ts);
            }

            m_imGuiLayer->Begin();
            for( auto& layer : m_layerStack ){
                layer->ImGuiRenderer();
            }
            m_imGuiLayer->End();
            m_window->OnUpdate();
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