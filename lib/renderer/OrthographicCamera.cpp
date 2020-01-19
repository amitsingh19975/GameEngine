#include "dark/renderer/OrthographicCamera.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace dk{
    
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_projectionMatrix( glm::ortho(left,right,bottom,top,-1.f,1.f) )
        , m_viewMatrix(1.f)
    {
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicCamera::SetProjection(float left, float right, float bottom, float top){
        m_projectionMatrix = glm::ortho(left,right,bottom,top, -1.f, 1.f);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix() {
        glm::mat4 transformation = glm::translate(glm::mat4(1.0f), m_position) *
            glm::rotate(glm::mat4(1.f), glm::radians(m_rotation),glm::vec3(0,0,1));
        
        m_viewMatrix = glm::inverse(transformation);
        m_viewProjectionMatrix = m_projectionMatrix * m_viewMatrix;
    }
}