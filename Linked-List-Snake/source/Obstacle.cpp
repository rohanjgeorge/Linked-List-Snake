#include "../header/Obstacle.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelView.h"
#include "../header/GraphicService.h"

sf::Texture Obstacle::obstacle_texture;
sf::Sprite Obstacle::obstacle_sprite;
float Obstacle::cell_width = 0.f;
float Obstacle::cell_height = 0.f;

Obstacle::Obstacle(sf::Vector2i position)
{
	grid_position = position;
	game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
}

Obstacle::~Obstacle() = default;

void Obstacle::initialize()
{
	initializeObstacleSprite();
}

void Obstacle::initializeObstacleSprite()
{
	if (obstacle_texture.loadFromFile("assets/textures/obstacle.png"))
	{
		obstacle_sprite.setTexture(obstacle_texture);
	}
}

void Obstacle::setupObstacleSprite(float width, float height)
{
	cell_width = width;
	cell_height = height;

	scaleObstacleSprite();
}

void Obstacle::scaleObstacleSprite()
{
	obstacle_sprite.setScale(
		static_cast<float>(cell_width) / obstacle_sprite.getTexture()->getSize().x,
		static_cast<float>(cell_height) / obstacle_sprite.getTexture()->getSize().y
	);
}

void Obstacle::update() { }

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

	float screen_position_x = left_offset + (cell_width * grid_position.x);
	float screen_position_y = top_offset + (cell_height * grid_position.y);

	obstacle_sprite.setPosition(screen_position_x, screen_position_y);
}