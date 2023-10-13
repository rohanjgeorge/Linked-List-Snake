#pragma once
#include <SFML/System/Vector2.hpp>
#include "../header/ElementService.h"
#include "../header/LevelConfig.h"
#include <vector>

class LevelModel
{
private:
    std::vector<ElementData> level_one_element_list = {};

    std::vector<ElementData> level_two_element_list = { ElementData(ElementType::OBSTACLE, sf::Vector2i(25, 15)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(26, 15)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(27, 15)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(28, 15)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(29, 15)) };

    std::vector<LevelData> level_data_list;
    
    float cell_width;
    float cell_height;

    void initializeLevelData();

public:
    static const int number_of_rows = 30;
    static const int number_of_columns = 50;

    LevelModel();
    ~LevelModel();

    void initialize(int width, int height);

    const std::vector<LevelData>& getLevelDataList();
    const std::vector<ElementData>& getElementDataList(int level_to_load);
    float getCellWidth();
    float getCellHeight();
};