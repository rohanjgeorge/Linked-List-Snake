#pragma once
#include <SFML/Graphics.hpp>

class ImageView;

class GraphicService
{
private:
	const int frame_rate = 60;

	const std::string game_window_title = "Outscal Presents - Snake Game";

	const int game_window_width = 1920;
	const int game_window_height = 1080;

	const sf::Color window_color = sf::Color(200, 200, 0, 255);

	const float background_alpha = 85.f;

	sf::VideoMode video_mode;
	sf::RenderWindow* game_window;

	ImageView* background_image;

	void configureVideoMode();
	void onDestroy();

	void initializeBackgroundImage();

public:
	GraphicService();
	~GraphicService();

	sf::RenderWindow* createGameWindow();

	void initialize();
	void update();
	void render();
	bool isGameWindowOpen();
	void setFrameRate(int);
	sf::RenderWindow* getGameWindow();

	void drawBackground();
};