
#pragma once

#include <vector>

enum class TileType
{
    Empty = 0,
    Player = 1,
    Apple = 2,
    SnakeBody = 3,
    Wall = 4
};

class GridMap
{
public:
    GridMap(int width, int height);
    void SetTile(int x, int y, TileType type);
    TileType GetTile(int x, int y) const;
    void Clear();
    int GetWidth() const;
    int GetHeight() const;
    

private:
    int m_Width;
    int m_Height;

    std::vector<std::vector<TileType>> m_Tiles;

};
