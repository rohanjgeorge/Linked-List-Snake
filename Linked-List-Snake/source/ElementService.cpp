#include "../header/ElementService.h"
#include "../header/LevelModel.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelController.h"
#include "../header/Obstacle.h"
#include "../header/LevelModel.h"

ElementService::ElementService() = default;

ElementService::~ElementService() = default;

void ElementService::initialize() 
{
	Obstacle::initialize();
}

void ElementService::update()
{
	for (int i = 0; i < obstacle_list.size(); i++)
	{
		obstacle_list[i]->update();
	}
}

void ElementService::render()
{
	for (int i = 0; i < obstacle_list.size(); i++)
	{
		obstacle_list[i]->render();
	}
}

const void ElementService::spawnElements(std::vector<ElementData>& element_data_list, float cell_width, float cell_height)
{
	Obstacle::setupObstacleSprite(cell_width, cell_height);

	for (int i = 0; i < element_data_list.size(); i++)
	{
		switch (element_data_list[i].element_type)
		{
		case::ElementType::OBSTACLE:
			spawnObstacle(element_data_list[i].position);
			break;
		}		
	}
}

void ElementService::spawnObstacle(sf::Vector2i position)
{
	Obstacle* obstacle = new Obstacle(position);

	obstacle->initialize();
	obstacle_list.push_back(obstacle);
}