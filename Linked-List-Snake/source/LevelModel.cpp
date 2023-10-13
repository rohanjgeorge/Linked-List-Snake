#include "../header/LevelModel.h"
#include "../header/LevelService.h"
#include "../header/ElementService.h"

LevelModel::LevelModel()
{
}

LevelModel::~LevelModel()
{
}

void LevelModel::initialize(int grid_width, int grid_height)
{
	grid_cell_width = static_cast<float>(grid_width) /static_cast<float>(number_of_columns);
	grid_cell_height = static_cast<float>(grid_height) /static_cast<float>(number_of_rows);

	initializeLevelData();
}

void LevelModel::initializeLevelData()
{
	level_data_list.push_back(LevelData(Level::ONE, &level_one_data_list));
	level_data_list.push_back(LevelData(Level::TWO, &level_two_data_list));
}

const std::vector<LevelData>& LevelModel::getLevelDataList()
{
	return level_data_list;
}

const std::vector<ElementData>& LevelModel::getElementDataList(int index)
{
	return *level_data_list[index].element_data_list;
}

float LevelModel::getGridCellWidth()
{
	return grid_cell_width;
}

float LevelModel::getGridCellHeight()
{
	return grid_cell_height;
}
