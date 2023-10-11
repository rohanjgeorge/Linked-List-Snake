#include "../header/LevelModel.h"

LevelModel::LevelModel()
{
}

LevelModel::~LevelModel()
{
}

void LevelModel::initialize(int grid_width, int grid_height)
{
	grid_cell_width = grid_width/number_of_columns;
	grid_cell_height = grid_height/number_of_rows;

	initializeLevelData();
}

void LevelModel::initializeLevelData()
{
	level_data_list.push_back({ Level::ONE, level_one_data_list });
	level_data_list.push_back({ Level::TWO, level_two_data_list });
}

std::vector<LevelData> LevelModel::getLevelDataList()
{
	return level_data_list;
}