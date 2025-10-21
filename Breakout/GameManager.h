#pragma once
#include <SFML/Graphics.hpp>
#include "CONSTANTS.h"
#include "Paddle.h"
#include "Ball.h"
#include "BrickManager.h"
#include "PowerupManager.h"
#include "MessagingSystem.h"
#include "UI.h"
#include "ScreenShaker.h"



class GameManager {
public:
    GameManager(sf::RenderWindow* window);
    void initialize();
    void update(float dt);
    void loseLife();
    void render();
    void levelComplete();
    void powerupEffect(POWERUPS pu, float t);

    //comparing for sorting the vector to descending order
    static bool comp(int a, int b);

    Paddle* getPaddle() const;
    BrickManager* getBrickManager() const;
    PowerupManager* getPowerupManager() const;
    sf::RenderWindow* getWindow() const;
    UI* getUI() const;

    void addScore(int);
    void updateScoreText();
    int getScore();


private:
    bool _pause;
    float _pauseHold;
    float _time;
    float _timeLastPowerupSpawned;
    int _lives;
    bool _levelComplete;
    bool gameFinished = false;
    int score = 0;
    std::pair<POWERUPS, float> _powerupInEffect;

    sf::Font _font;
    sf::Text _masterText;
    sf::Text scoreText;
    sf::Text leaderboardText;

    std::vector<sf::Text> leaderboardScores;
    std::vector<int> storedScores;

 /*   struct leaderboardInfo {
        int score;
        std::string name;
    };*/

  /*  std::vector<leaderboardInfo> leaderboardScores;*/

    sf::RectangleShape leaderboardBox;

    sf::RenderWindow* _window;
    Paddle* _paddle;
    Ball* _ball;
    BrickManager* _brickManager;
    PowerupManager* _powerupManager;
    MessagingSystem* _messagingSystem;
    UI* _ui;
    ScreenShaker* screenShaker;

    static constexpr float PAUSE_TIME_BUFFER = 0.5f;
    static constexpr float POWERUP_FREQUENCY = 7.5f;    // time between minimum powerup spawn
};
