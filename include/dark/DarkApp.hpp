#if !defined(DK_DARKAPP_HPP)
#define DK_DARKAPP_HPP

#include "dark/core/windows.hpp"
#include "dark/core/Log.hpp"
#include "dark/core/LayerStack.hpp"
#include "dark/imGui/ImGuiLayer.hpp"
#include "dark/renderer/Shader.hpp"

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
        inline static Dark& Get() noexcept { 
            CoreAssert(s_instance != nullptr, "App is not initilized"); 
            return *s_instance; 
        }
        constexpr base_window& GetWindow() const noexcept { return *m_window; }

    private:
        bool onWindowClose(WindowCloseEvent& e);
    private:
        Scope<base_window>  m_window;
        Ref<ImGuiLayer>     m_imGuiLayer;
        LayerStack          m_layerStack;
        bool                m_running{true};
        float               m_lastFrame{.0f};
        uint32_t            m_vertexArray;
        uint32_t            m_vertexBuffer;
        uint32_t            m_indexBuffer;
        Scope<Shader>       m_shader;
    private:
        static Dark* s_instance;
    };

    Scope<Dark> CreateApplication();
}

#endif // DK_DARK_HPP
