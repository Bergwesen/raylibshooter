
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <vector>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#define _USE_MATH_DEFINES
#include "objects.hpp"


typedef enum Screens {LOGO,TITLE,GAME,ENDING} Screens;

//globale konstante Variable 
const int Screenbreite = 500;
const int Screenhoehe = 800;
// die startwerte fuer den block
const int alienblockx = 100;
const int alienblocky = 300;
const int aliencount = 7;
const int alienrows = 6;


const int blocky = 600;
const int einsblockx = Screenbreite * 1/4;
const int duoblockx = Screenbreite * 2/4;
const int trioblockx = Screenbreite * 3/4;

const int schiffx = 250;
const int schiffy = 700;
const int schiffspeed = 4;
const int schusscoldown = 30;
const int Blockcount = 3;


void freeall(Raumschiff *a , Blockalien *b , std::vector<std::vector<Alien*>> *c,std::vector<Schuss*> *d, std::vector<Schuss*> *e){

  delete a;
  delete b->height;
  delete b->l;
  delete b->r;
  for (auto i : *c){
    for( auto x : i){
      delete x;
    }
  }
  for (auto i : *d){
    delete i;
  }
  for (auto i : *e){
    delete i;
  }
}

int deadrow(std::vector<Alien*> row){
  int count = 0;
  for( auto x : row){
    if(x->tot() == 1) count = count +1;
  }
  if(count == 0){
    return 1;
  }else if(count ==1 ){
    return 2;
  }else {
    return 3;
  }

}


