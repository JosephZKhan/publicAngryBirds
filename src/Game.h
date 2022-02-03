
#ifndef ANGRYBIRDS_GAME_H
#define ANGRYBIRDS_GAME_H

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Bird.h"
#include "Pig.h"

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void mouseReleased(sf::Event event);
  void keyPressed(sf::Event event, float dt);
  void addScore(int newPoints);
  void restart();
  void initLevel1();
  void initLevel2();
  void initLevel3();
  void initLevel4();



 private:
  sf::RenderWindow& window;
  sf::Color red = sf::Color(255, 0, 0, 255);



  int gameState = 0;

  GameObject background;
  GameObject marker;

  sf::Text titleText;
  sf::Text levelSelectText;
  sf::Text instructionsText;
  sf::Text quitText;
  sf::Text instructionScreenText;
  sf::Text scoreText;
  sf::Text gameOverText;
  sf::Text victoryScreenText;
  sf::Text levelSelectScreenText;
  sf::Text level1Text;
  sf::Text level2Text;
  sf::Text level3Text;
  sf::Text level4Text;

  sf::Font font;

  sf::Texture backgroundTexture;
  sf::Texture markerTexture;

  int introMenuIndex = 0;

  int levelSelectMenuIndex = 0;

  int levelIndex = 0;

  Bird birds[36]{};
  Pig pigs[36]{};
  int maxBirds = 35;
  int maxPigs = 35;
  int birdsInLevel = 5;
  int pigsInLevel = 2;
  int birdsAliveInLevel = birdsInLevel + 1;
  int pigsAliveInLevel = pigsInLevel + 1;
  int birdsListIndex = 0;

  float originPosX = 100;
  float originPosY = 528;

  int score = 0;

  bool playerRestart = false;

  bool theMouseIsClicked = false;


};

#endif // ANGRYBIRDS_GAME_H
