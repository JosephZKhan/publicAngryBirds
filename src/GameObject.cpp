//
// Created by Joseph Khan on 13/04/2021.
//

#include "GameObject.h"
#include <SFML/Graphics.hpp>
#include <iostream>

//default constructor initialises GameObjects to 0,0
GameObject::GameObject() {
  sprite.setPosition(0, 0);
}

//additional constructor allows uesr to set position
GameObject::GameObject(float newX, float newY){
  sprite.setPosition(newX, newY);
}


//setter function for sprite's texture
bool GameObject::initialiseSprite(sf::Texture& texture, std::string filename){
  if (!texture.loadFromFile(filename))
  {
    std::cout << "ERROR - Missing File";
  }

  sprite.setTexture(texture);
  return true;
}

//initialiser function for sprite pos
void GameObject::initialiseSpritePosition(float initX, float initY){
  sprite.setPosition(initX, initY);
  originX = initX;
  originY = initY;
}

//setter function for sprite pos
void GameObject::setSpritePosition(float setX, float setY){

  sprite.setPosition(setX, setY);
}

//getter function for sprite x
float GameObject::getSpriteX(){
  return sprite.getPosition().x;
}

//getter function for sprite y
float GameObject::getSpriteY(){
  return sprite.getPosition().y;
}

//setter function for sprite scale
void GameObject::scaleSprite(int setWidth, int setHeight){
  sprite.scale(setWidth, setHeight);
}

//getter function for sprite pointer
sf::Sprite* GameObject::getSpritePointer(){
  return spritePointer;
}

//death function
void GameObject::die(){
  isDead = true;
}

//undoing death function
void GameObject::resurrect(){
  isDead = false;
}

//getter function for isDead
bool GameObject::getIsDead(){
  return isDead;
}

bool GameObject::collide(int left, int top, int width, int height){
  //make left and bottom values using the input coordinates
  int right = left + width;
  int bottom = top + height;
  //if there is vertical intersection
  if ((top >= sprite.getPosition().y and top <= (sprite.getPosition().y + sprite.getGlobalBounds().height))
      or (bottom >= sprite.getPosition().y and bottom <= (sprite.getPosition().y + sprite.getGlobalBounds().height)))
  {
    //and also horizontal intersection
    if ((left > sprite.getPosition().x and left < (sprite.getPosition().x) + sprite.getGlobalBounds().width)
        or (right > sprite.getPosition().x and right < (sprite.getPosition().x) + sprite.getGlobalBounds().width))
    {
      //return true
      return true;
    }
  }
    //otherwise return false
  else {
    return false;
  }
}

//default destructor
GameObject::~GameObject(){

}
