#pragma once

enum class GameState
{
	BOOT,
	SPLASH_SCREEN,
	MAIN_MENU,
};

class GameService
{
private:
	static GameState current_state;

	void initialize();
	void destroy();

public:
	GameService();
	virtual ~GameService();

	void ignite();
	void update();
	void render();

	static void setGameState(GameState new_state);
	static GameState getGameState();
};