#include "GameEngine.h"

int main()
{
    GameEngine* game_engine = new GameEngine();
    game_engine->ignite();

    while(game_engine->isRunning())
    {
        game_engine->update();
    }

    return 0;
}
