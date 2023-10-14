#include "../header/LevelView.h"
#include "../header/ServiceLocator.h"
#include "../header/GraphicService.h"

LevelView::LevelView() = default;

LevelView::~LevelView() = default;

void LevelView::initialize()
{
	game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
    
    initializeBackground();
    calculateGridExtents();
    initializeBorder();
}

void LevelView::initializeBackground()
{
    backgroundRect.setSize(sf::Vector2f(game_window->getSize().x, game_window->getSize().y));
    backgroundRect.setFillColor(background_color);
}

void LevelView::initializeBorder()
{
    border_rect.setSize(sf::Vector2f(grid_width, grid_height));
    border_rect.setPosition(border_offset_left, border_offset_top);
    border_rect.setFillColor(sf::Color::Transparent);
    border_rect.setOutlineColor(border_color);
    border_rect.setOutlineThickness(border_thickness);
}

void LevelView::calculateGridExtents()
{
    grid_width = game_window->getSize().x - 2 * border_offset_left;
    grid_height = game_window->getSize().y - 2 * border_offset_top;
}

void LevelView::update() { }

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
    return grid_width;
}

float LevelView::getGridHeight()
{
    return grid_height;
}