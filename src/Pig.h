//
// Created by Joseph Khan on 16/04/2021.
//

#ifndef ANGRYBIRDSSFML_PIG_H
#define ANGRYBIRDSSFML_PIG_H
#include "GameObject.h"
#include <iostream>
#include "SFML/Graphics.hpp"

class Pig : public GameObject
{
 public:
  Pig();
  //Pig(int pigTypeStruct,  int newPigHealth);
  ~Pig();

  int getPigType();
  void setPigType(int newPigType);
  int getPigHealth();
  void setPigHealth(int newPigHealth);
  void depletePigHealth();

  sf::Texture normalPigTexture;
  sf::Texture fancyPigHealthyTexture;
  sf::Texture fancyPigDamagedTexture;
  sf::Texture fancyPigVeryInjuredTexture;
  std::string pigImageList[4]{"/Users/josephkhan/Desktop/games_in_cpp/angry-birds-2020-JosephZKhan/Data/Images/normalPig.png",
                               "/Users/josephkhan/Desktop/games_in_cpp/angry-birds-2020-JosephZKhan/Data/Images/fancyPigHealthy.png",
                               "/Users/josephkhan/Desktop/games_in_cpp/angry-birds-2020-JosephZKhan/Data/Images/fancyPigDamaged.png",
                               "/Users/josephkhan/Desktop/games_in_cpp/angry-birds-2020-JosephZKhan/Data/Images/fancyPigVeryInjured.png"};

 private:
  int pigType;
  int pigHealth;

};

#endif // ANGRYBIRDSSFML_PIG_H
