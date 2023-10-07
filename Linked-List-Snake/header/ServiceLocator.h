#pragma once
#include <sfml/Graphics/RenderWindow.hpp>

class GraphicService;

class ServiceLocator
{
private:
    sf::RenderWindow* game_window;
    GraphicService* graphic_service;

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
    void deleteServiceLocator();
};