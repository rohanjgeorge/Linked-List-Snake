#pragma once
#include <unordered_map>

class LevelModel;

enum class Level
{
    ONE,
    TWO,
};

class LevelService 
{
private:
    std::unordered_map<Level, LevelModel> level_map;

public:
    LevelService();
    ~LevelService();
};