#include "../header/Node.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelView.h"

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
	float x_position = LevelView::border_offset_left + LevelView::border_thickness + (position.x * node_width);
	float y_position = LevelView::border_offset_top + LevelView::border_thickness + (position.y * node_height);

	node_sprite.setPosition(sf::Vector2f(x_position, y_position));
}

void Node::updateNodePosition(sf::Vector2i pos, Direction dir)
{
	position = pos;
	direction = dir;
}

void Node::render()
{
	game_window->draw(node_sprite);
}

void Node::setNextNodeReference(Node* node)
{
	next_node = node;
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
