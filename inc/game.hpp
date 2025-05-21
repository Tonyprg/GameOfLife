#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>

#include <memory>
#include <map>

#include "grid.hpp"
#include "win.hpp"
#include "event.hpp"

class Game
{
    private:

        static std::map<std::string, int>
        getConfig (const std::string &fileName);

    private:

        std::map<std::string, int> config;
        Window window;
        Grid   grid;
        bool   isPause;
        Uint64 updateDelay;
        Uint64 lastUpdateTime;

        // Все обработчики по большей части замыкают вышеуказанные поля,
        // поэтому у них в конструкторах есть ссылки на необходимые поля.
        std::vector<std::shared_ptr<Event>> handlers;


        // Обновляет сетку и перерисовывает окно,
        // но при условии, что прошло достаточно времени
        // с момента последнего обновления.
        void
        update ();

    public:

        Game (const std::string &fileName);

        virtual ~Game ();

        // Запускает игру, пока окно не будет закрыто.
        void
        loop ();

};

#endif
