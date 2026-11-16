
#include "GridRenderer.h"
#include "Application.h"
#include <iostream>

GridRenderer::GridRenderer(float tileSize)
    : m_TileSize(tileSize)
{
}

void GridRenderer::SetTexture(
    TileType type,
    std::shared_ptr<Texture> texture)
{
    m_Textures[type] = std::move(texture);
}

float GridRenderer::GetRotation() const
{
    return snakeRotation;
}

void GridRenderer::SetRotation(float rotation)
{
    snakeRotation = rotation;
}

void GridRenderer::SetPositionX(int x)
{
    snakePosX = x;
}

void GridRenderer::SetPositionY(int y)
{
    snakePosY = y;
}

int GridRenderer::GetPositionX() const
{
    return snakePosX;
}

int GridRenderer::GetPositionY() const 
{
    return snakePosY;
}

void GridRenderer::Render(
    const GridMap &grid,
    Renderer &renderer,
    Shader &shader,
    const OrthographicCamera &camera)

{

    for (int y = 0; y < grid.GetHeight(); y++)
    {
        for (int x = 0; x < grid.GetWidth(); x++)
        {
            TileType tile = grid.GetTile(x, y);
            switch (tile)
            {

            case TileType::Player:
            {
                std::cout << "PLAYER FOUND: " << x << ", " << y << std::endl;
                auto it = m_Textures.find(tile);

                if (it == m_Textures.end())
                    continue;

                float posX = x * m_TileSize + m_TileSize / 2.0f;
                float posY = y * m_TileSize + m_TileSize / 2.0f;

                renderer.DrawSprite(
                    *it->second,
                    Vector2(posX, posY),
                    Vector2(m_TileSize, m_TileSize),
                    shader,
                    camera,
                    snakeRotation);

                break;
            }
            case TileType::Apple:
            case TileType::SnakeBody:
            {
                auto it = m_Textures.find(tile);

                if (it == m_Textures.end())
                    continue;


                float posX = x * m_TileSize + m_TileSize / 2.0f;
                float posY = y * m_TileSize + m_TileSize / 2.0f;

                renderer.DrawSprite(
                    *it->second,
                    Vector2(posX, posY),
                    Vector2(m_TileSize, m_TileSize),
                    shader,
                    camera,
                    180.0f);

                break;
            }
            case TileType::Empty:
                continue;
                break;

            case TileType::Wall:
                /* code */
                continue;
                break;

            default:
                break;
            }
        }
    }
}