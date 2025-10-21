#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

#include "CONSTANTS.h"
#include "PowerupManager.h"

class GameManager;

class UI
{
public:
	UI(sf::RenderWindow* window, int lives, GameManager* gameManager);
	~UI();

	void updatePowerupText(std::pair<POWERUPS, float>);
	void lifeLost(int lives);

	//readding lives once the player restarts the game
	void addLivesBack();
	void render();

private:
	GameManager* _gameManager;
	
	sf::RenderWindow* _window;
	sf::Font _font;
	sf::Text _powerupText;

	 
	sf::RectangleShape timeLeftBar;
	sf::RectangleShape timeElapsedBar;

	std::vector<sf::CircleShape> _lives;

	static constexpr float LIFE_RADIUS = 15.0f;
	static constexpr float LIFE_PADDING = 20.0f;

	int barSize = 200;
	bool powerupActivated = false;
};

