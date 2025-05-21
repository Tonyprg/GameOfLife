#ifndef EVENT_HPP
#define EVENT_HPP

#include <SDL2/SDL.h>

#include "win.hpp"
#include "grid.hpp"

class Event
{
    public:

        virtual bool
        check (const SDL_Event &e) const = 0;

        virtual void
        eval (const SDL_Event &e) = 0;
};

class EventSwitch: public Event
{
    private:

        const Window &window;
        const Grid &grid;

    public:

        EventSwitch (const Window &_window, const Grid &_grid);

        virtual bool
        check (const SDL_Event &e) const;

        virtual void
        eval (const SDL_Event &e);
};

class EventPause: public Event
{
    private:

        bool &isPause;

    public:

        EventPause (bool &_isPause);

        virtual bool
        check (const SDL_Event &e) const;

        virtual void
        eval (const SDL_Event &e);
};

class EventChangeDelay: public Event
{
    private:

        Uint64 &updateDelay;

        // Исключаем влияние погрешности
        // updateDelay = beginDelay * (1.6 ^ pw)
        Uint64 beginDelay;
        int pw;

    public:

        EventChangeDelay (Uint64 &_updateDelay);

        virtual bool
        check (const SDL_Event &e) const;

        virtual void
        eval (const SDL_Event &e);
};

class EventFillRandom: public Event
{
    private:

        const Window &window;
        const Grid &grid;

    public:

        EventFillRandom (const Window &_window, const Grid &_grid);

        virtual bool
        check (const SDL_Event &e) const;

        virtual void
        eval (const SDL_Event &e);
};

class EventClearGrid: public Event
{
    private:

        const Window &window;
        const Grid &grid;

    public:

        EventClearGrid (const Window &_window, const Grid &_grid);

        virtual bool
        check (const SDL_Event &e) const;

        virtual void
        eval (const SDL_Event &e);
};

#endif
