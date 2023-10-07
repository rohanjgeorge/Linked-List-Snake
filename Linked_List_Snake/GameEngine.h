#pragma once
#include "ServiceLocator.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Network.hpp>

class GameEngine
{
private:
	const int frame_rate = 60;
	ServiceLocator* service_locator;

	void initializeVariables();
	void initializeGameWindow();

public:
	GameEngine();
	virtual ~GameEngine();

	void ignite();
	void update();
	bool isRunning();
};
