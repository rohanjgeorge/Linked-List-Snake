#include "ServiceLocator.h"

ServiceLocator* ServiceLocator::getInstance()
{
	static ServiceLocator instance;
	return &instance;
}

ServiceLocator::ServiceLocator() { initializeServices(); }

ServiceLocator::~ServiceLocator() { clearAllServices(); }

void ServiceLocator::initializeServices()
{
	event_service = new EventService();
	graphic_service = new GraphicService();
	ui_service = new UIService();
	// player_service = new PlayerService();
	/*level_Service = new LevelService();
	food_service = new FoodService();
	sound_service = new SoundService();
	element_service = new ElementService();*/
}

void ServiceLocator::setGameWindow()
{
	game_window = graphic_service->getWindow();

	event_service->setGameWindow(game_window);
	ui_service->setWindow(game_window);
}


void ServiceLocator::clearAllServices()
{
	delete(event_service);
	delete(graphic_service);
	delete(ui_service);
	// delete(player_service);
	/*delete(level_Service);
	delete(food_service);
	delete(sound_service);
	delete(element_service);*/
}

void ServiceLocator::updateServices()
{
	// event_service->update();
	// graphic_service->updateGraphics();
	ui_service->updateUI();
}

EventService* ServiceLocator::getEventService() { return event_service; }

GraphicService* ServiceLocator::getGraphicService() { return graphic_service; }

UIService* ServiceLocator::getUIService() { return ui_service; }

PlayerService* ServiceLocator::getPlayerService() { return player_service; }

LevelService* ServiceLocator::getLevelService() { return level_Service; }

void ServiceLocator::deleteServiceLocator() { delete(this); }
