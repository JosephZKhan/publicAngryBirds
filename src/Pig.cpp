//
// Created by Joseph Khan on 16/04/2021.
//

#include "Pig.h"

//default pig constructor
Pig::Pig(){
  pigType = 0;
  pigHealth = 1;
}

//pig deconstructor
Pig::~Pig(){

}

//pigType getter function
int Pig::getPigType(){
  return pigType;
}

//pigType setter function
void Pig::setPigType(int newPigType){
  pigType = newPigType;
}

//pigHealth getter function
int Pig::getPigHealth(){
  return pigHealth;
}

//pigHealth setter function
void Pig::setPigHealth(int newPigHealth){
  pigHealth = newPigHealth;
}

//function to deplete pigs' health & update sprite if necessary
void Pig::depletePigHealth(){
  pigHealth = pigHealth - 1;

  if (pigType == 1)
  {
    switch (pigHealth)
    {
      case 1:
        initialiseSprite(fancyPigVeryInjuredTexture, pigImageList[3]);
        return;

      case 2:
        initialiseSprite(fancyPigDamagedTexture, pigImageList[2]);
    }
  }
}
