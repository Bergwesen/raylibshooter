



#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <vector>
#pragma once 


typedef enum Alientyp{ Row1,Row2,Row3,Row4,Row5,Row6,Ende};





                    




class Alien{
  public:
  Alien(int,Vector2);
  ~Alien();
  void Draw();
  void Movel();
  void Mover();
  void Moved();
  int hit();
  int getwidth();
  int getheight();
  int getx();
  int geth();

  private : 
  Vector2 position;
  int steps = 10;
  Alientyp sein;
  Texture2D bild;
  int leben = 3;







};



typedef struct Blockalien{
  int *l;
  int *r;
  int *height;
  void update(int *k ,int *b,int *a,std::vector<std::vector<Alien*>> h);
  };



                    


class Schuss{
  public:
  Schuss(Vector2 ort);
  ~Schuss();
  void Draw();
  void Move();
  int  isdead();
  int schusskolision(Blockalien b);


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

//das hier ist nicht dumme schreibweise der methode die aufgrund einer falschen debugguginng session enstant
/*typedef struct Blockalien{
  int *l;
  int *r;
  int *height;
  void update(int *k ,int *b,int *a,std::vector<std::vector<Alien*>> h);
  }; */



                    
//FUNKTIONEN
