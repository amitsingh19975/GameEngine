#if !defined(DK_IMGUI_LAYER_HPP)
#define DK_IMGUI_LAYER_HPP

#include "dark/core/Layer.hpp"
#include "dark/events/AppEvent.hpp"
#include "dark/events/KeyboardEvent.hpp"
#include "dark/events/MouseEvent.hpp"

namespace dk{
    struct ImGuiLayer : Layer {
        ImGuiLayer();
        ~ImGuiLayer() = default;

        void OnAttach() override;
        void OnDetach() override;
        void ImGuiRender() override;

        void Begin();
        void End();
    };
}


#endif // DK_IMGUI_LAYER_HPP
