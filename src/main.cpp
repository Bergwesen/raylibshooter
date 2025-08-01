
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







int main(){

  InitWindow(Screenbreite,Screenhoehe,"Spaceshooter"); 


  Screens Gamescreen = LOGO;
  int framecounter = 0;
  srand(time(NULL));
  Raumschiff *Spaceship  = new Raumschiff(250,600,3);
  Texture2D Schiff = LoadTexture("resources/schiff.png");
  Spaceship->tester();
  //kann eigentlich eine queue sein
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

  int alienimgheight = Alienblock[0][0]->getheight();
  int allienimgwidth = Alienblock[0][0]->getwidth();


  //Bloecke 
  Block uno = Block(Screenbreite * 1/4,500);
  Block duo = Block(Screenbreite * 2/4,500);
  Block trio = Block(Screenbreite *3/4,500);




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
        //std::cout<< aliencd << std::endl;



      mainblock.update(mainblock.l,mainblock.r,mainblock.height,Alienblock);

      //Schiff bewegung 
      if(IsKeyDown(KEY_A)) Spaceship->Movel();   
      if(IsKeyDown(KEY_D)) Spaceship->Mover(Screenbreite-48);   





      //Schiffaktionen
      if(IsKeyPressed(KEY_R)){
            schuesse.push_back(Spaceship->shoot());
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

      for( auto& ib : schuesse)  {
        if(ib->schusskolision(mainblock) == 1){
          std::cout<< " HIT asdfaf " << std::endl;
          int asf = (ib->getx() - alienblockx) / allienimgwidth;
          int asdf = (ib->gety() - alienblocky)/alienimgheight;
          std::cout<< " real hit " << asf << " und " << asdf << std::endl;
          Vector2 k = ib->schusslocater(Alienblock); 
          std::cout<< Alienblock.size()<< " "<< Alienblock[0].size() <<" HIT "<< k.x <<" , " << k.y << std::endl;
//          Alienblock[k.y][k.x]->l;
          std::cout<<" it " << std::endl;
        } else{
          break;
        }

      }





      //Alien bewegung

      if (aliencd >= 300)
      {
        aliencd = 0;
        std::cout<< "moveswitch " << alienmoveswitch << std::endl;
        if(alienmoveswitch  > 0 && alienmoveswitch < 5){
        for (int i = 0; i != alienrows; i++)
        {
          for (int x = 0; x < aliencount; x++)
          {
            //testet dass wir nicht auf null alien zugreifen ,dies sind alien die getoetet wurden
            //if(Alienblock[i][x] !=  NULL){
            if(!Alienblock[i][x]->tot()){
            Alienblock[i][x]->Movel();
            }
          }
          
        }
        alienmoveswitch = alienmoveswitch +1;
        } else if(alienmoveswitch < 0 && alienmoveswitch >= -5){
          for (int i = 0; i != alienrows; i++)
          {
            for (int x = 0; x < aliencount; x++)
            {

            if(!Alienblock[i][x]->tot()){
            //  if(Alienblock[i][x] != NULL){
              Alienblock[i][x]->Mover();
              }
            }
            }
          alienmoveswitch = alienmoveswitch +1;
        }
        else {
          for (int i = 0; i != alienrows; i++)
          {
            for (int x = 0; x < aliencount; x++)
            {

            if(!Alienblock[i][x]->tot()){
            //  if(Alienblock[i][x] != NULL){
              std::cout<< i <<" und " << x<<std::endl; 
              Alienblock[i][x]->Moved();
              }
              
            }
          }

          alienmoveswitch =  (alienmovereset == 1)  ? -5 : 1;
          alienmovereset = alienmovereset * -1;
        }
        mainblock.update(mainblock.l,mainblock.r,mainblock.height,Alienblock);
        std::cout << *mainblock.l <<  " "<< *mainblock.r << " " << *mainblock.height << std::endl;
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
      std::cout<< lowalien.size() << " sollte 8 sein " << std::endl;
      int randomzahl = rand() % lowalien.size();
      //for( auto m : lowalien){
          dschuesse.push_back(lowalien[randomzahl]->shoot());
     // }
   if(dschuesse.size() != 0){
      auto it = remove_if(dschuesse.begin(),dschuesse.end(), [](Schuss *x){
        return x->isdead();
      }) ;
      dschuesse.erase(it,dschuesse.end());
      }
      alienschusscd = 0;
      }
      for( auto& ib : dschuesse)  {
        ib->dMove();
      }
                       


      }
    break;
    case  ENDING:
    {

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
      Spaceship->Draw();
      //Schuss
      for(auto i : schuesse){
        i->Draw();
      }
      for(auto i : dschuesse){
        i->Draw();
      }

      //Alienblock
      for (int i = 0; i != alienrows; i++)
      {
        for (int x = 0; x < aliencount; x++)
        {

//          if(Alienblock[i][x] != NULL){
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

    }
    break;
    }
  EndDrawing();
}
return 0;
}
