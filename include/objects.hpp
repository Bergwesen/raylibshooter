



#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <vector>
#pragma once 

//Um die Auswahl der Bilder fuer die jeweiligen Aliens zu vereinfachen
typedef enum Alientyp{ Row1,Row2,Row3,Row4,Row5,Row6,Ende};





class Schuss; 




class Alien{
  public:
  Alien(int,Vector2);
  ~Alien();
  void Draw();
  void Movel(); //links
  void Mover(); //rechts
  void Moved(int border); //runter
  int hit();
  int getwidth(); //bilderbreite
  int getheight(); //bildhoehe
  int getx();
  int geth();
  int tot();
  Schuss* shoot();

  private : 
  Vector2 position;
  int steps = 15;
  Alientyp sein;
  Texture2D bild;
  int leben = 1;







};


//Struct um Informationen ueber den Alienblock zusammeln : Hoehe und Breite somit muss nicht immer eine Schusskolision berechnet werden
typedef struct Blockalien{
  int *l;
  int *r;
  int *height;
  int update(int *k ,int *b,int *a,std::vector<std::vector<Alien*>> h);
  };



                    


class Schuss{
  public:
  Schuss(Vector2 ort);
  ~Schuss();
  void Draw();
  void Move();
  void dMove();
  float getx();
  float gety();
  int  isdead();
  void kill();
  int schusskolision(Blockalien b);
  Vector2 schusslocater(std::vector<std::vector<Alien*>> &Alienblock );
  Vector2 groesse;


  private :
  Vector2 position;
  //Vector2 groesse;
  int dead;

};


class Raumschiff{
  public :
  Raumschiff(int x , int y,int speed,int live);
  ~Raumschiff();
  Vector2 position;
  int Schiffspeed;
  void Draw();
  void Movel();
  void Mover(int border);
  Schuss* shoot();
  void hit();
  int getheight();
  int getwidth();



  private :
  Texture2D bild;
  int leben = 3;



};


class Block{
  public:
  void Draw();
  Block(int x, int y);
  int tot();
  void hit();
  int gety();
  int getx();
  int getheight();
  int getwidth();
  int getleben();

  private :
  int leben = 8;
  Vector2 position;
  Texture2D bild;


};
