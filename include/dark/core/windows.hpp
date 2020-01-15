#if !defined(DK_WINDOWS_HPP)
#define DK_WINDOWS_HPP

#include "dark/core/Core.hpp"
#include "dark/core/Log.hpp"
#include "dark/events/AppEvent.hpp"
#include "dark/events/KeyboardEvent.hpp"
#include "dark/events/MouseEvent.hpp"

namespace dk {
    struct WindowsProps{
        std::string Title{"Dark Engine"};
        uint32_t Width{1280};
        uint32_t Height{720};
    };

    struct Window;
}

namespace dk::detail{
    template<typename T>
    struct WindowBase{
        using window_type = T;
        using EventCallbackFn = std::function<void(EventBase&)>;

        virtual ~WindowBase() = default;
        virtual void OnUpdate() =  0;
        virtual uint32_t GetWidth() const noexcept = 0;
        virtual uint32_t GetHeight() const noexcept = 0;

        virtual void SetEventCallback( EventCallbackFn const& callback ) = 0;
        virtual void SetVSync( bool enable ) = 0;
        virtual bool IsVSync() const = 0;

        virtual T* GetNativeWindow() = 0;

        inline static Scope<WindowBase> Create( WindowsProps const& props = WindowsProps() ){
            return CreateScope<Window>(props);
        }
    };
}

namespace dk{
    struct Window : detail::WindowBase<SDL_Window>{
        using detail::WindowBase<SDL_Window>::Create;
        using window_type = SDL_Window;

        Window( WindowsProps const& props );
        virtual ~Window();

        void OnUpdate() override;

        inline uint32_t GetWidth() const noexcept override{ return m_data.Width;}
        inline uint32_t GetHeight() const noexcept override{ return m_data.Height;}

        inline void SetEventCallback( EventCallbackFn const& callback ) override { m_data.EventCallback = callback; }

        void SetVSync(bool enabled) override;
        bool IsVSync() const override;

        inline SDL_Window* GetNativeWindow() override{ return m_win.get(); }
        constexpr SDL_GLContext GetContext(){ return m_cxt; }
        constexpr SDL_Event& GetEvent(){ return m_event; }

        auto Assert(bool cond, std::string title, std::string_view msg){
            if constexpr( Config::is_debug ){
                std::string err_msg(msg);
                if( !cond ){
                    SDL_GetError();
                    err_msg.append(SDL_GetError());
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,title.c_str(), err_msg.c_str(),nullptr);
                    CoreLog::Fatal(err_msg);
                    return false;
                }else{
                    return true;
                }
            }
        }

        constexpr auto& GetEvent() const noexcept{ return m_event; } 

        struct WindowData{
            std::string Title;
            uint32_t Width;
            uint32_t Height;
            uint32_t windowId;
            bool VSync;

            EventCallbackFn EventCallback;
        };

    private:
        virtual void Init( WindowsProps const& props );
        virtual void Shutdown();
        int EventFilter(void* userData, SDL_Event* evt);        

    private:
        Ref<SDL_Window> m_win;


        WindowData m_data;
        SDL_GLContext m_cxt;
        SDL_Event m_event;
    };
}

#endif // DK_WINDOWS_HPP
