//
// Created by Joseph Khan on 16/04/2021.
//

#include "Suvat.h"
#include <math.h>

Suvat::Suvat(){

}

Suvat::Suvat(float newU, float newA){
  u = newU;
  a = newA;
}

Suvat::~Suvat(){

}

void Suvat::updateT(){
  t += 1;
}

void Suvat::updateS(){
  s = (u * t) + (0.5  *  a * (pow(t, 2)));
}
