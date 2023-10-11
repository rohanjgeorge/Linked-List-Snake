#pragma once
#include "ElementService.h"
#include <SFML/System/Vector2.hpp>
#include "LevelService.h"
#include <vector>

struct ElementData
{
    ElementType element_type;
    sf::Vector2i position;
};

struct LevelData
{
    Level level_index;
    std::vector<ElementData> element_data_list;
};

class LevelModel
{
private:
    static const int number_of_rows = 70;
    static const int number_of_columns = 80;

    std::vector<ElementData> level_one_data_list = {{ElementType::OBSTACLE, sf::Vector2i{5, 5}},
                                                    {ElementType::OBSTACLE, sf::Vector2i{5, 5}},
                                                    {ElementType::OBSTACLE, sf::Vector2i{5, 5}}};

    std::vector<ElementData> level_two_data_list = {{ElementType::OBSTACLE, sf::Vector2i{5, 5}},
                                                    {ElementType::OBSTACLE, sf::Vector2i{5, 5}},
                                                    {ElementType::OBSTACLE, sf::Vector2i{5, 5}},
                                                    {ElementType::OBSTACLE, sf::Vector2i{5, 5}},
                                                    {ElementType::OBSTACLE, sf::Vector2i{5, 5}}};

    std::vector<LevelData> level_data_list;
    
    float grid_cell_width;
    float grid_cell_height;

    void initializeLevelData();

public:
    LevelModel();
    ~LevelModel();

    void initialize(int grid_width, int grid_height);

    std::vector<LevelData> getLevelDataList();
};