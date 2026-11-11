#pragma once 

#include "VertexArray.h"
#include "IndexBuffer.h"
#include ".././Shader.h"
#include "../../transform/Transform.h"
#include <glm/gtc/matrix_transform.hpp>
#include "../../core/GameObject.h"

#include "glad/glad.h"

class Renderer 
{
    public:
        void Clear();
        void Draw(const GameObject& gameObject,Shader &shader);


    
};