
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include  "objects.hpp"\



const int schussbreite = 4;
const int schusslaenge = 10;
const int schussgeschwindigkeit = 2; 

Raumschiff::Raumschiff(int x,int y,int speed){
      position.x = x;
      position.y = y;
      bild = LoadTexture("resources/schiff.png");
      Schiffspeed =  speed;

};
Raumschiff::~Raumschiff(){
  UnloadTexture(bild);
}
void Raumschiff::Draw(){
    DrawTextureV(bild,position,WHITE);
};

void Raumschiff::tester(){
  printf(" jo \n");
};

Schuss* Raumschiff::shoot(){
    // es hier so enden,dass die position die mitte des schiffs ist somit kommt der strahl uach von der mitte des schiffs
    Schuss *bang= new Schuss(position);
    return bang;

};

void Raumschiff::Movel(){

      position.x = position.x -  Schiffspeed ;   
      if(  position.x < 0 ){
        position.x = 0;
      };   
}
void Raumschiff::Mover(int border){

      position.x = position.x +  Schiffspeed;   
      if(position.x > (GetScreenWidth()- bild.width) ) {
          position.x = GetScreenWidth()-bild.width;
       }
}


Schuss::Schuss(Vector2 ort){
    position.x = ort.x;
    position.y = ort.y;
    groesse.x = schussbreite;
    groesse.y = schusslaenge;
    dead = 0;
}

 void Schuss::Draw(){
    DrawRectangleV(position,groesse,RED);
}

 Schuss::~Schuss(){
  printf("ist tot\n");
}
void Schuss::Move(){
  position.y = position.y -schussgeschwindigkeit;
  if(position.y <  0){
    dead = 1;
  }

}

int Schuss::isdead(){
  if(dead == 1){
  printf("is   b tot\n");
    return 1;
  }
  return 0;
}





Alien::Alien(Alientyp typ,Vector2 pos){
  position.x = pos.x;
  position.y = pos.y;
  sein = typ;
  switch (sein)
  {
  case Row1:
  {
    bild = LoadTexture("a1.png");
  }
    break;
    case Row2 :
    {

    bild = LoadTexture("a2.png");
    }
    break;

    case  Row3:
    {

    bild = LoadTexture("a3.png");
    }
    break;
  
    case  Row4:
    {

    bild = LoadTexture("a4.png");
    }
    break;

    case  Row5:
    {

    bild = LoadTexture("a5.png");
    }
    break;

    case  Row6:
    {

    bild = LoadTexture("a6.png");
    }
    break;
  }



}


Alien::~Alien(){
  UnloadTexture(bild);
}

void Alien::Draw(){
    DrawTextureV(bild,position,WHITE);
};

void Alien::Movel(){

      position.x = position.x -  steps;   
      if(  position.x < 0 ){
        position.x = 0;
      };   
}
void Alien::Mover(){

      position.x = position.x +  steps;   
      if(position.x > (GetScreenWidth()- bild.width) ) {
          position.x = GetScreenWidth()-bild.width;
       }
}
