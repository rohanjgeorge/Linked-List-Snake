#pragma once

class LevelConfiguration;
class LevelController;

enum class Level
{
    ONE,
    TWO,
};

class LevelService 
{
private:
    LevelController* level_controller;
    Level current_level;

    void createLevelController();
    void spawnPlayer();
    void spawnLevelElements(Level level_to_load);
    void destroy();

public:
    LevelService();
    ~LevelService();

    void initialize();
    void update();
    void render();

    void createLevel(Level level_to_load);
};