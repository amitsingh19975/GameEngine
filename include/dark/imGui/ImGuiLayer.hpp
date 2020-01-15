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

        void OnUpdate(Timestep ts) override;
        void OnAttach() override;
        void OnDetach() override;
    private:
        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent&);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent&);
        bool OnMouseScrolledEvent(MouseScrolledEvent&);
        bool OnMouseMovedEvent(MouseMovedEvent&);
        bool OnKeyReleasedEvent(KeyReleasedEvent&);
        bool OnKeyPressedEvent(KeyPressedEvent&);
        bool OnKeyTypedEvent(KeyTypedEvent&);
        bool OnWindowCloseEvent(WindowCloseEvent&);
        bool OnWindowResizeEvent(WindowResizeEvent&);
        void OnEvent(EventBase& e) override;
    };
}


#endif // DK_IMGUI_LAYER_HPP
