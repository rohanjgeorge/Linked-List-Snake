#include "../header/UIService.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"

UIService::UIService()
{
	game_window = nullptr;
}

UIService::~UIService()
{
	destroy();
}

void UIService::initialize()
{
	game_window = ServiceLocator::getInstance()->getGameWindow();
}

void UIService::update()
{
}

void UIService::render()
{
}

void UIService::destroy()
{
}