#include "../header/LevelModel.h"
#include "../header/LevelService.h"
#include "../header/ElementService.h"

LevelModel::LevelModel() = default;

LevelModel::~LevelModel() = default;

void LevelModel::initialize(int width, int height)
{
	cell_width = static_cast<float>(width) /static_cast<float>(number_of_columns);
	cell_height = static_cast<float>(height) /static_cast<float>(number_of_rows);

	initializeLevelData();
}

void LevelModel::initializeLevelData()
{
	level_configurations.push_back(LevelData(Level::ONE, &level_one_element_list));
	level_configurations.push_back(LevelData(Level::TWO, &level_two_element_list));
}

const std::vector<LevelData>& LevelModel::getLevelDataList()
{
	return level_configurations;
}

const std::vector<ElementData>& LevelModel::getElementDataList(int level_to_load)
{
	return *level_configurations[level_to_load].element_data_list;
}

float LevelModel::getCellWidth()
{
	return cell_width;
}

float LevelModel::getCellHeight()
{
	return cell_height;
}
