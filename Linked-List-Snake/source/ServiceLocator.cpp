#include "../header/ServiceLocator.h"
#include "../header/GraphicService.h"

ServiceLocator::ServiceLocator()
{
	graphic_service = nullptr;
	game_window = nullptr;

	createServices();
}

ServiceLocator::~ServiceLocator() { clearAllServices(); }

void ServiceLocator::createServices()
{
	graphic_service = new GraphicService();
}

void ServiceLocator::initialize()
{
	graphic_service->initialize();
	game_window = graphic_service->getGameWindow();
}

void ServiceLocator::update()
{
	graphic_service->update();
}

void ServiceLocator::render()
{
	graphic_service->render();
}

void ServiceLocator::clearAllServices()
{
	delete(graphic_service);
}

ServiceLocator* ServiceLocator::getInstance()
{
	static ServiceLocator instance;
	return &instance;
}

sf::RenderWindow* ServiceLocator::getGameWindow() { return game_window; }

GraphicService* ServiceLocator::getGraphicService() { return graphic_service; }

void ServiceLocator::deleteServiceLocator() { delete(this); }