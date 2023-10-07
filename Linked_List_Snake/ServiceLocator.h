#pragma once
#include "ElementService.h"
#include "EventService.h"
#include "FoodService.h"
#include "GraphicService.h"
#include "LevelService.h"
#include "PlayerService.h"
#include "SoundService.h"
#include "UIService.h"

class ServiceLocator
{
private:
    sf::RenderWindow* game_window;
    EventService* event_service;
    GraphicService* graphic_service;
    LevelService* level_Service;
    PlayerService* player_service;
    UIService* ui_service;
    FoodService* food_service;
    SoundService* sound_service;
    ElementService* element_service;

    ServiceLocator();
    ~ServiceLocator();

    void initializeServices();
    void clearAllServices();

public:
    static ServiceLocator* getInstance();

    void updateServices();
    void setGameWindow();
    EventService* getEventService();
    GraphicService* getGraphicService();
    PlayerService* getPlayerService();
    LevelService* getLevelService();
    UIService* getUIService();
    void deleteServiceLocator();

    enum GameState
    {
	    SPLASH_SCREEN,
        MAIN_MENU,
        INSTRUCTIONS,
        SNAKE_SELECTION,
        GAMEPLAY,
        GAME_END
    };
};
