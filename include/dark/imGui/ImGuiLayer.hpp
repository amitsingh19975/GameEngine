#if !defined(DK_IMGUI_LAYER_HPP)
#define DK_IMGUI_LAYER_HPP

#include "dark/Layer.hpp"

namespace dk{
    struct ImGuiLayer : Layer {
        ImGuiLayer();
        ~ImGuiLayer() = default;

        void OnUpdate(Timestep ts) override;
        void OnEvent(EventBase& e) override;
        void OnAttach() override;
        void OnDetach() override;
    private:
    };
}


#endif // DK_IMGUI_LAYER_HPP
