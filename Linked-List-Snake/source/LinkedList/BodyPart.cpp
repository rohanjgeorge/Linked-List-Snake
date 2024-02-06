#include "LinkedList/BodyPart.h"
#include "Global/ServiceLocator.h"
#include "Level/LevelView.h"
#include "Level/LevelModel.h"
#include "Global/Config.h"

namespace LinkedList
{
	using namespace Global;
	using namespace Level;
	using namespace UI::UIElement;

	BodyPart::BodyPart()
	{
		grid_position = sf::Vector2i(0, 0);
		createBodyPartImage();
	}

	BodyPart::~BodyPart()
	{
		destroy();
	}

	void BodyPart::initialize(float width, float height, sf::Vector2i pos, Direction dir)
	{
		bodypart_width = width;
		bodypart_height = height;
		direction = dir;
		grid_position = pos;

		initializeBodyPartImage();
	}

	void BodyPart::createBodyPartImage()
	{
		bodypart_image = new ImageView();
	}

	void BodyPart::initializeBodyPartImage()
	{
		bodypart_image->initialize(Config::snake_body_texture_path, bodypart_width, bodypart_height, getBodyPartScreenPosition());
		bodypart_image->setOriginAtCentre();
	}

	void BodyPart::updateNode(Direction dir)
	{
		direction = dir;
		grid_position = getNextBodyPartPosition();

		bodypart_image->setPosition(getBodyPartScreenPosition());
		bodypart_image->setRotation(getRotationAngle());
		bodypart_image->update();
	}

	sf::Vector2f BodyPart::getBodyPartScreenPosition()
	{
		float x_screen_position = LevelView::border_offset_left + (grid_position.x * bodypart_width) + (bodypart_width / 2);
		float y_screen_position = LevelView::border_offset_top + (grid_position.y * bodypart_height) + (bodypart_height / 2);

		return sf::Vector2f(x_screen_position, y_screen_position);
	}

	void BodyPart::render()
	{
		bodypart_image->render();
	}

	sf::Vector2i BodyPart::getNextBodyPartPosition()
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

	sf::Vector2i BodyPart::getNextPositionDown()
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

	sf::Vector2i BodyPart::getNextPositionUp()
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

	sf::Vector2i BodyPart::getNextPositionRight()
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

	sf::Vector2i BodyPart::getNextPositionLeft()
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

	float BodyPart::getRotationAngle()
	{
		switch (direction)
		{
		case Direction::UP:
			return 270.f;
		case Direction::DOWN:
			return 90.f;
		case Direction::RIGHT:
			return 0;
		case Direction::LEFT:
			return 180.f;
		}
	}

	Direction BodyPart::getDirection()
	{
		return direction;
	}

	sf::Vector2i BodyPart::getPosition()
	{
		return grid_position;
	}

	void BodyPart::destroy()
	{
		delete (bodypart_image);
	}
}