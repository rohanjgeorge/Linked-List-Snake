#pragma once
#include <SFML/Graphics.hpp>

class Obstacle
{
private: 
    sf::RenderWindow* game_window;

    static sf::Texture obstacle_texture;
    static sf::Sprite obstacle_sprite;

    sf::Vector2i grid_position;

    static float cell_width;
    static float cell_height;

    static void initializeObstacleSprite();
    static void scaleObstacleSprite();
    void setObstacleSpritePosition();
    void drawObstacle();

public:
    Obstacle(sf::Vector2i position);
    ~Obstacle();

    static void initialize();
    void update();
    void render();

    static void setupObstacleSprite(float width, float height);
};