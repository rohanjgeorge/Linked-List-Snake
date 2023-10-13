#pragma once
#include <SFML/System/Vector2.hpp>
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