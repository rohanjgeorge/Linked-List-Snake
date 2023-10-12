#include "../header/LevelService.h"
#include "../header/LevelController.h"
#include "../header/ServiceLocator.h"
#include "../header/ElementService.h"
#include "../header/LevelModel.h"

LevelService::LevelService()
{
	level_controller = nullptr;

	createLevelController();
}

LevelService::~LevelService()
{
	destroy();
}

void LevelService::createLevelController()
{
	level_controller = new LevelController();
}

void LevelService::initialize()
{
	level_controller->initialize();
}

void LevelService::update()
{
	level_controller->update();
}

void LevelService::render()
{
	level_controller->render();
}

void LevelService::createLevel(Level level_index)
{
	spawnLevelElements(level_index);
}

void LevelService::spawnLevelElements(Level level_index)
{
	float cell_width = level_controller->getLevelModel()->getGridCellWidth();
	float cell_height = level_controller->getLevelModel()->getGridCellHeight();

	std::vector<ElementData> element_data_list = level_controller->getElementDataList((int)level_index);
	ServiceLocator::getInstance()->getElementService()->spawnElements(element_data_list, cell_width, cell_height);
}

LevelController* LevelService::getLevelController()
{
	return level_controller;
}

void LevelService::destroy()
{
	delete level_controller;
}