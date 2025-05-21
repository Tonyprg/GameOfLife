#ifndef GRID_HPP
#define GRID_HPP

#include <cstdlib>

#include <vector>
#include <SDL2/SDL.h>

class Grid
{
    private:

        size_t rows;
        size_t cols;
        mutable std::vector<std::vector<bool>> field;

        int countAliveCellsAround (size_t row, size_t col) const;

    public:

        Grid (size_t rows, size_t cols);

        virtual ~Grid () {}

        size_t
        getRows () const {
            return rows;
        }

        size_t
        getCols () const {
            return cols;
        }

        const std::vector<bool>&
        operator[] (size_t i) const {
            return field[i];
        }

        void
        swichCell (size_t i, size_t j) const {
            field[i][j] = !field[i][j];
        }

        // Заполняет поле случайным образом
        void
        fillRandom () const;

        // Очищает поле
        void
        clear () const;

        // Вычисляет следующее состояние поля
        // согласно правилам GameOfLife
        void
        nextState () const;
};

#endif
