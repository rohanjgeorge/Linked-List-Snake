#include "../header/PlayerController.h"
#include "../header/SingleLinkedList.h"
#include "../header/ServiceLocator.h"
#include "../header/LevelService.h"
#include "../header/LevelController.h"
#include "../header/LevelModel.h"

PlayerController::PlayerController()
{
	single_linked_list = nullptr;

	createLinkedList();
}

PlayerController::~PlayerController()
{
	destroy();
}

void PlayerController::createLinkedList()
{
	single_linked_list = new SingleLinkedList();
}

void PlayerController::initialize()
{
	float width = ServiceLocator::getInstance()->getLevelService()->getLevelController()->getLevelModel()->getGridCellWidth();
	float height = ServiceLocator::getInstance()->getLevelService()->getLevelController()->getLevelModel()->getGridCellHeight();

	single_linked_list->initialize(width, height);
}

void PlayerController::update()
{
	single_linked_list->update();
}

void PlayerController::render()
{
	single_linked_list->render();
}

void PlayerController::spawnPlayer()
{
	for (int i = 0; i < initial_snake_length; i++)
	{
		single_linked_list->insertNode();
	}
}

void PlayerController::destroy()
{
	delete (single_linked_list);
}