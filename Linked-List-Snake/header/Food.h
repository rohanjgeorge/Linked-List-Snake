#pragma once
#include <SFML/Graphics.hpp>

class ImageView;
enum class FoodType;

class Food
{
private:
    ImageView* food_image;

    sf::Vector2i grid_position;

    float cell_width;
    float cell_height;

    FoodType food_type;

    void initializeFoodImage();
    sf::String getFoodTexturePath();
    sf::Vector2f getFoodImagePosition();

public:
    static const int number_of_foods = 8;

    Food();
    ~Food();

    void initialize(sf::Vector2i grid_pos, float width, float height, FoodType type);
    void update();
    void render();

    FoodType getFoodType();
};