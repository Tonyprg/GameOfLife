#include "game.hpp"

int main (int argc, char *argv[])
{
    srand(time(NULL));
    Game g("config.txt");
    g.loop();
    return 0;
}
