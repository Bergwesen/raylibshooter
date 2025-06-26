
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