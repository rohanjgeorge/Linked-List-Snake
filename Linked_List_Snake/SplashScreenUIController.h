#pragma once
#include <SFML/Graphics.hpp>

class SplashScreenUIController
{
private:
	sf::RenderWindow* game_window;
	sf::Texture outscal_logo_texture;
	sf::Sprite outscal_logo;
	sf::Clock clock;
	float elapsedTime;
	const float logo_animation_time = 2.0f;
	const float splash_screen_time = 6.0f;

	void initializeVariables(sf::RenderWindow* window);
	void initializeOutscalLogo();
	void loadOutscalTexture();
	void setPositionToCenter();
	float showLogo();
	void hideLogo(float alpha);
	void renderBrandLogo();
	void logoAnimationComplete();

public:
	SplashScreenUIController(sf::RenderWindow* window);

	void show();
	void update(float deltaTime);
};

