



#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#pragma once 

class Schuss{
  public:
  Schuss(Vector2 ort);
  ~Schuss();
  void Draw();
  void Move();
  int  isdead();


  private :
  Vector2 position;
  Vector2 groesse;
  int dead;


};




                    



class Raumschiff{
  public :
  Raumschiff(int x , int y,int speed);
  ~Raumschiff();
  Vector2 position;
  int Schiffspeed;
  void Draw();
  void tester();
  void Movel();
  void Mover(int border);
  Schuss* shoot();




  private :
  Texture2D bild;



};






                    
