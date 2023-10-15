#pragma once
#include <SFML/Graphics.hpp>

class ImageView;

class Obstacle
{
private: 
    ImageView* obstacle_image;

    sf::Vector2i grid_position;

    float cell_width;
    float cell_height;

    void initializeObstacleImage();
    sf::Vector2f getObstacleImagePosition();

public:
    Obstacle();
    ~Obstacle();

    void initialize(sf::Vector2i grid_pos, float width, float height);
    void update();
    void render();
};