#include "../header/GameplayUIController.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/SoundService.h"
#include "../header/EventService.h"
#include "../header/TextView.h"
#include "../header/Config.h"
#include "../header/LevelService.h"
#include "../header/PlayerService.h"
#include "../header/PlayerController.h"

GameplayUIController::GameplayUIController()
{
    createTexts();
}

GameplayUIController::~GameplayUIController()
{
    destroy();
}

void GameplayUIController::initialize()
{
    initializeTexts();
}

void GameplayUIController::createTexts()
{
    level_number_text = new TextView();
    score_text = new TextView();
    time_complexity_text = new TextView();
}

void GameplayUIController::initializeTexts()
{
    initializeLevelNumberText();
    initializeScoreText();
    initializeTimeComplexityText();
}

void GameplayUIController::initializeLevelNumberText()
{
    level_number_text->initialize("Level : 1", sf::Vector2f(level_number_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::Black);
}

void GameplayUIController::initializeScoreText()
{
    score_text->initialize("Score : 0", sf::Vector2f(score_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::Black);
}

void GameplayUIController::initializeTimeComplexityText()
{
    time_complexity_text->initialize("Time Complexity : O(1)", sf::Vector2f(time_complexity_text_x_position, text_y_position), FontType::BUBBLE_BOBBLE, font_size, sf::Color::Black);
}

void GameplayUIController::update()
{
    updateLevelNumberText();
    updateScoreText();
    updateTimeComplexityText();
}

void GameplayUIController::render()
{
    level_number_text->render();
    score_text->render();
    time_complexity_text->render();
}

void GameplayUIController::show()
{
    level_number_text->show();
    score_text->show();
    time_complexity_text->show();
}

void GameplayUIController::updateLevelNumberText()
{
    Level level = ServiceLocator::getInstance()->getLevelService()->getCurrentLevel();
    sf::String level_number_value = std::to_string(1 + static_cast<int>(level));

    level_number_text->setText("Level : " + level_number_value);
    level_number_text->update();
}

void GameplayUIController::updateScoreText()
{
    int player_score = ServiceLocator::getInstance()->getPlayerService()->getPlayerScore();
    sf::String score_value = std::to_string(player_score);

    score_text->setText("Score : " + score_value);
    score_text->update();
}

void GameplayUIController::updateTimeComplexityText()
{
    TimeComplexity time_complexity = ServiceLocator::getInstance()->getPlayerService()->getTimeComplexity();
    sf::String time_complexity_value;

    switch (time_complexity)
    {
    case TimeComplexity::ONE:
        time_complexity_value = "1";
        break;
    case TimeComplexity::N:
        time_complexity_value = "N";
        break;
    }

    time_complexity_text->setText("Time Complexity : (" + time_complexity_value + ")");
    time_complexity_text->update();
}

void GameplayUIController::destroy()
{
    delete (level_number_text);
    delete (score_text);
    delete (time_complexity_text);
}
