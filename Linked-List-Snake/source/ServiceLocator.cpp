#include "../header/ServiceLocator.h"
#include "../header/EventService.h"
#include "../header/GraphicService.h"
#include "../header/TimeService.h"
#include "../header/SoundService.h"
#include "../header/LevelService.h"
#include "../header/UIService.h"
#include "../header/GameService.h"
#include "../header/ElementService.h"
#include "../header/PlayerService.h"

ServiceLocator::ServiceLocator()
{
	graphic_service = nullptr;
	event_service = nullptr;
	time_service = nullptr;
	sound_service = nullptr;
	level_service = nullptr;
	player_service = nullptr;
	element_service = nullptr;
	ui_service = nullptr;
	game_window = nullptr;

	createServices();
}

ServiceLocator::~ServiceLocator() { clearAllServices(); }

void ServiceLocator::createServices()
{
	event_service = new EventService();
	graphic_service = new GraphicService();
	time_service = new TimeService();
	sound_service = new SoundService();
	level_service = new LevelService();
	player_service = new PlayerService();
	element_service = new ElementService();
	ui_service = new UIService();
}

void ServiceLocator::initialize()
{
	graphic_service->initialize();
	sound_service->initialize();
	time_service->initialize();

	game_window = graphic_service->getGameWindow();

	event_service->initialize();
	level_service->initialize();
	player_service->initialize();
	element_service->initialize();
	ui_service->initialize();
}

void ServiceLocator::update()
{
	time_service->update();
	event_service->update();

	if (GameService::getGameState() == GameState::GAMEPLAY)
	{
		level_service->update();
		player_service->update();
		element_service->update();
	}

	ui_service->update();
	graphic_service->update();
}

void ServiceLocator::render()
{
	graphic_service->render();

	if (GameService::getGameState() == GameState::GAMEPLAY)
	{
		level_service->render();
		player_service->render();
		element_service->render();
	}

	ui_service->render();
}

void ServiceLocator::clearAllServices()
{
	delete(ui_service);
	delete(player_service);
	delete(element_service);
	delete(level_service);
	delete(graphic_service);
	delete(sound_service);
	delete(event_service);
	delete(time_service);
}

ServiceLocator* ServiceLocator::getInstance()
{
	static ServiceLocator instance;
	return &instance;
}

sf::RenderWindow* ServiceLocator::getGameWindow() { return game_window; }

EventService* ServiceLocator::getEventService() { return event_service; }

GraphicService* ServiceLocator::getGraphicService() { return graphic_service; }

TimeService* ServiceLocator::getTimeService() { return time_service; }

SoundService* ServiceLocator::getSoundService() { return sound_service; }

LevelService* ServiceLocator::getLevelService() { return level_service; }

PlayerService* ServiceLocator::getPlayerService() { return player_service; }

ElementService* ServiceLocator::getElementService() { return element_service; }

UIService* ServiceLocator::getUIService() { return ui_service; }

void ServiceLocator::deleteServiceLocator() { delete(this); }