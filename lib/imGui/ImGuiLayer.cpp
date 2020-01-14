#include "imgui.h"
#include "dark/imGui/ImGuiLayer.hpp"
#include "dark/DarkApp.hpp"
#include "dark/openGL/imgui_impl_opengl2.h"
#include "dark/openGL/imgui_impl_sdl.h"

namespace dk{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){}

    void ImGuiLayer::OnAttach() {

        IMGUI_CHECKVERSION();
        CoreAssert(ImGui::CreateContext() != nullptr, "ImGui is unable to crate context");
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        auto& temp_win = Dark::Get().GetWindow();
        using type = std::decay_t<decltype(temp_win)>;
        
        if constexpr( std::is_same_v< typename type::window_type, SDL_Window > ){
            Window& win = static_cast<Window&>(temp_win);
            ImGui_ImplSDL2_InitForOpenGL(win.GetNativeWindow(),win.GetContext());
        }
        CoreAssert( ImGui_ImplOpenGL2_Init(), "ImGui is unable to set glsl version" );
    }

    void ImGuiLayer::OnDetach() {

    }

    void ImGuiLayer::OnUpdate( Timestep ts) {
        dk::ClientLog::Info("Layer Name: {0}, Frame: {1}", GetName(), ts);
        auto& win = Dark::Get().GetWindow();
        ImGuiIO& io = ImGui::GetIO();
        
        io.DeltaTime = ts;
        io.DisplaySize = ImVec2(win.GetWidth() , win.GetHeight());
        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(win.GetNativeWindow());
        ImGui::NewFrame();


        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(EventBase& e) {
        EventDispatcher dis(e);
        dis.Dispatch<MouseButtonPressedEvent>([&](auto& e){ return this->OnMouseButtonPressedEvent(e);});
        dis.Dispatch<MouseButtonReleasedEvent>([&](auto& e){ return this->OnMouseButtonReleasedEvent(e);});
        dis.Dispatch<MouseScrolledEvent>([&](auto& e){ return this->OnMouseScrolledEvent(e);});
        dis.Dispatch<MouseMovedEvent>([&](auto& e){ return this->OnMouseMovedEvent(e);});
        dis.Dispatch<KeyReleasedEvent>([&](auto& e){ return this->OnKeyReleasedEvent(e);});
        dis.Dispatch<KeyPressedEvent>([&](auto& e){ return this->OnKeyPressedEvent(e);});
        dis.Dispatch<KeyTypedEvent>([&](auto& e){ return this->OnKeyTypedEvent(e);});
        dis.Dispatch<WindowCloseEvent>([&](auto& e){ return this->OnWindowCloseEvent(e);});
        dis.Dispatch<WindowResizeEvent>([&](auto& e){ return this->OnWindowResizeEvent(e);});
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.GetMouseButton()] = true;
        CoreLog::Warn("Mouse Btn {0} is pressed : {1}",e.GetMouseButton(),io.MouseDown[e.GetMouseButton()]);
        return false;     
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.MouseReleased[e.GetMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffset();
        io.MouseWheel += e.GetYOffset();
        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(),e.GetY());
        return false;
    }

    bool ImGuiLayer::OnWindowCloseEvent(WindowCloseEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplSDL2_Shutdown();
        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = false;
        return false;
    }
    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharactersUTF8(e.GetData());

        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.GetKeyCode()] = true;
        io.KeyCtrl  = io.KeysDown[SDL_SCANCODE_RCTRL]   || io.KeysDown[SDL_SCANCODE_LCTRL];
        io.KeyAlt   = io.KeysDown[SDL_SCANCODE_RALT]    || io.KeysDown[SDL_SCANCODE_LALT];
        io.KeyShift  = io.KeysDown[SDL_SCANCODE_RSHIFT] || io.KeysDown[SDL_SCANCODE_LSHIFT];
        io.KeySuper  = io.KeysDown[SDL_SCANCODE_RGUI]   || io.KeysDown[SDL_SCANCODE_LGUI];
        return false;
    }

    bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e){
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
        glViewport(0,0,e.GetWidth(),e.GetHeight());
        return false;
    }

}