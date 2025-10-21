#include <sstream>

#include "UI.h"
#include "GameManager.h"
#include <iomanip>

UI::UI(sf::RenderWindow* window, int lives, GameManager* gameManager) 
	: _window(window), _gameManager(gameManager)
{
	for (int i = lives; i > 0; --i)
	{
		sf::CircleShape newLife;
		newLife.setFillColor(sf::Color::Red);	
		newLife.setOutlineColor(sf::Color::Cyan);
		newLife.setOutlineThickness(4.0f);
		newLife.setRadius(LIFE_RADIUS);
		newLife.setPosition((LIFE_RADIUS*2 + LIFE_PADDING) * i, LIFE_PADDING);
		_lives.push_back(newLife);
	}
	_powerupText.setCharacterSize(30);
	_powerupText.setPosition(665, 20);
	_powerupText.setFillColor(sf::Color::Cyan);
	_font.loadFromFile("font/montS.ttf");
	_powerupText.setFont(_font);


	timeLeftBar.setSize(sf::Vector2f(0, 30));
	timeLeftBar.setPosition(750, 25);
	timeLeftBar.setFillColor(sf::Color::Green);

	timeElapsedBar.setSize(sf::Vector2f(200, 30));
	timeElapsedBar.setPosition(750, 25);
	timeElapsedBar.setFillColor(sf::Color::White);

}

UI::~UI()
{
}


void UI::updatePowerupText(std::pair<POWERUPS, float> powerup)
{
	std::ostringstream oss;

	switch (powerup.first)
	{
	case bigPaddle:
		powerupActivated = true;
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("big ");
		_powerupText.setFillColor(paddleEffectsColour);
		timeLeftBar.setFillColor(paddleEffectsColour);
		//we have hard coded the maximum time as 5.0f since the the power up effects all last 5 seconds. we could make a maximum time variable if we were to implement different times
		timeLeftBar.setSize(sf::Vector2f(barSize * (powerup.second / 5.0f), timeLeftBar.getSize().y));
		break;
	case smallPaddle:
		powerupActivated = true;
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("small ");
		_powerupText.setFillColor(paddleEffectsColour);
		timeLeftBar.setFillColor(paddleEffectsColour);
		timeLeftBar.setSize(sf::Vector2f(barSize * (powerup.second / 5.0f), timeLeftBar.getSize().y));
		break;
	case slowBall:
		powerupActivated = true;
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("slow ");
		_powerupText.setFillColor(ballEffectsColour);
		timeLeftBar.setFillColor(ballEffectsColour);
		timeLeftBar.setSize(sf::Vector2f(barSize * (powerup.second / 5.0f), timeLeftBar.getSize().y));
		break;
	case fastBall:
		powerupActivated = true;
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fast ");
		_powerupText.setFillColor(ballEffectsColour);
		timeLeftBar.setFillColor(ballEffectsColour);
		timeLeftBar.setSize(sf::Vector2f(barSize * (powerup.second / 5.0f), timeLeftBar.getSize().y));
		break;
	case fireBall:
		powerupActivated = true;
		oss << std::fixed << std::setprecision(2) << powerup.second;
		_powerupText.setString("fire ");
		_powerupText.setFillColor(extraBallEffectsColour);
		timeLeftBar.setFillColor(extraBallEffectsColour);
		timeLeftBar.setSize(sf::Vector2f(barSize * (powerup.second / 5.0f), timeLeftBar.getSize().y));
		break;
	case none:
		powerupActivated = false;
		_powerupText.setString("");
		
		break;
	}
}

void UI::lifeLost(int lives)
{
	_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Transparent);
}

void UI::addLivesBack()
{
	//_lives[_lives.size() - 1 - lives].setFillColor(sf::Color::Red);
	for (int i = 0; i < _lives.size(); i++) {
		_lives[i].setFillColor(sf::Color::Red);
	}
}

void UI::render()
{
	if (powerupActivated == true) {
		_window->draw(timeElapsedBar);
		_window->draw(timeLeftBar);
	}
	_window->draw(_powerupText);
	for (sf::CircleShape life : _lives)
	{
		_window->draw(life);
	}
}