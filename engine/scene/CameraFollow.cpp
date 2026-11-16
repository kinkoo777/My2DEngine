#include "scene/CameraFollow.h"


void CameraFollow::Update(
        const GameObject& target,
        OrthographicCamera& camera,
        float width,
        float height)
{
    Vector2 targetPos = target.GetTransform().GetPosition();

    Vector2 CameraPos = Vector2(targetPos.GetX() - width / 2, targetPos.GetY() - height / 2);

    camera.SetPosition(CameraPos.GetX(), CameraPos.GetY());

    

}