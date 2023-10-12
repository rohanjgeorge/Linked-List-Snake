#pragma once
#include <vector>
#include "LevelModel.h"

class LevelView;

class LevelController
{
private:
    LevelModel* level_model;
    LevelView* level_view;

public:
    LevelController();
    ~LevelController();

    void initialize();
    void update();
    void render();

    LevelModel* getLevelModel();
    LevelView* getLevelView();
    const std::vector<ElementData>& getElementDataList(int level_index);
};