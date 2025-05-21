#include <cmath>
#include "event.hpp"


EventSwitch::EventSwitch (const Window &_window, const Grid &_grid):
    window(_window), grid(_grid) {}


bool
EventSwitch::check (const SDL_Event &e) const {
    return e.type == SDL_MOUSEBUTTONDOWN;
}


void
EventSwitch::eval (const SDL_Event &e) {
    grid.swichCell((float)e.button.y / (float)window.getHeight() * grid.getRows(),
                   (float)e.button.x / (float)window.getWidth() * grid.getCols());
    window.redraw(grid);
}


EventPause::EventPause (bool &_isPause):
    isPause(_isPause) {}


bool
EventPause::check (const SDL_Event &e) const {
    return e.type == SDL_KEYDOWN and
           e.key.keysym.sym == SDLK_p;
}


void
EventPause::eval (const SDL_Event &e) {
    isPause = not isPause;
}


EventChangeDelay::EventChangeDelay (Uint64 &_updateDelay):
    updateDelay(_updateDelay)
{
    beginDelay = updateDelay;
    pw = 0;
}


bool
EventChangeDelay::check (const SDL_Event &e) const {
    return e.type == SDL_KEYDOWN and
           (e.key.keysym.sym == SDLK_i or e.key.keysym.sym == SDLK_d);
}


void
EventChangeDelay::eval (const SDL_Event &e)
{
    if (e.key.keysym.sym == SDLK_i)
        pw = std::min(pw - 1, 10); // decrease delay => increase speed
    else if (e.key.keysym.sym == SDLK_d)
        pw = std::max(pw + 1, -10); // increase delay => decrease speed
    updateDelay = beginDelay * std::pow(1.6, pw);
    updateDelay = std::min((Uint64)2000, std::max((Uint64)1, updateDelay));
    // в итоге 1 <= updateDelay <= 2000
}


EventFillRandom::EventFillRandom (const Window &_window, const Grid &_grid):
    window(_window), grid(_grid) { }


bool
EventFillRandom::check (const SDL_Event &e) const {
    return e.type == SDL_KEYDOWN and
           e.key.keysym.sym == SDLK_r;
}


void
EventFillRandom::eval (const SDL_Event &e)
{
    grid.fillRandom();
    window.redraw(grid);
}


EventClearGrid::EventClearGrid (const Window &_window, const Grid &_grid):
    window(_window), grid(_grid) {}


bool
EventClearGrid::check (const SDL_Event &e) const {
    return e.type == SDL_KEYDOWN and
           e.key.keysym.sym == SDLK_c;
}


void
EventClearGrid::eval (const SDL_Event &e)
{
    grid.clear();
    window.redraw(grid);
}
