#include "imgui.h"
#include "dark/imGui/ImGuiLayer.hpp"
#include "dark/DarkApp.hpp"
#include "examples/imgui_impl_opengl2.h"
#include "examples/imgui_impl_sdl.h"

namespace dk{
    ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer"){}

    void ImGuiLayer::OnAttach() {

        IMGUI_CHECKVERSION();
        CoreAssert(ImGui::CreateContext() != nullptr, "ImGui is unable to crate context");
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        ImGui::StyleColorsDark();

        ImGuiStyle& style = ImGui::GetStyle();
        if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable ){
            style.WindowRounding = .0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.f;
        }

        auto& app = Dark::Get().GetWindow();
        using type = std::decay_t<decltype(app)>;
        
        if constexpr( std::is_same_v< typename type::window_type, SDL_Window > ){
            Window& win = static_cast<Window&>(app);
            ImGui_ImplSDL2_InitForOpenGL(win.GetNativeWindow(),win.GetContext());
        }
        CoreAssert( ImGui_ImplOpenGL2_Init(), "ImGui is unable to set glsl version" );
    }

    void ImGuiLayer::OnDetach() {
        ImGui_ImplOpenGL2_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
    }

    void ImGuiLayer::ImGuiRenderer() {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void ImGuiLayer::Begin(){
        auto& win = Dark::Get().GetWindow();

        ImGui_ImplOpenGL2_NewFrame();
        ImGui_ImplSDL2_NewFrame(win.GetNativeWindow());
        ImGui::NewFrame();
    }

    void ImGuiLayer::End() {
        auto& app = Dark::Get().GetWindow();
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(app.GetWidth() , app.GetHeight());

        ImGui::Render();
        ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

        if( io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable ){
            using type = std::decay_t<decltype(app)>;
            if constexpr( std::is_same_v< typename type::window_type, SDL_Window > ){
                auto& win = static_cast<Window&>( app );
                auto ctx = win.GetContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                SDL_GL_MakeCurrent(app.GetNativeWindow(),ctx);
            }
        }
    }

}