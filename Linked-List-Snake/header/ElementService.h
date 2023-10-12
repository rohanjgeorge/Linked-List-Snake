#pragma once
#include <vector>

class Obstacle;
struct ElementData;

enum class ElementType
{
	OBSTACLE,
};

class ElementService
{
private:
	std::vector<Obstacle*> obstacle_list;

	const void spawnObstacle(std::vector<ElementData>& element_data_list, int index, float cell_width, float cell_height);

public:
	ElementService();
	~ElementService();

	void initialize();
	void update();
	void render();

	const void spawnElements(std::vector<ElementData>& element_data_list, float cell_width, float cell_height);
};