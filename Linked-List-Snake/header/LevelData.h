#pragma once
#include <vector>

enum class Level;
struct ElementData;

struct LevelData
{
    LevelData(Level ind, std::vector<ElementData>* data_list)
    {
        level_index = ind;
        element_data_list = data_list;
    }

    Level level_index;
    std::vector<ElementData>* element_data_list;
};