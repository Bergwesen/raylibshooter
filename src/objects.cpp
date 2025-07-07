
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

int Schuss::isdead(){
  if(dead == 1){
  printf("is   b tot\n");
    return 1;
  }
  return 0;
}


int Schuss::schusskolision(Blockalien b){
    std::cout<< position.x<< " und " <<*b.l <<" und " <<*b.r <<" und "<< *b.height <<" und " << position.y<< std::endl;
    if(position.x >= *b.r && position.x <= *b.l && position.y <= *b.height){
      return 1;
    }
      return 0;
    
};





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

void Alien::Moved(){
  position.y = position.y + steps;
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

int Alien::getx(){
  return position.x;
}
// soll angeben ob ein alien tot ist und seine position in der list auf null gesetzt werden muss
int Alien::hit(){
  leben = leben -1;
  if(leben == 0){
    return 0;
  } else if(leben < 0){
    //fehler szenario
    return 1111110;
  } else {
    return 1;
  }
}
  //das hier ist nicht dumme schreibweise der methode die aufgrund einer falschen debugguginng session enstant
void Blockalien::update(int *k,int *b,int *a,std::vector<std::vector<Alien*>> h){
    l = k;
    r = b;
    height = a;
    *l = -1;
    *r = -1;
    *height = -1;
      for(auto i = h.rbegin() ; i!= h.rend() ; i++){
        std::vector<Alien*>& ref = *i;
         for(int x = 0; x < ref.size(); x++){
          // geplant ist es tote alien zu null zu setzen
          if( ref[x] != NULL){
              std::cout<< "jo " << std::endl;
              Alien &g = *ref[x];
              if(*l == -1){
                // iterieren von links nach rechts deshalb ist der erste alien die linke grenze
                *l = g.getx();
              }
              *r = std::max(*r,g.getx());
              // irgendwas ist falsch
              *height = g.geth();
          }
          if(*r != -1 && *l != -1 && *height != -1){
            return;
          }
         }
          if( *r != -1 && *l != -1 && *height != -1){
            return;
          }

      }
}






















//FUNKTIONENEN

