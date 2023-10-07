#include "SplashScreenUIController.h"
#include "ServiceLocator.h"

SplashScreenUIController::SplashScreenUIController(sf::RenderWindow* window)
{
    initializeVariables(window);
	initializeOutscalLogo();
}

void SplashScreenUIController::initializeVariables(sf::RenderWindow* window)
{
    this->game_window = window;
    elapsedTime = 0.0f;
}

void SplashScreenUIController::initializeOutscalLogo()
{
    loadOutscalTexture();
    outscal_logo.setTexture(outscal_logo_texture);
    setPositionToCenter();
}

void SplashScreenUIController::loadOutscalTexture()
{
    if (!outscal_logo_texture.loadFromFile("textures/outscal_logo.png")) {
        printf("ERROR :: UIService :: Unable to find Outscal Logo Texture");
    }
}

void SplashScreenUIController::setPositionToCenter()
{
    sf::Vector2u windowSize = game_window->getSize();
    sf::Vector2u logoSize = outscal_logo_texture.getSize();
    outscal_logo.setPosition((windowSize.x - logoSize.x) / 2.0f, (windowSize.y - logoSize.y) / 2.0f);
}

// Reset the clock to zero when showing the splash screen.
void SplashScreenUIController::show() {
	clock.restart();
	elapsedTime = 0.0f;
    float totalElapsedTime = 0.0f;

	while (totalElapsedTime < splash_screen_time) {
        float deltaTime = clock.restart().asSeconds();
        totalElapsedTime += deltaTime;
        update(deltaTime);
    }

    logoAnimationComplete();
}

void SplashScreenUIController::update(float deltaTime) {
    elapsedTime += deltaTime;
    float alpha = showLogo();
    if(elapsedTime > 4.0f) // Show for 4 seconds total:
		hideLogo(alpha);
    renderBrandLogo();
}

// Calculate the alpha value based on elapsed time (e.g., linear interpolation)
float SplashScreenUIController::showLogo()
{
    float alpha = std::min(1.0f, elapsedTime / logo_animation_time); // Gradually becomes visible over 2 seconds
    outscal_logo.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha * 255)));
    return alpha;
}

// Once the logo is fully visible, start fading out after 2 seconds.
void SplashScreenUIController::hideLogo(float alpha)
{
    alpha = std::max(0.0f, 1.0f - ((elapsedTime - 4.0f) / logo_animation_time));
    outscal_logo.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha * 255)));
}

// Draw the brand logo sprite on the window
void SplashScreenUIController::renderBrandLogo()
{
    game_window->clear();
    game_window->draw(outscal_logo);
    game_window->display();
}

void SplashScreenUIController::logoAnimationComplete() { ServiceLocator::getInstance()->getUIService()->setUIState(UIState::MAIN_MENU); }
