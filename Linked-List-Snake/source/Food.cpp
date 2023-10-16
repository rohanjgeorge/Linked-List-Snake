#include "../header/Food.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelView.h"
#include "../header/ImageView.h"
#include "../header/Config.h"

Food::Food()
{
	food_image = new ImageView();
}

Food::~Food()
{
	delete (food_image);
}

void Food::initialize(sf::Vector2i grid_pos, float width, float height, FoodType type)
{
	grid_position = grid_pos;
	cell_width = width;
	cell_height = height;
	food_type = type;

	initializeFoodImage();
}

void Food::initializeFoodImage()
{
	sf::Vector2f screen_position = getFoodImagePosition();
	sf::String food_texture_path = getFoodTexturePath();

	food_image->initialize(food_texture_path, cell_width, cell_height, screen_position);
	food_image->show();
}

sf::String Food::getFoodTexturePath()
{
	switch (food_type)
	{
	case FoodType::APPLE:
		return Config::apple_texture_path;

	case FoodType::MANGO:
		return Config::mango_texture_path;

	case FoodType::ORANGE:
		return Config::orange_texture_path;

	case FoodType::PIZZA:
		return Config::pizza_texture_path;

	case FoodType::BURGER:
		return Config::burger_texture_path;

	case FoodType::CHEESE:
		return Config::cheese_texture_path;

	case FoodType::POISION:
		return Config::poision_texture_path;

	case FoodType::ALCOHOL:
		return Config::alcohol_texture_path;
	}
}

void Food::update()
{
	food_image->update();
}

void Food::render()
{
	food_image->render();
}

FoodType Food::getFoodType()
{
	return food_type;
}

sf::Vector2f Food::getFoodImagePosition()
{
	float screen_position_x = LevelView::border_offset_left + (cell_width * grid_position.x);
	float screen_position_y = LevelView::border_offset_top + (cell_height * grid_position.y);

	return sf::Vector2f(screen_position_x, screen_position_y);
}