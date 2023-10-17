#include "../header/FoodService.h"
#include "../header/ServiceLocator.h"
#include "../header/TimeService.h"
#include "../header/Food.h"
#include "../header/LevelModel.h"
#include "../header/PlayerService.h"

FoodService::FoodService() : random_engine(random_device())
{
	current_food_item = nullptr;
}

FoodService::~FoodService()
{
	destroyFood();
}

void FoodService::initialize() 
{
	elapsed_duration = spawn_duration;
}

void FoodService::update()
{
	if (current_spawning_status == FoodSpawningStatus::ACTIVE)
	{
		updateElapsedDuration();
		handleFoodSpawning();
	}

	if (current_food_item) current_food_item->update();
}

void FoodService::render()
{
	if (current_food_item) current_food_item->render();
}

void FoodService::startFoodSpawning(float width, float height)
{
	current_spawning_status = FoodSpawningStatus::ACTIVE;

	cell_width = width;
	cell_height = height;
}

void FoodService::stopFoodSpawning()
{
	current_spawning_status = FoodSpawningStatus::IN_ACTIVE;
	destroyFood();
	reset();
}

Food* FoodService::createFood(sf::Vector2i position, FoodType type)
{
	Food* food = new Food();
	food->initialize(position, cell_width, cell_height, type);
	return food;
}

void FoodService::spawnFood()
{
	current_food_item = createFood(getValidSpawnPosition(), getRandomFoodType());
}

sf::Vector2i FoodService::getValidSpawnPosition()
{
	std::vector<sf::Vector2i> player_position_data = ServiceLocator::getInstance()->getPlayerService()->getCurrentPlayerPositionList();
	std::vector<sf::Vector2i> elements_position_data = ServiceLocator::getInstance()->getElementService()->getElementsPositionList();
	sf::Vector2i spawn_position;

	do spawn_position = getRandomPosition();
	while (!isValidPosition(player_position_data, elements_position_data, spawn_position));

	return spawn_position;
}

sf::Vector2i FoodService::getRandomPosition()
{
	// Co-ordinate distribution i.e. selecting random position for food.
	std::uniform_int_distribution<int> x_distribution(0, LevelModel::number_of_columns - 1);
	std::uniform_int_distribution<int> y_distribution(0, LevelModel::number_of_rows - 1);

	int x_position = static_cast<int>(x_distribution(random_engine));
	int y_position = static_cast<int>(y_distribution(random_engine));

	return sf::Vector2i(x_position, y_position);
}

FoodType FoodService::getRandomFoodType()
{
	std::uniform_int_distribution<int> distribution(0, Food::number_of_foods - 1);

	return static_cast<FoodType>(distribution(random_engine));
}

bool FoodService::isValidPosition(std::vector<sf::Vector2i> player_position_data, std::vector<sf::Vector2i> elements_position_data, sf::Vector2i food_position)
{
	for (int i = 0; i < player_position_data.size(); i++)
	{
		if (food_position == player_position_data[i]) return false;
	}

	for (int i = 0; i < elements_position_data.size(); i++)
	{
		if (food_position == elements_position_data[i]) return false;
	}

	return true;
}

void FoodService::destroyFood()
{
	if(current_food_item) delete(current_food_item);
}

void FoodService::updateElapsedDuration()
{
	elapsed_duration += ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
}

void FoodService::handleFoodSpawning()
{
	if (elapsed_duration >= spawn_duration)
	{
		destroyFood();
		reset();
		spawnFood();
	}
}

void FoodService::reset()
{
	elapsed_duration = 0.f;
}
