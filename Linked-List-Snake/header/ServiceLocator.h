#pragma once
#include <sfml/Graphics/RenderWindow.hpp>
class GraphicService;
class SoundService;

class ServiceLocator
{
private:
    sf::RenderWindow* game_window;
    GraphicService* graphic_service;
    SoundService* sound_service;

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
    GraphicService* getGraphicService();
    SoundService* getSoundService();
    void deleteServiceLocator();
};