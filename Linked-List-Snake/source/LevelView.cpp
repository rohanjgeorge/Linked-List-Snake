#include "../header/LevelView.h"
#include "../header/ServiceLocator.h"

LevelView::LevelView()
{
}

LevelView::~LevelView()
{
}

void LevelView::initialize()
{
	game_window = ServiceLocator::getInstance()->getGameWindow();
    
    initializeBackground();
    calculateBorderExtents();
    initializeBorder();
}

void LevelView::initializeBackground()
{
    backgroundRect.setSize(sf::Vector2f(game_window->getSize().x, game_window->getSize().y));
    backgroundRect.setFillColor(background_color);
}

void LevelView::initializeBorder()
{
    border_rect.setSize(sf::Vector2f(border_width, border_height));
    border_rect.setPosition(border_offset_left, border_offset_top);
    border_rect.setFillColor(sf::Color::Transparent);
    border_rect.setOutlineColor(border_color);
    border_rect.setOutlineThickness(border_thickness);
}

void LevelView::calculateBorderExtents()
{
    border_width = game_window->getSize().x - 2 * border_offset_left;
    border_height = game_window->getSize().y - 2 * border_offset_top;
}

void LevelView::update()
{
}

void LevelView::render()
{
	drawLevel();
}

void LevelView::drawLevel()
{
    game_window->draw(backgroundRect);
    game_window->draw(border_rect);
}

float LevelView::getGridWidth()
{
    return border_width - border_thickness;
}

float LevelView::getGridHeight()
{
    return border_height - border_thickness;
}