#pragma once

class LevelModel;
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
};