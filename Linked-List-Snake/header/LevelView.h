#pragma once
#include <SFML/Graphics.hpp>

class LevelView
{
private:
    sf::RenderWindow* game_window;
    sf::RectangleShape backgroundRect;
    sf::RectangleShape border_rect;

    sf::Color background_color = sf::Color(0, 153, 0);  // Green
    sf::Color border_color = sf::Color::Black;

    float border_thickness = 10.0f;

    // Border offset from the ends
    float x_offset = 40.0f;
    float y_offset = 40.0f;
    float border_width;
    float border_height;
    
    void initializeBackground();
    void initializeBorder();
    void calculateBorderExtents();
    void drawLevel();

public:
    LevelView();
    ~LevelView();

    void initialize();
    void update();
    void render();

    float getGridWidth();
    float getGridHeight();
};