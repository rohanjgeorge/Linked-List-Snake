#include "../header/LevelSelectionUIController.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/SoundService.h"
#include "../header/EventService.h"
#include "../header/LevelService.h"

LevelSelectionUIController::LevelSelectionUIController() { game_window = nullptr; }

void LevelSelectionUIController::initialize()
{
    game_window = ServiceLocator::getInstance()->getGameWindow();
    initializeButtons();
}

void LevelSelectionUIController::initializeButtons()
{
    if (loadButtonTexturesFromFile())
    {
        setButtonSprites();
        scaleAllButttons();
        positionButtons();
    }
}

bool LevelSelectionUIController::loadButtonTexturesFromFile()
{
    return level_one_button_texture.loadFromFile("assets/textures/level_one_button.png") &&
        level_two_button_texture.loadFromFile("assets/textures/level_two_button.png");
}

void LevelSelectionUIController::setButtonSprites()
{
    level_one_button_sprite.setTexture(level_one_button_texture);
    level_two_button_sprite.setTexture(level_two_button_texture);
}

void LevelSelectionUIController::scaleAllButttons()
{
    scaleButton(&level_one_button_sprite);
    scaleButton(&level_two_button_sprite);
}

void LevelSelectionUIController::scaleButton(sf::Sprite* button_to_scale)
{
    button_to_scale->setScale(
        button_width / button_to_scale->getTexture()->getSize().x,
        button_height / button_to_scale->getTexture()->getSize().y
    );
}

void LevelSelectionUIController::positionButtons()
{
    float x_position = calculateLeftOffsetForButton();

    level_one_button_sprite.setPosition({ x_position, 500.f });
    level_two_button_sprite.setPosition({ x_position, 700.f });
}

float LevelSelectionUIController::calculateLeftOffsetForButton()
{
    return (static_cast<float>(game_window->getSize().x) / 2) - button_width / 2;
}

void LevelSelectionUIController::update()
{
    handleButtonInteractions();
}

void LevelSelectionUIController::render()
{
    ServiceLocator::getInstance()->getGraphicService()->drawBackground();
    game_window->draw(level_one_button_sprite);
    game_window->draw(level_two_button_sprite);
}

void LevelSelectionUIController::show() { }

void LevelSelectionUIController::handleButtonInteractions()
{
    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*game_window));

    if (clickedButton(&level_one_button_sprite, mouse_position))
    {
        GameService::setGameState(GameState::GAMEPLAY);
        ServiceLocator::getInstance()->getLevelService()->createLevel(Level::ONE);
        ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
    }

    if (clickedButton(&level_two_button_sprite, mouse_position))
    {
        GameService::setGameState(GameState::GAMEPLAY);
        ServiceLocator::getInstance()->getLevelService()->createLevel(Level::TWO);
        ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
    }
}

bool LevelSelectionUIController::clickedButton(sf::Sprite* button_sprite, sf::Vector2f mouse_position)
{
    return ServiceLocator::getInstance()->getEventService()->pressedLeftMouseButton() &&
        button_sprite->getGlobalBounds().contains(mouse_position);
}