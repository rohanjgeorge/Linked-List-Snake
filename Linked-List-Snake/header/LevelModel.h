#pragma once
#include <SFML/System/Vector2.hpp>
#include "../header/ElementService.h"
#include <vector>

enum class Level;
enum class ElementType;

struct ElementData
{
public:
    ElementData(ElementType type, sf::Vector2i pos)
    {
        element_type = type;
        position = pos;
    }

    ElementType element_type;
    sf::Vector2i position;
};

struct LevelData
{
public:
    LevelData(Level ind, std::vector<ElementData>* data_list)
    {
        level_index = ind;
        element_data_list = data_list;
    }

    Level level_index;
    std::vector<ElementData>* element_data_list;
};

class LevelModel
{
private:
    std::vector<ElementData> level_one_data_list = {ElementData(ElementType::OBSTACLE, sf::Vector2i(25, 15)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(26, 15)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(27, 15)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(28, 15)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(29, 15))};

    std::vector<ElementData> level_two_data_list = { ElementData(ElementType::OBSTACLE, sf::Vector2i(5, 5)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(5, 7)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(9, 5)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(25, 9)),
                                                    ElementData(ElementType::OBSTACLE, sf::Vector2i(37, 14)) };

    std::vector<LevelData> level_data_list;
    
    float grid_cell_width;
    float grid_cell_height;

    void initializeLevelData();

public:
    static const int number_of_rows = 30;
    static const int number_of_columns = 50;

    LevelModel();
    ~LevelModel();

    void initialize(int grid_width, int grid_height);

    const std::vector<LevelData>& getLevelDataList();
    const std::vector<ElementData>& getElementDataList(int index);
    float getGridCellWidth();
    float getGridCellHeight();
};