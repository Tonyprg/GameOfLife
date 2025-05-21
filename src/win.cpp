#include "win.hpp"


Window::Window (std::string title, int width, int height)
{
    this->width = width;
    this->height = height;
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}


void
Window::redraw (const Grid &gs) const
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (size_t i = 0; i <= gs.getRows(); ++i)
    {
        float y = (float)i * (float)height / (float)gs.getRows();
        SDL_RenderDrawLineF(renderer, 0, y, width, y);
    }
    for (size_t i = 0; i <= gs.getCols(); ++i)
    {
        float x = (float)i * (float)width / (float)gs.getCols();
        SDL_RenderDrawLineF(renderer, x, 0, x, height);
    }
    for (size_t i = 0; i < gs.getRows(); ++i)
    {
        for (size_t j = 0; j < gs.getCols(); ++j)
        {
            if (gs[i][j])
            {
                SDL_FRect rect;
                rect.x = (float)j * (float)width / (float)gs.getCols();
                rect.y = (float)i * (float)height / (float)gs.getRows();
                rect.h = (float)height / (float)gs.getRows();
                rect.w = (float)width / (float)gs.getCols();
                SDL_RenderFillRectF(renderer, &rect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}
