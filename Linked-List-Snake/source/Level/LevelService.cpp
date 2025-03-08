#include "Global/ServiceLocator.h"
#include "Level/LevelService.h"
#include "Level/LevelController.h"
#include <Level/LevelNumber.h>

namespace Level
{
	using namespace Global;

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

	void LevelService::createLevel(LevelNumber level_to_load)
	{
		current_level = level_to_load;
	}

	void LevelService::setCurrentLevelNumber(LevelNumber level_to_load)
	{
		current_level = level_to_load;
	}

	void LevelService::destroy()
	{
		delete level_controller;
	}
}