#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class GraphicService
{
private:
	const std::string game_window_title = "Outscal Presents - Snake";
	const int game_window_width = 1920;
	const int game_window_height = 1080;
	const sf::Color window_color = sf::Color(200, 200, 0, 255);

	sf::VideoMode video_mode;
	sf::RenderWindow* game_window;

	void configureVideoMode();

public:
	GraphicService();
	~GraphicService();

	void createGameWindow();
	void updateGraphics();
	void drawNextFrame();
	bool isGameWindowOpen();
	sf::RenderWindow* getWindow();
	void setFrameRate(int);
};
