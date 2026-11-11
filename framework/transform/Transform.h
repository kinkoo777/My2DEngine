#pragma once

#include <glm/gtc/matrix_transform.hpp>

class Transform 
{
    public:
        Transform();

        void SetPosition(float x, float y, float z);
        void SetRotation(float radians);
        void SetScale(float x, float y, float z);

        glm::mat4 GetMatrix() const;

    private:
        glm::vec3 m_Position;
        float m_Rotation;
        glm::vec3 m_Scale;
        
};