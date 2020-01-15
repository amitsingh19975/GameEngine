#include <Dark.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp> 

glm::mat4 camera(float Translate, glm::vec2 const & Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

struct ExLayer : dk::Layer{
    ExLayer() : Layer("ExLayer"){}

    void OnUpdate( dk::Timestep) override{
        // dk::ClientLog::Info("Layer Name: {0}, Frame: {1}", GetName(), ts);
    }

    void OnEvent( dk::EventBase& e ) override{
        dk::ClientLog::Info(e);
    }
};


struct Sandbox : public dk::Dark{
    Sandbox() {
        
        PushLayer(dk::CreateRef<ExLayer>());
    }

    ~Sandbox(){

    }
};

dk::Scope<dk::Dark> dk::CreateApplication(){
    return dk::CreateScope<Sandbox>();
}