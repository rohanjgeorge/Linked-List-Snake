#include "header/GameService.h"

int main()
{
    GameService* game_service = new GameService();
    game_service->ignite();

    game_service->update();
    game_service->render();

    return 0;
}