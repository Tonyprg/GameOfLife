#include "grid.hpp"


int
Grid::countAliveCellsAround (size_t row, size_t col) const
{
    int res = 0;
    for (size_t i = 0; i < 3; ++i)
    {
        for (size_t j = 0; j < 3; ++j)
        {
            // Арифметика по модулю rows и cols.
            // где (rows - 1) или (cols - 1) эквивалентно -1.
            // Такое сложение необходимо, чтобы избежать приколов с (size_t)0 - 1.
            size_t ii = (row + (rows - 1) + i) % rows;
            size_t jj = (col + (cols - 1) + j) % cols;

            if (ii == row && jj == col) continue;
            res += field[ii][jj];
        }
    }
    return res;
}


Grid::Grid (size_t rows, size_t cols)
{
    this->rows = rows;
    this->cols = cols;
    for (size_t i = 0; i < rows; ++i)
    {
        field.push_back(std::vector<bool>(cols));
        for (size_t j = 0; j < cols; ++j)
            field[field.size() - 1][j] = false;
    }
}


void
Grid::fillRandom () const
{
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            field[i][j] = (double)rand() / RAND_MAX < 0.4;
}


void
Grid::clear () const
{
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            field[i][j] = false;
}


void
Grid::nextState () const
{
    auto nextField = field;
    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            int count = countAliveCellsAround(i, j);
            if (field[i][j] == 0 && count == 3)
                nextField[i][j] = true;
            else if (field[i][j] == 1 && count != 2 && count != 3)
                nextField[i][j] = false;
        }
    }
    field = std::move(nextField);
}
