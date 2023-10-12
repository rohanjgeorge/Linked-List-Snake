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

    float border_width;
    float border_height;
    
    void initializeBackground();
    void initializeBorder();
    void calculateBorderExtents();
    void drawLevel();

public:
    static const int border_thickness = 10;
    static const int border_offset_left = 40;
    static const int border_offset_top = 40;

    LevelView();
    ~LevelView();

    void initialize();
    void update();
    void render();

    float getGridWidth();
    float getGridHeight();
};