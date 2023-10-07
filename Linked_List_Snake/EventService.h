#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class EventService
{
private:
	sf::Event game_event;
	sf::RenderWindow* game_window;

	bool closedGameWindow();
	bool quitGame();
	bool isKeyEvent();
	bool pressedEscapeKey();

public:
	EventService();
	~EventService();

	void setGameWindow(sf::RenderWindow* window_to_set);
	void processEvents();
};
