//
// Created by Joseph Khan on 16/04/2021.
//

#ifndef ANGRYBIRDSSFML_SUVAT_H
#define ANGRYBIRDSSFML_SUVAT_H

class Suvat
{
 public:
  Suvat();
  Suvat(float newU, float newA);
  ~Suvat();
  void updateT();
  void updateS();

  float s = 0;
  float u;
  float v = u;
  float a;
  float t = 0;

 private:


};

#endif // ANGRYBIRDSSFML_SUVAT_H
