#include "Level/LevelModel.h"

namespace Level
{
	LevelModel::LevelModel() = default;

	LevelModel::~LevelModel() = default;

	void LevelModel::initialize(int width, int height)
	{
		cell_width = width / number_of_columns;
		cell_height = height / number_of_rows;
	}

	const std::vector<LevelData>& LevelModel::getLevelDataList()
	{
		return level_configurations;
	}

	float LevelModel::getCellWidth()
	{
		return cell_width;
	}

	float LevelModel::getCellHeight()
	{
		return cell_height;
	}
}
