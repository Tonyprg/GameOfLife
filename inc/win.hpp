#ifndef WIN_HPP
#define WIN_HPP

#include <string>
#include <SDL2/SDL.h>

#include "grid.hpp"

class Window
{
    private:

        size_t width;
        size_t height;

        SDL_Window   *window;
        SDL_Renderer *renderer;
        SDL_Surface  *surface;

    public:

        Window (std::string title, int width, int height);
        virtual ~Window () {}

        size_t
        getWidth () const {
            return width;
        }

        size_t
        getHeight () const {
            return height;
        }

        void
        redraw (const Grid &gs) const;
};

#endif
