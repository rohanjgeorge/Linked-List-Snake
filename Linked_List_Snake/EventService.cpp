#include "EventService.h"
#include "ServiceLocator.h"

EventService::EventService() { game_window = nullptr; }

EventService::~EventService() = default;

void EventService::setGameWindow(sf::RenderWindow* window_to_set) { game_window = window_to_set; }

void EventService::processEvents()
{
	if (game_window != nullptr)
	{
		// Iterate over all events in the queue.
		while (game_window->pollEvent(game_event))
		{
			if (closedGameWindow() || quitGame())
				game_window->close();
		}
	}
}

bool EventService::closedGameWindow() { return game_event.type == sf::Event::Closed; }

bool EventService::quitGame() { return (isKeyEvent() && pressedEscapeKey()); }

bool EventService::isKeyEvent() { return game_event.type == sf::Event::KeyPressed; }

bool EventService::pressedEscapeKey() { return game_event.key.code == sf::Keyboard::Escape; }
