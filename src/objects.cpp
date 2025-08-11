
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <iterator>
#include  "objects.hpp"



const int schussbreite = 4;
const int schusslaenge = 10;
const int schussgeschwindigkeit = 3; 

Raumschiff::Raumschiff(int x,int y,int speed,int live){
      position.x = x;
      position.y = y;
      bild = LoadTexture("resources/schiff.png");
      Schiffspeed =  speed;
      leben = live;

};
Raumschiff::~Raumschiff(){
  UnloadTexture(bild);
}
void Raumschiff::Draw(){
    DrawTextureV(bild,position,WHITE);
};


void Raumschiff::hit(){
  if(leben >= 1){
    leben = leben -1;
    }
}

int Raumschiff::getwidth(){
  return bild.width;
}

int Raumschiff::getheight(){
  return bild.height;
}


Schuss* Raumschiff::shoot(){
    Vector2 temp = position;
    temp.x = position.x + bild.width/2;
    Schuss *bang= new Schuss(temp);
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

void Schuss::dMove(){
  position.y = position.y + schussgeschwindigkeit;
  if(position.y >  800){
    dead = 1;
  }

}

int Schuss::isdead(){
  if(dead == 1){
    return 1;
  }
  return 0;
}
//Markiert einen Schuss damit er spaeter geloescht wird
void Schuss::kill(){
  dead = 1;
}

//Es sollen nur Schuesse weiter ueberpruft werden, die sich in der Breite   und Groesse befinden
int Schuss::schusskolision(Blockalien b){
    if(position.x >= *b.l && position.x <= *b.r && position.y <= *b.height){
      return 1;
    }
      return 0;
    
};

float Schuss::getx(){
  return position.x;
}

float Schuss::gety(){
  return position.y;
}

//Sucht den Alien , der getroffen wird 
//Leider noch in n^2 noch nicht geaendert
Vector2 Schuss::schusslocater(std::vector<std::vector<Alien*>> &Alienblock){
  int zeile = -1;
  int spalte = -1;
  int flag = false;
  for(auto y : Alienblock ){
    spalte = spalte +1;
    for (auto x : y)
    {
      zeile = zeile+ 1;
      if(!x->tot()){
      if (position.x >= x->getx() && (x->getx() + x->getwidth()) >= position.x)
      {

        if ((position.y + groesse.y) >= x->geth() && (position.y + groesse.y) <= (x->geth() + x->getheight()))
        {
          flag = true;
          x->hit();
          break;
        }
      }
      }
    }
    if(flag){
      break;
    }
    zeile = -1;
  }

  Vector2 a;
  if( spalte == -1 || zeile == -1){
    a.x = -1;
    a.y = -1;
  }
  else{
  a.x = zeile;
  a.y = spalte;
  dead = 1;
  }
  return a;
}





Alien::Alien(int b,Vector2 pos){
  position.x = pos.x;
  position.y = pos.y;
  switch (b)
  {
  case 1:
  {
    bild = LoadTexture("resources/a1.png");
  }
    break;
    case 2 :
    {

    bild = LoadTexture("resources/a2.png");
    }
    break;

    case  3:
    {


    bild = LoadTexture("resources/a3.png");
    }
    break;
  
    case  4:
    {

    bild = LoadTexture("resources/a4.png");
    }
    break;

    case  5:
    {

    bild = LoadTexture("resources/a5.png");
    }
    break;

    case  6:
    {

    bild = LoadTexture("resources/a6.png");
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

Schuss* Alien::shoot(){
    Vector2 temp = position;
    temp.x = position.x + bild.width/2;
    Schuss *bang= new Schuss(temp);
    return bang;

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

void Alien::Moved(int border){
  position.y = position.y + steps;
  if(position.y > border){
    position.y = position.y - steps;
    return;
  }
  if(position.y > (GetScreenHeight()-bild.height)){
    position.y = GetScreenHeight() -bild.height;
  }
}


int Alien::getwidth(){
  return bild.width;
}

int Alien::getheight(){
  return bild.height;
}


int Alien::geth(){
  return position.y;
}

int Alien::tot(){
  if(leben <= 0){
    return 1;
  }
  return 0;
}

int Alien::getx(){
  return position.x;
}

int Alien::hit(){
  leben = leben -1;
  if(leben == 0){
    return 0;
  } else if(leben < 0){
    //fehler szenario
    return 0;
  } else {
    return leben;
  }
}
//Der Block muss regelmaessig geupdatet werden,damit er nach jedem Schuss und jeder Bewegung die neuen Werte hat
int Blockalien::update(int *k,int *b,int *a,std::vector<std::vector<Alien*>> h){
  l = k;
  r = b;
  height = a;
  *l =  6000;
  *r = -1;
  *height = -1;
  int dead = true;
  int aliencount = 0;
  for(int y = 0; y < h.size(); y++){

    for(int z = 0 ; z< h[y].size() ; z++){
      if(!h[y][z]->tot()){
      *l = std::min(*l,h[y][z]->getx());
      *r = std::max(*r,h[y][z]->getx()+h[y][z]->getwidth());
      *height = std::max(*height,h[y][z]->geth());
      dead = false;
      aliencount = aliencount +1 ;
      }
    }
  }
  if(dead){
    return 1;
  }
  else{
    return 0;
  }
}

Block::Block(int x , int y){
    position.x = x;
    position.y = y;
    bild = LoadTexture("resources/b1.png");
}

int Block::getx(){
  return position.x; 
}

int Block::getleben(){
  return leben; 
}

int Block::gety(){
  return position.y; 
}


int Block::tot(){
  if( leben<= 0){
    return 1;
  }else {
    return 0;
  }

}

void Block::Draw(){
    DrawTextureV(bild,position,WHITE);
    //TODO 
    /*
    switch(leben){
      case 0 :
      {
        bild = LoadTexture();
      }
      break;
      case 1 :
      {

        bild = LoadTexture();
      }
      break;
      case 2 :
      {
        bild = LoadTexture();
      }
      break;
      case 3 :
      {
        bild = LoadTexture();
      }
      break;
      default :


    } */
};
void Block::hit(){
    leben = leben -1;
    if(leben <= 0){
      leben = 0;
    }
}

int Block::getheight(){
  return bild.height;
}

int Block::getwidth(){
  return bild.width;
}