#include "GraphicService.h"

GraphicService::GraphicService() { game_window = nullptr; }

GraphicService::~GraphicService() { delete(game_window); }

void GraphicService::createGameWindow()
{
	configureVideoMode();
	game_window = new sf::RenderWindow(video_mode, game_window_title, sf::Style::Fullscreen);
}

void GraphicService::configureVideoMode()
{
	video_mode = *(new sf::VideoMode(game_window_width, game_window_height, sf::VideoMode::getDesktopMode().bitsPerPixel));
}

void GraphicService::setFrameRate(int frame_rate_to_set) { game_window->setFramerateLimit(frame_rate_to_set); }

void GraphicService::updateGraphics() { }

void GraphicService::drawNextFrame()
{
	// Clear previous frame,
	// game_window->clear(window_color);		// This is probably not supposed to be here. The color of the window must be set by the respective UI Screen.

	// Draw current frame.
	game_window->display();
}

bool GraphicService::isGameWindowOpen() { return game_window->isOpen(); }

sf::RenderWindow* GraphicService::getWindow() { return game_window; }
