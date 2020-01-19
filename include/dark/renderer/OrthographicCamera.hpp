#if !defined(DK_ORTHOGRAPIC_CAMERA_HPP)
#define DK_ORTHOGRAPIC_CAMERA_HPP

#include "glm/glm.hpp"

namespace dk {
    struct OrthographicCamera{

        OrthographicCamera(float left, float right, float bottom, float top);
        
        void SetProjection(float left, float right, float bottom, float top);

        constexpr auto& GetProjectionMatrix() const noexcept { return m_projectionMatrix; } 
        constexpr auto& GetViewMatrix() const noexcept { return m_viewMatrix; } 
        constexpr auto& GetViewProjectionMatrix() const noexcept { return m_viewProjectionMatrix;} 
        
        constexpr auto& GetPosition() noexcept { return m_position; } 
        constexpr auto& GetRotation() noexcept { return m_rotation; } 

        void SetPostion( glm::vec3 const& pos ) noexcept { m_position = pos; RecalculateViewMatrix();}
        template<typename... Args>
        void SetPostion( Args&&... args ) noexcept { SetPostion({ glm::vec3(std::forward<Args>(args)...) });}
        void SetRotation( float rot ) noexcept { m_rotation = rot; RecalculateViewMatrix();}

    private:
        void RecalculateViewMatrix();
    private:
        glm::mat4 m_projectionMatrix;
        glm::mat4 m_viewMatrix;
        glm::mat4 m_viewProjectionMatrix;

        glm::vec3 m_position;
        float m_rotation{0};
    };
}



#endif // DK_ORTHOGRAPIC_CAMERA_HPP
