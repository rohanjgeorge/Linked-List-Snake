#include "../header/LevelService.h"
#include "../header/LevelController.h"

LevelService::LevelService()
{
	level_controller = nullptr;

	createLevelControllerAndConfig();
}

LevelService::~LevelService()
{
	destroy();
}

void LevelService::createLevelControllerAndConfig()
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
}

void LevelService::destroy()
{
	delete level_controller;
}