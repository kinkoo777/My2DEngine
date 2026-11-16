#pragma once

#include "scene/GameObject.h"
#include "renderer/OrthographicCamera.h"
#include "math/Vector2.h"

class CameraFollow
{
public:
    void Update(
        const GameObject& target,
        OrthographicCamera& camera,
        float width,
        float height
    );
};