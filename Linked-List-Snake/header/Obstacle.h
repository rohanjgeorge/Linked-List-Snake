#pragma once
#include <SFML/Graphics.hpp>

class Obstacle
{
private: 
    sf::RenderWindow* game_window;

    static sf::Texture obstacle_texture;
    static sf::Sprite obstacle_sprite;
    
    static bool texture_loaded;

    int x_index;
    int y_index;

    float cell_width;
    float cell_height;

    void initializeObstacleSprite();
    void scaleObstacleSprite();
    void setObstacleSpritePosition();
    void drawObstacle();

public:
    Obstacle(int x, int y, float cell_width, float cell_height);
    ~Obstacle();

    void initialize();
    void update();
    void render();
};