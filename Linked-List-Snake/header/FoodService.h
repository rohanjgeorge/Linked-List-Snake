#pragma once
#include <SFML/System/Vector2.hpp>
#include <random>
#include <vector>

class Node;
class Food;
enum class FoodType;

enum FoodSpawningStatus
{
	ACTIVE,
	IN_ACTIVE,
};

class FoodService
{
private:
	const float spawn_duration = 5.f;
	const int minimum_player_size = 10;

	float elapsed_duration;

	FoodSpawningStatus current_spawning_status;
	Food* current_food_item;

	float cell_width;
	float cell_height;

	// To generate random values.
	std::default_random_engine random_engine;

	// To give random seed to generator.
	std::random_device random_device;

	Food* createFood(sf::Vector2i position, FoodType type);
	void spawnFood();

	sf::Vector2i getValidSpawnPosition();
	sf::Vector2i getRandomPosition();
	FoodType getRandomFoodType();

	bool isValidPosition(std::vector<sf::Vector2i> player_position_data, std::vector<sf::Vector2i> elements_position_data, sf::Vector2i food_position);

	void updateElapsedDuration();
	void handleFoodSpawning();
	void reset();

public:
	FoodService();
	~FoodService();

	void initialize();
	void update();
	void render();

	void startFoodSpawning(float width, float height);
	void stopFoodSpawning();

	void destroyFood();
	bool handleFoodCollision(Node* head_node, FoodType& out_food_type);
};