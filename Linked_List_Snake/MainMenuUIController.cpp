#include "MainMenuUIController.h"

#include "ServiceLocator.h"

MainMenuUIController::MainMenuUIController(sf::RenderWindow* window)
{
	this->game_window = window;
	setBackgroundImage();
    initializeButtons();
}

// Load the background texture and sprite
void MainMenuUIController::setBackgroundImage()
{
    if (background_texture.loadFromFile("textures/snake_bg.png")) {
        background_sprite.setTexture(background_texture);
        background_sprite.setScale(
            static_cast<float>(game_window->getSize().x) / background_sprite.getTexture()->getSize().x,
            static_cast<float>(game_window->getSize().y) / background_sprite.getTexture()->getSize().y
        );
    }
}

void MainMenuUIController::initializeButtons()
{
    if (loadButtonTexturesFromFile())
    {
        setButtonSprites();
        scaleButttons();
        positionButtons();
    }
}

bool MainMenuUIController::loadButtonTexturesFromFile()
{
    return play_button_texture.loadFromFile("textures/play_button.png") &&
        instructions_button_texture.loadFromFile("textures/instructions_button.png") &&
        quit_button_texture.loadFromFile("textures/quit_button.png");
}

void MainMenuUIController::setButtonSprites()
{
    play_button_sprite.setTexture(play_button_texture);
    instructions_button_sprite.setTexture(instructions_button_texture);
    quit_button_sprite.setTexture(quit_button_texture);
}

void MainMenuUIController::scaleButttons()
{
    play_button_sprite.setScale(
        button_width / play_button_sprite.getTexture()->getSize().x,
        button_height / play_button_sprite.getTexture()->getSize().y
    );
    instructions_button_sprite.setScale(
        button_width / instructions_button_sprite.getTexture()->getSize().x,
        button_height / instructions_button_sprite.getTexture()->getSize().y
    );
    quit_button_sprite.setScale(
        button_width / quit_button_sprite.getTexture()->getSize().x,
        button_height / quit_button_sprite.getTexture()->getSize().y
    );
}

void MainMenuUIController::positionButtons()
{
    float x_position = (static_cast<float>(game_window->getSize().x) / 2) - button_width / 2;

    play_button_sprite.setPosition({ x_position, 500.f });
    instructions_button_sprite.setPosition({ x_position, 700.f });
    quit_button_sprite.setPosition({ x_position, 900.f });
}

void MainMenuUIController::show()
{
	
}

void MainMenuUIController::update()
{
    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*game_window));

	game_window->clear();

    game_window->draw(background_sprite);
    game_window->draw(play_button_sprite);
    game_window->draw(instructions_button_sprite);
    game_window->draw(quit_button_sprite);

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		handleButtonInteractions(mouse_position);
}

// Check for button interactions
void MainMenuUIController::handleButtonInteractions(sf::Vector2f mouse_position)
{
    if (play_button_sprite.getGlobalBounds().contains(mouse_position)) {
        // Should actually be redirected to Level Selection Screen.
        ServiceLocator::getInstance()->getUIService()->setUIState(UIState::GAMEPLAY);
    }

    if (instructions_button_sprite.getGlobalBounds().contains(mouse_position)) {
        ServiceLocator::getInstance()->getUIService()->setUIState(UIState::INSTRUCTIONS);
    }

    if (quit_button_sprite.getGlobalBounds().contains(mouse_position)) {
        game_window->close();
    }
}