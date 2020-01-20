#if !defined(DK_ORTHOGRAHPIC_CAMERA_CONTROLLER)
#define DK_ORTHOGRAHPIC_CAMERA_CONTROLLER

#include "dark/core/Core.hpp"
#include "dark/renderer/OrthographicCamera.hpp"
#include "dark/core/Timestep.hpp"
#include "dark/events/AppEvent.hpp"
#include "dark/events/MouseEvent.hpp"
#include "glm/glm.hpp"

namespace dk{
    struct OrthographicCameraController{

        OrthographicCameraController( float aspectRatio, float rotation = false) ;

        void OnUpdate( Timestep ts );
        void OnEvent( EventBase& e );

        constexpr OrthographicCamera& GetCamera() noexcept{
            return m_camera;
        }

        constexpr OrthographicCamera const& GetCamera() const noexcept{
            return m_camera;
        }

        constexpr void SetZoomLevel( float z ) noexcept{
            m_zoomLevel = z;
        }
        
    private:
        bool OnMouseScrolled( MouseScrolledEvent& e);
        bool OnWindowResized( WindowResizeEvent& e );
    private:
        float               m_aspectRatio;
        float               m_zoomLevel{1.f};
        OrthographicCamera  m_camera;

        bool                m_rotation;

        glm::vec3           m_cameraPosition{0,0,0};
        float               m_cameraSpeed{5.f};
        float               m_cameraRotationSpeed{180.f};
        float               m_cameraRotation{0.f};
    };
        
}

#endif // DK_ORTHOGRAHPIC_CAMERA_CONTROLLER
