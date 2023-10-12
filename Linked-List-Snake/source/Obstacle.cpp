#include "../header/Obstacle.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelView.h"

sf::Texture Obstacle::obstacle_texture;
sf::Sprite Obstacle::obstacle_sprite;

bool Obstacle::texture_loaded = false;

Obstacle::Obstacle(int x, int y, float width, float height)
{
	x_index = x;
	y_index = y;
	cell_width = width;
	cell_height = height;
}

Obstacle::~Obstacle()
{
}

void Obstacle::initialize()
{
	game_window = ServiceLocator::getInstance()->getGameWindow();

	initializeObstacleSprite();
}

void Obstacle::initializeObstacleSprite()
{
	if (texture_loaded) return;

	if (obstacle_texture.loadFromFile("assets/textures/obstacle.png"))
	{
		obstacle_sprite.setTexture(obstacle_texture);
		scaleObstacleSprite();
		texture_loaded = true;
	}
}

void Obstacle::scaleObstacleSprite()
{
	obstacle_sprite.setScale(
		static_cast<float>(cell_width) / obstacle_sprite.getTexture()->getSize().x,
		static_cast<float>(cell_height) / obstacle_sprite.getTexture()->getSize().y
	);
}

void Obstacle::update()
{
}

void Obstacle::render()
{
	drawObstacle();
}

void Obstacle::drawObstacle()
{
	setObstacleSpritePosition();
	game_window->draw(obstacle_sprite);
}

void Obstacle::setObstacleSpritePosition()
{
	float left_offset = LevelView::border_offset_left + LevelView::border_thickness;
	float top_offset = LevelView::border_offset_top + LevelView::border_thickness;

	float x_position = left_offset + (cell_width * x_index);
	float y_position = top_offset + (cell_height * y_index);

	obstacle_sprite.setPosition(x_position, y_position);
}