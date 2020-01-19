#include "dark/renderer/OrthographicCameraController.hpp"
#include "dark/platform/WindowsInput.hpp"

namespace dk{
    
    OrthographicCameraController::OrthographicCameraController( float aspectRatio, float rotation )
        : m_aspectRatio(aspectRatio)
        , m_camera(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel)
        , m_rotation(rotation)
    {

    }

    void OrthographicCameraController::OnUpdate( Timestep ts ){
        if( WindowsInput::IsKeyPressed(dk::DK_KEY_W) ){
            m_cameraPosition[1] -= m_cameraSpeed * ts; 
        }else if ( WindowsInput::IsKeyPressed(dk::DK_KEY_A) ){
            m_cameraPosition[0] += m_cameraSpeed * ts; 
        }else if ( WindowsInput::IsKeyPressed(dk::DK_KEY_S) ){
            m_cameraPosition[1] += m_cameraSpeed * ts;
        }else if ( WindowsInput::IsKeyPressed(dk::DK_KEY_D)){
            m_cameraPosition[0] -= m_cameraSpeed * ts;
        }
        
        if( m_rotation ){
            if( dk::WindowsInput::IsKeyPressed(dk::DK_KEY_Q) ){
                m_cameraRotation += m_cameraRotationSpeed * ts;
            }else if (dk::WindowsInput::IsKeyPressed(dk::DK_KEY_R)){
                m_cameraRotation -= m_cameraRotationSpeed * ts;
            }
            m_camera.SetRotation(m_cameraRotation);
        }

        m_camera.SetPostion(m_cameraPosition);
        m_cameraSpeed = m_zoomLevel;
    }

    void OrthographicCameraController::OnEvent( EventBase& e ){
        EventDispatcher dis(e);
        dis.Dispatch<MouseScrolledEvent>(std::bind(&OrthographicCameraController::OnMouseScrolled, this, std::placeholders::_1));
        dis.Dispatch<WindowResizeEvent>(std::bind(&OrthographicCameraController::OnWindowResized, this, std::placeholders::_1));
    }

    bool OrthographicCameraController::OnMouseScrolled( MouseScrolledEvent& e){
        m_zoomLevel -= e.GetYOffset() * 0.25f;
        m_zoomLevel = std::max(m_zoomLevel,0.25f);
        m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized( WindowResizeEvent& e ){
        m_aspectRatio = (float)e.GetWidth()/(float)e.GetHeight();
        m_camera.SetProjection(-m_aspectRatio * m_zoomLevel, m_aspectRatio * m_zoomLevel, -m_zoomLevel, m_zoomLevel);
        return false;
    }

}