#ifndef GRID_H
#define GRID_H

#include <vector>
#include <string>

class GameGrid {
private:
    std::vector<std::vector<char>> grid;

public:
    GameGrid();
    void CreateGrid();
    void Clear();
    void SetCell(int x, int y, char ch);
    char GetCell(int x, int y) const;
    void Print() const;

    // Добавляем два метода для доступа к сетке
    const std::vector<std::vector<char>>& GetGrid() const; // Константная версия
    std::vector<std::vector<char>>& GetGrid(); // Неконстантная версия
};

#endif // GRID_H