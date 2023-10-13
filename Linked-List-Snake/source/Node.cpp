#include "../header/Node.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelView.h"
#include "../header/LevelModel.h"

Node::Node()
{
	next_node = nullptr;
	position = sf::Vector2i(0, 0);
}

Node::~Node()
{
}

void Node::initialize(float width, float height, sf::Vector2i pos, Direction dir)
{
	node_width = width;
	node_height = height;
	direction = dir;

	position = pos;

	game_window = ServiceLocator::getInstance()->getGameWindow();
	initializeNodeSprite();
}

void Node::initializeNodeSprite()
{
	if (node_texture.loadFromFile("assets/textures/snake_body.png"))
	{
		node_sprite.setTexture(node_texture);
		scaleNodeSprite();
		setNodeSpritePosition();
	}
}

void Node::scaleNodeSprite()
{
	node_sprite.setScale(
		static_cast<float>(node_width) / node_sprite.getTexture()->getSize().x,
		static_cast<float>(node_height) / node_sprite.getTexture()->getSize().y
	);
}

void Node::setNodeSpritePosition()
{
	float x_position = LevelView::border_offset_left  + (position.x * node_width);
	float y_position = LevelView::border_offset_top  + (position.y * node_height);

	node_sprite.setPosition(sf::Vector2f(x_position, y_position));
}

void Node::updateNodePosition(Direction dir)
{
	direction = dir;
	position = getNextNodePosition();
	setNodeSpritePosition();
}

void Node::render()
{
	game_window->draw(node_sprite);
}

void Node::setNextNodeReference(Node* node)
{
	next_node = node;
}

sf::Vector2i Node::getNextNodePosition() 
{
	switch (direction) 
	{
	case Direction::UP:
		return getNextPositionUp();
	case Direction::DOWN:
		return getNextPositionDown();
	case Direction::RIGHT:
		return getNextPositionRight();
	case Direction::LEFT:
		return getNextPositionLeft();
	default:
		return position;
	}
}

sf::Vector2i Node::getNextPositionDown() 
{
	if (position.y >= LevelModel::number_of_rows - 1)
	{
		return sf::Vector2i(position.x, 0);
	}
	else 
	{
		return sf::Vector2i(position.x, position.y + 1);
	}
}

sf::Vector2i Node::getNextPositionUp()
{
	if (position.y <= 0) 
	{
		return sf::Vector2i(position.x, LevelModel::number_of_rows - 1);
	}
	else 
	{
		return sf::Vector2i(position.x, position.y - 1);
	}
}

sf::Vector2i Node::getNextPositionRight() 
{
	if (position.x >= LevelModel::number_of_columns - 1)
	{
		return sf::Vector2i(0, position.y);
	}
	else
	{
		return sf::Vector2i(position.x + 1, position.y);
	}
}

sf::Vector2i Node::getNextPositionLeft() 
{
	if (position.x <= 0)
	{
		return sf::Vector2i(LevelModel::number_of_columns - 1, position.y);
	}
	else 
	{
		return sf::Vector2i(position.x - 1, position.y);
	}
}

Node* Node::getNextNodeReference()
{
	return next_node;
}

Direction Node::getNodeDirection()
{
	return direction;
}

sf::Vector2i Node::getNodePosition()
{
	return position;
}
