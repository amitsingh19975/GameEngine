#if !defined(DK_DARKAPP_HPP)
#define DK_DARKAPP_HPP

#include "dark/core/windows.hpp"
#include "dark/core/Log.hpp"
#include "dark/core/LayerStack.hpp"
#include "dark/imGui/ImGuiLayer.hpp"
#include "dark/renderer/Shader.hpp"
#include "dark/renderer/Buffer.hpp"
#include "dark/renderer/VertexArray.hpp"
#include "dark/renderer/OrthographicCamera.hpp"

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
        constexpr uint32_t GetWidth() const noexcept { return Deref( m_window ).GetWidth(); }
        constexpr uint32_t GetHeight() const noexcept { return Deref( m_window ).GetHeight(); }

    private:
        bool onWindowClose(WindowCloseEvent& e);
    private:
        Scope<base_window>  m_window;
        Ref<ImGuiLayer>     m_imGuiLayer;
        LayerStack          m_layerStack;
        bool                m_running{true};
        bool                m_minimized{false};
        float               m_lastFrame{.0f};
    private:
        static Dark* s_instance;
    };

    Scope<Dark> CreateApplication();
}

#endif // DK_DARK_HPP
