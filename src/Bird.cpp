//
// Created by Joseph Khan on 15/04/2021.
//

#include "Bird.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

//default bird constructor
Bird::Bird(){
  birdType = 0;
}

//bird deconstructor
Bird::~Bird(){

}

//birdType getter function
int Bird::getBirdType(){
  return birdType;
}

//birdType setter function
void Bird::setBirdType(int newBirdType){
  birdType = newBirdType;
}

//isMoving getter function
bool Bird::getIsMoving()
{
  return isMoving;
}

//isMoving setter function
void Bird::setBirdMoving(bool newBool){
  isMoving = newBool;
}

//bird movement updating
void Bird::moveBird() {
  if (birdType == 0)
  {
    horizontal.updateT();
    horizontal.updateS();

    vertical.updateT();
    vertical.updateS();
  }

  if (birdType == 1)
  {
    if (!isShootingForward)
    {
      horizontal.updateT();
      horizontal.updateS();

      vertical.updateT();
      vertical.updateS();
    }
    else
    {
      horizontal.updateT();
      horizontal.updateS();
    }
  }

  if (birdType == 2)
  {
    if (!isShootingDown)
    {
      horizontal.updateT();
      horizontal.updateS();

      vertical.updateT();
      vertical.updateS();
    }
    else
    {
      vertical.a = 0;
      vertical.u = -5;
      vertical.updateT();
      vertical.updateS();
    }
  }

}

//bird trajectory update
void Bird::changeAim(float multX, float multY){

  horizontal.u = horizontal1.u * multX;
  vertical.u = vertical1.u * multY;
}

