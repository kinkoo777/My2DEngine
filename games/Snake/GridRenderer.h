#pragma once

#include "GridMap.h"

#include "renderer/Renderer.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"

#include <memory>
#include <unordered_map>

class GridRenderer
{
public:
    GridRenderer(float tileSize);

    void SetTexture(TileType type, std::shared_ptr<Texture> texture);

    void Render(
        const GridMap& grid,
        Renderer& renderer,
        Shader& shader,
        const OrthographicCamera& camera
    );

    float GetRotation() const;
    void SetRotation(float rotation);
    int GetPositionX() const;
    int GetPositionY() const;
    void SetPositionX(int x);
    void SetPositionY(int y);



private:
    float m_TileSize;
    float snakeRotation = 0.0f;
    int snakePosX = 5;
    int snakePosY = 5;

    std::unordered_map<TileType, std::shared_ptr<Texture>> m_Textures;
};