//
// Created by Joseph Khan on 15/04/2021.
//

#ifndef ANGRYBIRDSSFML_BIRD_H
#define ANGRYBIRDSSFML_BIRD_H
#include "GameObject.h"
#include "Suvat.h"
#include <SFML/Graphics.hpp>

class Bird : public GameObject
{
 public:
  Bird();
  ~Bird();

  int getBirdType();
  void setBirdType(int newBirdType);

  void moveBird();

  bool getIsMoving();
  void setBirdMoving(bool newBool);

  void changeAim(float multX, float multY);

  sf::Texture redBirdTexture;
  sf::Texture yellowBirdTexture;
  sf::Texture blueBirdTexture;

  std::string birdImageNames[3]{"/Users/josephkhan/Desktop/games_in_cpp/angry-birds-2020-JosephZKhan/Data/Images/redBird.png", "/Users/josephkhan/Desktop/games_in_cpp/angry-birds-2020-JosephZKhan/Data/Images/yellowBird.png", "/Users/josephkhan/Desktop/games_in_cpp/angry-birds-2020-JosephZKhan/Data/Images/blueBird.png"};


  Suvat horizontal{25, 0};
  Suvat vertical{50, -0.6};

  Suvat horizontal1 = horizontal;
  Suvat vertical1 = vertical;

  bool isShootingForward = false;
  bool isShootingDown = false;
  bool canShootForward = true;
  bool drawMarker = false;

  float savedYPos;



  //BIRD TYPE GUIDE
  //0 = RED
  //1 = YELLOW

 private:
  int birdType;
  bool isMoving = false;
};

#endif // ANGRYBIRDSSFML_BIRD_H
