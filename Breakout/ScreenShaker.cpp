#include "ScreenShaker.h"

ScreenShaker::ScreenShaker()
{

}

ScreenShaker::~ScreenShaker()
{

}

void ScreenShaker::shakeScreen(float time, int intensity)
{
	shakeDuration = time;
	shakeIntensity = intensity;
	shaking = true;
	shakerSwitch = 1;
}

void ScreenShaker::update(float dt)
{
	if (!shaking) {
		return;
	}

	if (currentTime > shakeDuration) {
		shaking = false;
		currentTime = 0;
		shakeIntensity = 0;
		screenPosition = sf::Vector2i(0, 0);
	}

	int shakeX = shakerSwitch * shakeIntensity;
	int shakeY = shakerSwitch * shakeIntensity;

	screenPosition.x += shakeX;
	screenPosition.y += shakeY;

	if (screenPosition.x != 0 && screenPosition.y != 0) {
		shakerSwitch *= -1;
	}

	currentTime += dt;

}

bool ScreenShaker::isShaking()
{
	return shaking;
}

void ScreenShaker::setShaking(bool shake)
{
	shaking = shake;
}

void ScreenShaker::setShakeIntensity(int intensity)
{
	shakeIntensity = intensity;
}

int ScreenShaker::getShakeIntensity()
{
	return shakeIntensity;
}

void ScreenShaker::setShakeDuration(int duration)
{
	shakeDuration = duration;
}

int ScreenShaker::getShakeDuration()
{
	return shakeDuration;
}

sf::Vector2i ScreenShaker::getScreenPosition()
{
	return screenPosition;
}
