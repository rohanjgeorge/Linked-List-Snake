#pragma once
#include <sfml/Graphics/RenderWindow.hpp>
class EventService;
class GraphicService;
class TimeService;
class SoundService;
class LevelService;
class PlayerService;
class ElementService;
class UIService;

class ServiceLocator
{
private:
    sf::RenderWindow* game_window;
    EventService* event_service;
    GraphicService* graphic_service;
    TimeService* time_service;
    SoundService* sound_service;
    LevelService* level_service;
    PlayerService* player_service;
    ElementService* element_service;
    UIService* ui_service;

    ServiceLocator();
    ~ServiceLocator();

    void createServices();
    void clearAllServices();

public:
    static ServiceLocator* getInstance();

    void initialize();
    void update();
    void render();

    sf::RenderWindow* getGameWindow();
    EventService* getEventService();
    GraphicService* getGraphicService();
    TimeService* getTimeService();
    SoundService* getSoundService();
    LevelService* getLevelService();
    PlayerService* getPlayerService();
    ElementService* getElementService();
    UIService* getUIService();
    void deleteServiceLocator();
};