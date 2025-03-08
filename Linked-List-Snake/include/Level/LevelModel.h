#pragma once
#include <SFML/System/Vector2.hpp>
#include "Level/LevelData.h"
#include <vector>

namespace Level
{
    class LevelModel
    {
    private:
       

        std::vector<LevelData> level_configurations;

        float cell_width;
        float cell_height;

        //void initializeLevelData();

    public:
        static const int number_of_rows = 20;
        static const int number_of_columns = 20;

        LevelModel();
        ~LevelModel();

        void initialize(int width, int height);

        //const std::vector<Element::ElementData>& getElementDataList(int level_to_load);
        float getCellWidth();
        float getCellHeight();
    };
}