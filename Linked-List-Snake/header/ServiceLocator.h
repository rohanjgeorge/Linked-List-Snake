#pragma once

class EventService;
class GraphicService;
class TimeService;
class SoundService;
class LevelService;
class PlayerService;
class ElementService;
class FoodService;
class UIService;

class ServiceLocator
{
private:
    EventService* event_service;
    GraphicService* graphic_service;
    TimeService* time_service;
    SoundService* sound_service;
    LevelService* level_service;
    PlayerService* player_service;
    ElementService* element_service;
    FoodService* food_service;
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

    EventService* getEventService();
    GraphicService* getGraphicService();
    TimeService* getTimeService();
    SoundService* getSoundService();
    LevelService* getLevelService();
    PlayerService* getPlayerService();
    ElementService* getElementService();
    FoodService* getFoodService();
    UIService* getUIService();
    void deleteServiceLocator();
};