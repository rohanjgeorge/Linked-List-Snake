#include "../header/GraphicService.h"
#include "../header/ImageView.h"
#include "../header/TextView.h"
#include "../header/Config.h"

GraphicService::GraphicService()
{
	game_window = nullptr;
}

GraphicService::~GraphicService()
{
	onDestroy();
}

void GraphicService::initialize()
{
	game_window = createGameWindow();
	setFrameRate(frame_rate);

	initializeBackgroundImage();
	TextView::initializeTextView();
}

sf::RenderWindow* GraphicService::createGameWindow()
{
	configureVideoMode();
	return new sf::RenderWindow(video_mode, game_window_title, sf::Style::Fullscreen);
}

void GraphicService::configureVideoMode()
{
	video_mode = *(new sf::VideoMode(game_window_width, game_window_height, sf::VideoMode::getDesktopMode().bitsPerPixel));
}

void GraphicService::onDestroy()
{
	delete(game_window);
	delete(background_image);
}

void GraphicService::setFrameRate(int frame_rate_to_set)
{
	game_window->setFramerateLimit(frame_rate_to_set);
}

void GraphicService::update() 
{
	background_image->update();
}

void GraphicService::render() { }

bool GraphicService::isGameWindowOpen()
{
	return game_window->isOpen();
}

sf::RenderWindow* GraphicService::getGameWindow()
{
	return game_window;
}

void GraphicService::initializeBackgroundImage()
{
	background_image = new ImageView();

	background_image->initialize(Config::background_texture_path, game_window_width, game_window_height, sf::Vector2f(0,0));
	background_image->setImageAlpha(background_alpha);
}

void GraphicService::drawBackground()
{
	background_image->render();
}