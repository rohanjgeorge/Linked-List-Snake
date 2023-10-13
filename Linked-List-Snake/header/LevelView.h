#pragma once
#include <SFML/Graphics.hpp>

class LevelView
{
private:
    sf::RenderWindow* game_window;
    sf::RectangleShape backgroundRect;
    sf::RectangleShape border_rect;

    sf::Color background_color = sf::Color(180, 200, 160);
    sf::Color border_color = sf::Color::Black;

    float grid_width;
    float grid_height;
    
    void initializeBackground();
    void initializeBorder();
    void calculateGridExtents();
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