int main(){

  InitWindow(Screenbreite,Screenhoehe,"Spaceshooter"); 
restart:
  Screens Gamescreen = LOGO;
  int score = 0;

  Block uno = Block(einsblockx,blocky);
  Block duo = Block(duoblockx,blocky);
  Block trio = Block(trioblockx,blocky);
  int leben = 3;
reset: 


  int startzeit = 100;
  int rowmove = 0;


  int framecounter = 0;
  srand(time(NULL));
  Raumschiff *Spaceship  = new Raumschiff(schiffx,schiffy,4,leben);
  int schusscd = 0;
  Texture2D Schiff = LoadTexture("resources/schiff.png");
  std::vector<Schuss*> schuesse{};
  std::vector<Schuss*> dschuesse{};

  //Alien init 

  std::vector<std::vector<Alien*>> Alienblock;
  Blockalien mainblock;
  mainblock.height = new int;
  mainblock.l = new int;
  mainblock.r = new int; 
  Vector2 incr;
  std::vector<Alien*> lowalien;
  int aliencd = 0;
  int alienschusscd = 0;
  int alienmoveswitch = 1;
  int alienmovereset = 1;
  incr.x = alienblockx;
  incr.y = alienblocky;
  for(int i = 0 ; i!= alienrows ; i++){
    Alienblock.push_back(std::vector<Alien*> {});
    for(int x = 0 ; x < aliencount ; x ++){
      Alien *vieh =  new Alien(i+1,incr);
      Alienblock[i].push_back(vieh);
      incr.x = incr.x + vieh->getwidth();
    }
    incr.x = alienblockx;
    incr.y= incr.y - Alienblock[i][0]->getheight();
  }
  int rowcount = 0;

  int alienimgheight = Alienblock[0][0]->getheight();
  int allienimgwidth = Alienblock[0][0]->getwidth();


  //DeathScreen input
  bool retry = false;
  int chose = 0;

  SetTargetFPS(60);
  while(!WindowShouldClose()){

    switch (Gamescreen)
    {
    case LOGO:
    {
      framecounter =framecounter +1;
      if(framecounter >= 50){
        Gamescreen = TITLE;
        framecounter = 0;
      }
    }
      break;
    case TITLE:
    {
      Gamescreen = GAME; 
    }
    break;
    case  GAME:
    {
        //counters und frames
        aliencd = aliencd + 1;
        alienschusscd = alienschusscd +1;
        schusscd = schusscd +1;


      //Gibt an ob alle aliens tot sind
      int reesetflag = mainblock.update(mainblock.l,mainblock.r,mainblock.height,Alienblock);
      if(reesetflag){
        std::cout<< "TOOT"<<std::endl;
        WaitTime(1);
        goto reset;
      }

      //Schiff bewegung 
      if(IsKeyDown(KEY_A)) Spaceship->Movel();   
      if(IsKeyDown(KEY_D)) Spaceship->Mover(Screenbreite-48);   





      //Schiffaktionen
      if(IsKeyPressed(KEY_R) && schusscd >= schusscoldown){
            schuesse.push_back(Spaceship->shoot());
            schusscd = 0;
      } 

      //Schussaktion + loeschen 
      if(schuesse.size() != 0){
      auto it = remove_if(schuesse.begin(),schuesse.end(), [](Schuss *x){
        return x->isdead();
      }) ;
      schuesse.erase(it,schuesse.end());
      }

      for( auto& ib : schuesse)  {
        ib->Move();
      }

      //Schuss Kolisioncheck
      for( auto& ib : schuesse)  {
        if(ib->schusskolision(mainblock) == 1){
          Vector2 k = ib->schusslocater(Alienblock); 
          if(k.x != -1 && k.y != -1){
            if(Alienblock[k.y][k.x]->tot()){
                score = score +10;
                startzeit = startzeit -5;
                if(startzeit< 10) startzeit = 10;
            }
            }
        } else{
          break;
        }

      }



      //Alien bewegung
      if (aliencd >= startzeit){
        aliencd = 0;
        if(alienmoveswitch  > 0 && alienmoveswitch <= 5){

          for (int x = 0; x < aliencount; x++)
          {
            if(!Alienblock[rowmove][x]->tot()){
            Alienblock[rowmove][x]->Movel();
            }
          }
        rowmove = rowmove +1;
        if(rowmove== alienrows ){
        alienmoveswitch = alienmoveswitch +1;
        rowmove = 0;
        }

        } else if(alienmoveswitch < 0 && alienmoveswitch >= -5){
            for (int x = 0; x < aliencount; x++)
            {

            if(!Alienblock[rowmove][x]->tot()){
              Alienblock[rowmove][x]->Mover();
              }
            }
            rowmove = rowmove +1;
            if(rowmove == alienrows){
          alienmoveswitch = alienmoveswitch +1;
          rowmove = 0;
          }
        }
        else {
          int nestedflag = 0;
          for (int i = 0; i != alienrows; i++)
          {
            if(nestedflag == 0){
            for (int x = 0; x < aliencount; x++)
            {

            if(!Alienblock[i][x]->tot()){
              if(Alienblock[i][x]->geth()+20 > uno.gety() - uno.getheight()){
                nestedflag = 1;
                break;
              }
              Alienblock[i][x]->Moved(uno.gety());
              }
              
            }
            }
          }

          alienmoveswitch =  (alienmovereset == 1)  ? -5 : 1;
          alienmovereset = alienmovereset * -1;
        }
        mainblock.update(mainblock.l,mainblock.r,mainblock.height,Alienblock);
      }

      //Alien schuss
      //untersten aliens
      if(alienschusscd >= 100){
      lowalien.clear();
      for(int x = 0; x < Alienblock.size(); x++){
        for(auto i : Alienblock){
          if(!i[x]->tot()){
            lowalien.push_back(i[x]);
            break;
          }

        }
      }

      //Auswahl des Aliens das schiessen soll
     int randomzahl;
     if(lowalien.size() > 0){
       randomzahl = rand() % lowalien.size();
       dschuesse.push_back(lowalien[randomzahl]->shoot());
       alienschusscd = 0;
      }
      }

   //Schussaktion + Loeschen
   if(dschuesse.size() != 0){
      auto it = remove_if(dschuesse.begin(),dschuesse.end(), [](Schuss *x){
        return x->isdead();
      }) ;
      dschuesse.erase(it,dschuesse.end());
      }
      for( auto& ib : dschuesse)  {
        ib->dMove();
      }


      //  Blockleben check
      if(uno.tot() && duo.tot() && trio.tot()){ 
        Gamescreen = ENDING;
      }
      //Alien zu Block
      for(auto i : dschuesse){
        if( i->getx() >= einsblockx &&  i->getx()<= einsblockx+uno.getwidth()){
          if((i->gety() +  i->groesse.y) >= (blocky) ){
          i->kill();   
          uno.hit();
         }
        }else if(i->getx() >= duoblockx && i->getx() <= duoblockx+duo.getwidth()){
          if((i->gety() +i->groesse.y ) >=  (blocky )  ){
          i->kill();   
          duo.hit();
         }
        } else if(i->getx() >= trioblockx && i->getx() <= trioblockx+trio.getwidth()){
          if((i->gety() + i->groesse.y) >= (blocky ) ){
          i->kill();   
          trio.hit();
         }
        }else{
          if((i->gety() - i->groesse.y)  <  blocky - uno.getheight() ){
            break;
          }
        }
      }
        //Raumschiff  zu Block
       for(auto i : schuesse){
        if( i->getx() >= einsblockx &&  i->getx()<= einsblockx+uno.getwidth()){
          if((i->gety() +  i->groesse.y) <= (blocky+uno.getheight())  ){
          i->kill();   
          uno.hit();
         }
        }else if(i->getx() >= duoblockx && i->getx() <= duoblockx+duo.getwidth()){
          if((i->gety() +i->groesse.y ) <=  (blocky+uno.getheight() )  ){
          i->kill();   
          duo.hit();
         }
        } else if(i->getx() >= trioblockx && i->getx() <= trioblockx+trio.getwidth()){
          if((i->gety() + i->groesse.y) <= (blocky + uno.getheight() ) ){
          i->kill();   
          trio.hit();
         }
        }else{
          if((i->gety() - i->groesse.y)  <  blocky - uno.getheight() ){
            break;
          }
        }
      }






   //Entfernen von schuessen die Tot sind
      for(auto i : dschuesse){
        if(i->gety() >= Spaceship->position.y){
        if(i->getx() >= Spaceship->position.x && i->getx() <= (Spaceship->position.x + Spaceship->getwidth())){
          i->kill();
          Spaceship->hit();
          leben = leben -1;
          WaitTime(0.5);
          Spaceship->position.x = Spaceship->position.x +60;
          if(leben <= 0){
           Gamescreen = ENDING; 

          }
        }
        }else {
          break;
        }
      }
                       


      }
    break;
    case  ENDING:
    {
      
      if(IsKeyPressed(KEY_W)){
        retry = true;
      }else if(IsKeyPressed(KEY_S)){
        retry = false;
      }

      if(IsKeyPressed(KEY_ENTER)){
        if(retry){
          chose = 1;
        }else{
          chose = 2;
        }
      }
      if(chose == 2){
        goto restart;
        freeall(Spaceship,&mainblock,&Alienblock,&schuesse,&dschuesse);
      }else if(chose == 1) {
        freeall(Spaceship,&mainblock,&Alienblock,&schuesse,&dschuesse);
        CloseWindow();
      } 
    }
    break;
    }







  BeginDrawing();
  ClearBackground(WHITE);
    switch (Gamescreen)
    {
    case LOGO:
    {
      DrawRectangle(0,0,Screenbreite,Screenhoehe,BLACK);
      DrawText("Space Shooters",40,Screenhoehe*0.5,50,WHITE);

    }
    break;
    case TITLE :
    {
      DrawRectangle(0,0,Screenbreite,Screenhoehe,BLACK);
      DrawText("Start",40,Screenhoehe*0.5,50,RED);

    }
    break;
    case  GAME:
    {

      DrawRectangle(0,0,Screenbreite,Screenhoehe,BLACK);
      DrawText("Space Shooters",40,Screenhoehe*0.5,50,WHITE);
      DrawText(TextFormat("Score : %d ",score),50, 10,20,WHITE);
      DrawText(TextFormat("Leben : %d,  Block 1 : %d , Block 2 : %d , Block 3 :%d ",leben,uno.getleben(),duo.getleben(),trio.getleben()),40, 750,20,WHITE);
      Spaceship->Draw();
      for(auto i : schuesse){
        i->Draw();
      }
      for(auto i : dschuesse){
        i->Draw();
      }
      //AlienBlock malen
      for (int i = 0; i != alienrows; i++)
      {
        for (int x = 0; x < aliencount; x++)
        {
          if(!Alienblock[i][x]->tot()){
          std::vector<Alien*> b = Alienblock[i];
          b[x]->Draw();
          }
        }
        }
        uno.Draw();
        duo.Draw();
        trio.Draw();

        }
    break;
    case  ENDING:
    {
      DrawRectangle(0, 0, Screenbreite, Screenhoehe, BLACK);
      DrawText("Game Over", 40, Screenhoehe * 0.5, 50, RED);
      if(retry){
      DrawText("End", 40, Screenhoehe * 0.5 + 40, 50, WHITE);
      DrawText("Retry", 40, Screenhoehe * 0.5 + 80, 50, RED);
      }else {
      DrawText("End", 40, Screenhoehe * 0.5 + 40, 50, RED);
      DrawText("Retry", 40, Screenhoehe * 0.5 + 80, 50, WHITE);
      }
    }
    break;
    }
  EndDrawing();
}
CloseWindow();
return 0;
}
