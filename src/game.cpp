#include <iostream>

#include "parse.hpp"
#include "game.hpp"


std::map<std::string, int>
Game::getConfig (const std::string &fileName)
{
    Parser p;
    p.addDefaultParameter("width",  500, 100, 700);
    p.addDefaultParameter("height", 500, 100, 700);
    p.addDefaultParameter("rows",    40,  10, 200);
    p.addDefaultParameter("cols",    40,  10, 200);

    std::map<std::string, int> config;

    try {
        config = p.readFile(fileName);
    } catch (const ErrorOpenFile &err) {
        config = p.getDefaultParameters();
    } catch (const ErrorParse &err) {
        config = p.getDefaultParameters();
    }

    try {
        p.writeFile(fileName, config);
    } catch (const ErrorOpenFile &err) {
        std::cout << "Неудалось записать файл." << std::endl;
    }

    return config;
}


void
Game::update ()
{
    if (not isPause and
        (SDL_GetTicks64() - lastUpdateTime > updateDelay))
    {
        grid.nextState();
        window.redraw(grid);
        lastUpdateTime = SDL_GetTicks64();
    }
}


Game::Game (const std::string &fileName):
    config(getConfig(fileName)),
    window("", config["width"], config["height"]),
    grid(config["rows"], config["cols"]),
    isPause(true),
    updateDelay(300)
{

    SDL_Init(SDL_INIT_EVERYTHING);
    handlers.push_back(std::make_shared<EventSwitch>(window, grid));
    handlers.push_back(std::make_shared<EventPause>(isPause));
    handlers.push_back(std::make_shared<EventChangeDelay>(updateDelay));
    handlers.push_back(std::make_shared<EventFillRandom>(window, grid));
    handlers.push_back(std::make_shared<EventClearGrid>(window, grid));
    window.redraw(grid);
    update();
}


Game::~Game () {
    SDL_Quit();
}


void
Game::loop ()
{
    bool running = true;
    SDL_Event event;
    while (running)
    {
        while (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
                running = false;

            for (auto hand: handlers)
                if (hand->check(event))
                    hand->eval(event);
        }
        update();
    }
}
