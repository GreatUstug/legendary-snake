#ifndef GRID_H
#define GRID_H

#include <vector>

class GameGrid
{
private:
    std::vector<std::vector<char>> grid;

public:
    GameGrid();
    void CreateGrid();
    void Clear();
    void SetCell(int x, int y, char ch);
    char GetCell(int x, int y) const;
    void Print() const;

    const std::vector<std::vector<char>>& GetGrid() const;
    std::vector<std::vector<char>>& GetGrid();
};

#endif