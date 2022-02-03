//
// Created by Joseph Khan on 13/04/2021.
//

#ifndef ANGRYBIRDSSFML_GAMEOBJECT_H
#define ANGRYBIRDSSFML_GAMEOBJECT_H
#include <SFML/Graphics.hpp>


class GameObject
{
 public:
  GameObject();
  GameObject(float new_x, float new_y);
  ~GameObject();


  bool initialiseSprite(sf::Texture &texture, std::string filename);
  void initialiseSpritePosition(float initX, float initY);
  void setSpritePosition(float setX, float setY);
  float getSpriteX();
  float getSpriteY();
  void scaleSprite(int setWidth, int setHeight);
  sf::Sprite* getSpritePointer();

  int originX;
  int originY;

  void die();
  void resurrect();
  bool getIsDead();

  bool collide(int left, int top, int width, int height);

 private:
  sf::Sprite sprite;
  sf::Sprite* spritePointer = &sprite;

  bool isDead = false;

};

#endif // ANGRYBIRDSSFML_GAMEOBJECT_H
