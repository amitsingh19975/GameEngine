#include <Dark.hpp>

struct ExLayer : dk::Layer{
    ExLayer() : Layer("ExLayer"){}

    void OnUpdate( dk::Timestep ts ) override{
        dk::ClientLog::Info("Layer Name: {0}, Frame: {1}", GetName(), ts);
    }

    void OnEvent( dk::EventBase& e ) override{
        dk::ClientLog::Info(e);
    }
};

struct Sandbox : public dk::Dark{
    Sandbox() {
        PushLayer(dk::CreateRef<ExLayer>());
        PushOverlay(dk::CreateRef<dk::ImGuiLayer>());
    }

    ~Sandbox(){

    }
};

dk::Scope<dk::Dark> dk::CreateApplication(){
    return dk::CreateScope<Sandbox>();
}