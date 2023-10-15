#include "../header/Node.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelView.h"
#include "../header/LevelModel.h"
#include "../header/ImageView.h"
#include "../header/Config.h"

Node::Node()
{
	next_node = nullptr;
	grid_position = sf::Vector2i(0, 0);
	node_image = new ImageView();
}

Node::~Node()
{
	delete (node_image);
}

void Node::initialize(float width, float height, sf::Vector2i pos, Direction dir)
{
	node_width = width;
	node_height = height;
	direction = dir;
	grid_position = pos;

	initializeNodeUI();
}

void Node::initializeNodeUI()
{
	node_image->initialize(Config::snake_body_texture_path, node_width, node_height, getNodeScreenPosition());
}

void Node::updateNode(Direction dir)
{
	direction = dir;
	grid_position = getNextNodePosition();

	node_image->setPosition(getNodeScreenPosition());
	node_image->update();
}

sf::Vector2f Node::getNodeScreenPosition()
{
	float x_screen_position = LevelView::border_offset_left + (grid_position.x * node_width);
	float y_screen_position = LevelView::border_offset_top + (grid_position.y * node_height);

	return sf::Vector2f(x_screen_position, y_screen_position);
}

void Node::render()
{
	node_image->render();
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
		return grid_position;
	}
}

sf::Vector2i Node::getNextPositionDown() 
{
	if (grid_position.y >= LevelModel::number_of_rows - 1)
	{
		return sf::Vector2i(grid_position.x, 0);
	}
	else 
	{
		return sf::Vector2i(grid_position.x, grid_position.y + 1);
	}
}

sf::Vector2i Node::getNextPositionUp()
{
	if (grid_position.y <= 0)
	{
		return sf::Vector2i(grid_position.x, LevelModel::number_of_rows - 1);
	}
	else 
	{
		return sf::Vector2i(grid_position.x, grid_position.y - 1);
	}
}

sf::Vector2i Node::getNextPositionRight() 
{
	if (grid_position.x >= LevelModel::number_of_columns - 1)
	{
		return sf::Vector2i(0, grid_position.y);
	}
	else
	{
		return sf::Vector2i(grid_position.x + 1, grid_position.y);
	}
}

sf::Vector2i Node::getNextPositionLeft() 
{
	if (grid_position.x <= 0)
	{
		return sf::Vector2i(LevelModel::number_of_columns - 1, grid_position.y);
	}
	else 
	{
		return sf::Vector2i(grid_position.x - 1, grid_position.y);
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
	return grid_position;
}
