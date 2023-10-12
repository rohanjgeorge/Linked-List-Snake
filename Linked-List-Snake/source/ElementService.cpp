#include "../header/ElementService.h"
#include "../header/LevelModel.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelController.h"
#include "../header/Obstacle.h"
#include "../header/LevelModel.h"

ElementService::ElementService()
{
}

ElementService::~ElementService()
{
}

void ElementService::initialize()
{
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
	for (int i = 0; i < element_data_list.size(); i++)
	{
		switch (element_data_list[i].element_type)
		{
		case::ElementType::OBSTACLE:
			spawnObstacle(element_data_list, i, cell_width, cell_height);
			break;
		}		
	}
}

const void ElementService::spawnObstacle(std::vector<ElementData>& element_data_list, int index, float cell_width, float cell_height)
{
	Obstacle* obstacle = new Obstacle(element_data_list[index].position.x, 
										element_data_list[index].position.y, 
										cell_width, cell_height);

	obstacle->initialize();
	obstacle_list.push_back(obstacle);
}