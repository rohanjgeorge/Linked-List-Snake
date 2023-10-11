#include "../header/LevelController.h"
#include "../header/LevelModel.h"
#include "../header/LevelView.h"

LevelController::LevelController()
{
	level_model = new LevelModel();
	level_view = new LevelView();
}

LevelController::~LevelController()
{
	delete level_model;
	delete level_view;
}

void LevelController::initialize()
{
	level_view->initialize();
	level_model->initialize(level_view->getGridWidth(), level_view->getGridHeight());
}

void LevelController::update()
{
	level_view->update();
}

void LevelController::render()
{
	level_view->render();
}

LevelModel* LevelController::getLevelModel()
{
	return level_model;
}

LevelView* LevelController::getLevelView()
{
	return level_view;
}
