#if !defined(DK_SANDBOX_2D)
#define DK_SANDBOX_2D


#include "Dark.hpp"
#include "dark/core/EntryPoint.hpp"

#include "glm/gtc/matrix_transform.hpp"
#include "dark/platform/openGL/OpenGLShader.hpp"
#include "dark/platform/openGL/OpenGLBuffer.hpp"

struct SandBox2D : dk::Layer{
    SandBox2D( uint32_t width, uint32_t height) 
        : SandBox2D((float)width/(float)height)
    {}

    SandBox2D( float aspectRatio = 1.6f )
        : Layer("SandBox2D")
        , m_camera(aspectRatio,true)
    {}

public:

    void OnAttach() override {
        m_texture = dk::Texture2D::Create("../assets/textures/space_ship.png");
    }

    void OnDetach() override {

    }

    void OnUpdate( dk::Timestep ts) override {
        
        dk::RenderCommand::SetClearColor(0.1f,.1f,.1f, 1.f);
        dk::RenderCommand::Clear();
        
        m_camera.OnUpdate(ts);
        
        dk::Renderer2D::BeginScene(m_camera.GetCamera());
            // dk::Renderer2D::DrawQuad({-0.5f, -.5f}, {1.f,1.f}, {1,0.8,0.2,1.f});
            dk::Renderer2D::DrawQuad({-1.f, -1.f}, {2.f,2.f}, m_texture);
        dk::Renderer2D::EndScene();
    }

    void OnEvent( dk::EventBase& e) override {
        m_camera.OnEvent(e);
    }

    void ImGuiRender() override {

    }


private:
    dk::OrthographicCameraController        m_camera;
    dk::Ref<dk::VertexArray>                m_vertexArray;
    dk::Ref<dk::Texture2D>                  m_texture;

    glm::vec3                               m_sqColor{0.5,0.8,0.2};
};

#endif // DK_SANDBOX_2D
