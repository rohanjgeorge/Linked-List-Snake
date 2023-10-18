#pragma once

class LevelConfiguration;
class LevelController;

enum class Level
{
    ONE,
    TWO,
};

enum class LevelType
{
    SINGLE_LINKED_LIST,
    DOUBLE_LINKED_LIST,
};

class LevelService 
{
private:
    LevelController* level_controller;
    Level current_level;
    LevelType current_level_type;

    void createLevelController();
    void spawnPlayer();
    void spawnLevelElements(Level level_to_load);
    void spawnFood();
    void destroy();

public:
    LevelService();
    ~LevelService();

    void initialize();
    void update();
    void render();

    void createLevel(LevelType level_type);
    void setCurrentLevel(Level level_to_load);

    float getCellWidth();
    float getCellHeight();
    Level getCurrentLevel();
    LevelType getCurrentLevelType();
};