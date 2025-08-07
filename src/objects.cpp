
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

void Schuss::dMove(){
  position.y = position.y + schussgeschwindigkeit;
  if(position.y >  800){
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

void Schuss::kill(){
  dead = 1;
}

//Anpassen sodass man nur checkt ob es groesser ist als die y hohe es muss nicht zwischen sein siehe block auch fuer schusslcaoter
int Schuss::schusskolision(Blockalien b){
    //std::cout<< position.x<< " und " <<*b.l <<" und " <<*b.r <<" und "<< *b.height <<" und " << position.y<< std::endl;
    if(position.x >= *b.l && position.x <= *b.r && position.y <= *b.height){
    std::cout<< position.x<< " und " <<*b.l <<" und " <<*b.r <<" und "<< *b.height <<" und " << position.y<< std::endl;
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

Vector2 Schuss::schusslocater(std::vector<std::vector<Alien*>> &Alienblock){
  int zeile = -1;
  
  for(auto x : Alienblock[0] ){
    zeile = zeile +1;

    //std::cout <<  position.x << " ist in  " << x->getx() <<"-"<< x->getwidth()+x->getx()<< std::endl;
    if( x != NULL){
    std::cout <<  position.x << " ist in  " << x->getx() <<"-"<< x->getwidth()+x->getx()<< std::endl;
    if( position.x >= x->getx() && (x->getx()+x->getwidth()) >= position.x){
        std::cout << "     test " << position.x << " und kkkk " << x->getx() << std::endl;
        
        break;
    }
    }
  }
  int spalte = -1;
  for(auto x : Alienblock){
        spalte = spalte +1;
       // if(x[zeile] != NULL){
        if(!x[zeile]->tot()){
        std::cout << " test " << position.y << " und " << x[zeile]->geth()<<  " und " << x[zeile]->getheight()<< std::endl;
        if( (position.y+groesse.y ) >= x[zeile]->geth() && (position.y+groesse.y) <= x[zeile]->geth() + x[zeile]->getheight()  ){
         std::cout<< "HHHIT "<< zeile << ","<<  spalte ;
         dead = 1;
          int restleben = x[zeile]->hit();
          std::cout<<" leben " << restleben <<std::endl;
         if(restleben== 0){
            //x[zeile] = NULL;
            std::cout<<"drinnnnnnnen"<<std::endl;
         }
         break;
        }
        }
  }

  Vector2 a;
  if( spalte == -1 || zeile == -1){
    a.x = -1;
    a.y = -1;
    dead = 1;
  }
  else{
  a.x = zeile;
  a.y = spalte;
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
    // es hier so enden,dass die position die mitte des schiffs ist somit kommt der strahl uach von der mitte des schiffs
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
// soll angeben ob ein alien tot ist und seine position in der list auf null gesetzt werden muss
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
  //das hier ist nicht dumme schreibweise der methode die aufgrund einer falschen debugguginng session enstant
/*void Blockalien::update(int *k,int *b,int *a,std::vector<std::vector<Alien*>> h){
    l = k;
    r = b;
    height = a;
    *l = -1;
    *r = -1;
    *height = -1;
      for(auto i = h.begin() ; i!= h.end() ; i++){
        std::vector<Alien*>& ref = *i;
         for(int x = 0; x < ref.size(); x++){
          // geplant ist es tote alien zu null zu setzen
          if( ref[x] != NULL){
 //             std::cout<< "jo " << std::endl;
              Alien &g = *ref[x];
              if(*l == -1){
                // iterieren von links nach rechts deshalb ist der erste alien die linke grenze
                *l = g.getx();
              }
              *r = std::max(*r,g.getx());
              // irgendwas ist falsch
              *height = g.geth();
//              std::cout << g.geth() << " hoehe " << std::endl;
          }
         }
          if( *r != -1 && *l != -1 && *height != -1){
            return;
          }

      }
} */

void Blockalien::update(int *k,int *b,int *a,std::vector<std::vector<Alien*>> h){
  l = k;
  r = b;
  height = a;
  *l =  6000;
  *r = -1;
  *height = -1;
  for(int y = 0; y < h.size(); y++){

    for(int z = 0 ; z< h[y].size() ; z++){
      if(h[y][z] != NULL){
      *l = std::min(*l,h[y][z]->getx());
      *r = std::max(*r,h[y][z]->getx()+h[y][z]->getwidth());
      *height = std::max(*height,h[y][z]->geth());
      }
    }
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