#include "GridMap.h"


GridMap::GridMap(int width, int height)
    : m_Width(width),
      m_Height(height)
{
    m_Tiles.resize(height);

    for (int y = 0; y < height; y++)
    {
        m_Tiles[y].resize(width, TileType::Empty);
    }

}

void GridMap::SetTile(int x, int y, TileType type)
{
    if (x < 0 || x >= m_Width ||
        y < 0 || y >= m_Height)
        return;
    m_Tiles[y][x] = type;
}
TileType GridMap::GetTile(int x, int y) const
{
    if (x < 0 || x >= m_Width ||
        y < 0 || y >= m_Height)
    {
        return TileType::Empty;
    }

    return m_Tiles[y][x];
}

void GridMap::Clear()
{
    for (int y = 0; y < m_Height; y++)
    {
        for (int x = 0; x < m_Width; x++)
        {
            m_Tiles[y][x] = TileType::Empty;
        }
    }

    m_Tiles[m_Height / 2][m_Width / 2] = TileType::Player;
}


int GridMap::GetWidth() const
{
    return m_Width;
}

int GridMap::GetHeight() const
{
    return m_Height;
}