#include "dark/DarkApp.hpp"
#include "dark/platform/WindowsInput.hpp"
#include "dark/renderer/Renderer.hpp"
#include "dark/renderer/RenderCommand.hpp"
namespace dk{

    Dark* Dark::s_instance = nullptr;

    Dark::Dark()
        : m_window(Window::Create())
        , m_imGuiLayer(new ImGuiLayer())
    {
        CoreAssert(s_instance == nullptr,"Application is already initialized");
        s_instance = this;
        Deref(m_window).SetEventCallback(std::bind(&Dark::onEvent,this,std::placeholders::_1));
        Renderer::Init();
        
        PushOverlay(m_imGuiLayer);
        
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

        while(m_running){
            float time = SDL_GetTicks()/ 1000.f;
            Timestep ts = time - m_lastFrame;
            m_lastFrame = time;

            for( auto& layer : m_layerStack ){
                Deref(layer).OnUpdate(ts);
            }

            Deref(m_imGuiLayer).Begin();
            for( auto& layer : m_layerStack ){
                Deref(layer).ImGuiRender();
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