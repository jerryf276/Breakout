#include "GameManager.h"
#include "Ball.h"
#include "PowerupManager.h"
#include <iostream>

GameManager::GameManager(sf::RenderWindow* window)
    : _window(window), _paddle(nullptr), _ball(nullptr), _brickManager(nullptr), _powerupManager(nullptr),
    _messagingSystem(nullptr), _ui(nullptr), _pause(false), _time(0.f), _lives(3), _pauseHold(0.f), _levelComplete(false),
    _powerupInEffect({ none,0.f }), _timeLastPowerupSpawned(0.f)
{
    _font.loadFromFile("font/montS.ttf");
    _masterText.setFont(_font);
    _masterText.setPosition(50, 400);
    _masterText.setCharacterSize(48);
    _masterText.setFillColor(sf::Color::Yellow);
}

void GameManager::initialize()
{
    _paddle = new Paddle(_window);
    _brickManager = new BrickManager(_window, this);
    _messagingSystem = new MessagingSystem(_window);
    _ball = new Ball(_window, 400.0f, this); 
    _powerupManager = new PowerupManager(_window, _paddle, _ball);
    _ui = new UI(_window, _lives, this); \
    screenShaker = new ScreenShaker();


    // Create bricks
    _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
}

void GameManager::update(float dt)
{
    _powerupInEffect = _powerupManager->getPowerupInEffect();
    _ui->updatePowerupText(_powerupInEffect);
    _powerupInEffect.second -= dt;
    
    screenShaker->update(dt);
    _window->setPosition(screenShaker->getScreenPosition());

    if (_lives <= 0)
    {
        _masterText.setString("Game over. Press R to retry.");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            delete _ball;
            delete _brickManager;
            delete _powerupManager;
            _ball = new Ball(_window, 400.0f, this);
            _brickManager = new BrickManager(_window, this);
            _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
            _powerupManager = new PowerupManager(_window, _paddle, _ball);

            _lives = 3;
            _ui->addLivesBack();
            _masterText.setString("");
        }
        return;
    }
    if (_levelComplete)
    {
        _masterText.setString("Level completed. Press R to play again.");
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            delete _ball;
            delete _brickManager;
            delete _powerupManager;
            _ball = new Ball(_window, 400.0f, this);
            _brickManager = new BrickManager(_window, this);
            _brickManager->createBricks(5, 10, 80.0f, 30.0f, 5.0f);
            _powerupManager = new PowerupManager(_window, _paddle, _ball);

            _lives = 3;
            _ui->addLivesBack();
            _masterText.setString("");
            _levelComplete = false;
        }
        return;
    }
    // pause and pause handling
    if (_pauseHold > 0.f) _pauseHold -= dt;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        //Escape might be more decent for pausing a game (easier to reach)
    {
        if (!_pause && _pauseHold <= 0.f)
        {
            _pause = true;
            _masterText.setString("paused.");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
        if (_pause && _pauseHold <= 0.f)
        {
            _pause = false;
            _masterText.setString("");
            _pauseHold = PAUSE_TIME_BUFFER;
        }
    }
    if (_pause)
    {
        return;
    }

    // timer.
    _time += dt;


    if (_time > _timeLastPowerupSpawned + POWERUP_FREQUENCY && rand()%700 == 0)      // TODO parameterise
    {
        _powerupManager->spawnPowerup();
        _timeLastPowerupSpawned = _time;
    }

    // move paddle
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) _paddle->moveRight(dt);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) _paddle->moveLeft(dt);

    // update everything 
    _paddle->update(dt);
    _ball->update(dt);
    _powerupManager->update(dt);
}

void GameManager::loseLife()
{
    _lives--;
    _ui->lifeLost(_lives);

    //Shaking the screen when the player loses a life
    screenShaker->shakeScreen(1, 1);
}

void GameManager::render()
{
    _paddle->render();
    _ball->render();
    _brickManager->render();
    _powerupManager->render();
    _window->draw(_masterText);
    _ui->render();
}

void GameManager::levelComplete()
{
    _levelComplete = true;
}

sf::RenderWindow* GameManager::getWindow() const { return _window; }
UI* GameManager::getUI() const { return _ui; }
Paddle* GameManager::getPaddle() const { return _paddle; }
BrickManager* GameManager::getBrickManager() const { return _brickManager; }
PowerupManager* GameManager::getPowerupManager() const { return _powerupManager; }
