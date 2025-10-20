#pragma once
#include <SFML/Graphics.hpp>


//Taken from https://old.reddit.com/r/gamedev/comments/1bgbv9r/programming_screen_shake_is_easy/, Created by UpbeatGalaxy, Created on March 16 2024 (Accessed: 19/10/25)
//anything NOT taken from the link in this class is my work
class ScreenShaker
{
public:
	ScreenShaker();
	~ScreenShaker();
	void shakeScreen(float time, int intensity);
	void update(float dt);
	bool isShaking();
	void setShaking(bool);
	void setShakeIntensity(int);
	int getShakeIntensity();


	void setShakeDuration(int);
	int getShakeDuration();


	sf::Vector2i getScreenPosition();

private:
	bool shaking = false;
	int shakeIntensity = 0;
	float shakeDuration = 0;
	float currentTime = 0;
	sf::Vector2i screenPosition = sf::Vector2i(0, 0);
	int shakerSwitch = 1;


protected:

};

