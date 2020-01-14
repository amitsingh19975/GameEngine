#if !defined(DK_DARKAPP_HPP)
#define DK_DARKAPP_HPP

#include "windows.hpp"
#include "Log.hpp"
#include "LayerStack.hpp"

namespace dk{
    class Dark{
        using base_window = detail::WindowBase<SDL_Window>;
        
    public:
        Dark();
        virtual ~Dark();
        void Run();
        void onEvent( EventBase& e );

        void PushLayer( Ref<Layer> layer );
        void PushOverlay( Ref<Layer> overlay );

    private:
        bool onWindowClose(WindowCloseEvent& e);
    private:
        Scope<base_window> m_window;
        bool m_running{true};
        LayerStack m_layerStack;
        float m_lastFrame{.0f};
    };

    Scope<Dark> CreateApplication();
}

#endif // DK_DARK_HPP
