#include "dark/windows.hpp"
#include <type_traits>

namespace dk {
    static bool s_SDLWindowInitialized = false;

    Window::Window( WindowsProps const& props ){
        Init(props);
    }

    Window::~Window() {}

    void Window::Init( WindowsProps const& props ){
        m_data.Height = props.Height;
        m_data.Width = props.Width;
        m_data.Title = props.Title;
        m_data.windowId = SDL_GetWindowID(this->m_win.get());

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

        CoreLog::Info("Creating Window {0} ({1}, {2})",props.Title,props.Width,props.Height);

        if( !s_SDLWindowInitialized ){
            Window::Assert(SDL_Init(SDL_INIT_EVERYTHING) >= 0, "Init Failure","SDL failed to initialize: ");
            s_SDLWindowInitialized = true;
        }
        CoreLog::Info("SDL Initialized");
        auto win = SDL_CreateWindow(
                m_data.Title.c_str() ,SDL_WINDOWPOS_CENTERED
                ,SDL_WINDOWPOS_CENTERED ,m_data.Width , m_data.Height
                ,SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
            );
        
        Window::Assert( win != nullptr, "Init Failed","Window could not be created: ");
        m_win = Ref<SDL_Window>(win,SDL_DestroyWindow);
        CoreLog::Info("SDL Window Created Successfully");

        m_cxt = SDL_GL_CreateContext(m_win.get());
        Window::Assert(m_cxt != nullptr, "Init Failed","OpenGL context could not be created: ");

        Window::Assert( gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress), "Init Failed", "Failed to initialize the OpenGL context: " );

        SDL_AddEventWatch([](void* userdata, SDL_Event* evt)->int{
            auto& props = *static_cast<Window::WindowData*>(userdata);
            switch(evt->type){
                case SDL_WINDOWEVENT:{
                    if( evt->window.windowID == props.windowId ){
                        auto& temp_w = evt->window;
                        switch(temp_w.event){
                            case SDL_WINDOWEVENT_SIZE_CHANGED:{
                                props.Height = temp_w.data2;
                                props.Width = temp_w.data1;
                                auto e = WindowResizeEvent(props.Width,props.Height);
                                props.EventCallback(e);
                                break;
                            }
                            case SDL_WINDOWEVENT_CLOSE:{
                                auto e = WindowCloseEvent();
                                props.EventCallback(e);
                                break;
                            }
                        }
                    }
                    break;
                }
                case SDL_KEYDOWN:{
                    auto e = KeyPressedEvent(evt->key.keysym.sym,evt->key.repeat);
                    props.EventCallback(e);
                    break;
                }
                case SDL_KEYUP:{
                    auto e = KeyReleasedEvent(evt->key.keysym.sym);
                    props.EventCallback(e);
                    break;
                }
                case SDL_MOUSEMOTION:{
                    auto e = MouseMovedEvent(evt->motion.x,evt->motion.y);
                    props.EventCallback(e);
                    break;
                }
                case SDL_MOUSEWHEEL:{
                    auto e = MouseScrolledEvent(evt->wheel.x,evt->wheel.y);
                    props.EventCallback(e);
                    break;
                }
                case SDL_MOUSEBUTTONDOWN:{
                    auto e = MouseButtonPressedEvent(evt->button.type);
                    props.EventCallback(e);
                    break;
                }
                case SDL_MOUSEBUTTONUP:{
                    auto e = MouseButtonReleasedEvent(evt->button.type);
                    props.EventCallback(e);
                    break;
                }
                case SDL_QUIT:{
                    auto e = WindowCloseEvent();
                    props.EventCallback(e);
                    break;
                }
            }

            return 0;
        },&m_data);
        SetVSync(true);
    }

    void Window::Shutdown(){
        m_win.~shared_ptr();
    }

    void Window::OnUpdate(){
        SDL_PollEvent(&m_event);
        SDL_GL_SwapWindow(m_win.get());
    }

    void Window::SetVSync( bool enabled ){
        if( enabled ){
            SDL_GL_SetSwapInterval(1);
        }else{
            SDL_GL_SetSwapInterval(0);
        }
        m_data.VSync = enabled;
    }

    bool Window::IsVSync() const {
        return m_data.VSync;
    }
}