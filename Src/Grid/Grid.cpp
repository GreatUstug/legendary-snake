#include "Grid.h"
#include "../../Include/Constants.h"
#include <iostream>
#include <algorithm>

GameGrid::GameGrid() 
{
    CreateGrid();
}

void GameGrid::CreateGrid()
{
    grid.resize(ROWS_WITH_BORDERS, std::vector<char>(COLS_WITH_BORDERS, FIELD_CHAR));

    std::fill(grid.front().begin(), grid.front().end(), BORDER_CHAR);
    std::fill(grid.back().begin(), grid.back().end(), BORDER_CHAR);

    for (auto it = grid.begin() + 1; it != grid.end() - 1; ++it)
    {
        it->front() = BORDER_CHAR;
        it->back() = BORDER_CHAR;
    }
}

void GameGrid::Clear()
{
    for (auto& row : grid)
    {
        std::fill(row.begin(), row.end(), FIELD_CHAR);
    }

    std::fill(grid.front().begin(), grid.front().end(), BORDER_CHAR);
    std::fill(grid.back().begin(), grid.back().end(), BORDER_CHAR);

    for (auto it = grid.begin() + 1; it != grid.end() - 1; ++it)
    {
        it->front() = BORDER_CHAR;
        it->back() = BORDER_CHAR;
    }
}

void GameGrid::SetCell(int x, int y, char ch)
{
    if (x >= 0 && x < COLS_WITH_BORDERS && y >= 0 && y < ROWS_WITH_BORDERS)
    {
        grid[y][x] = ch;
    }
}

char GameGrid::GetCell(int x, int y) const
{
    if (x >= 0 && x < COLS_WITH_BORDERS && y >= 0 && y < ROWS_WITH_BORDERS)
    {
        return grid[y][x];
    }
    return FIELD_CHAR;
}

void GameGrid::Print() const
{
    std::cout << CLEAR_SCREEN;
    for (const auto& row : grid)
    {
        std::cout.write(row.data(), row.size());
        std::cout << '\n';
    }
}

const std::vector<std::vector<char>>& GameGrid::GetGrid() const
{
    return grid;
}

std::vector<std::vector<char>>& GameGrid::GetGrid()
{
    return grid;
}