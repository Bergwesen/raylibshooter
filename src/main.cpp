
#include "resource_dir.h" // utility header for SearchAndSetResourceDir
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <cmath>
#include <vector>
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
const int alienrows = 7;







int main(){

  InitWindow(Screenbreite,Screenhoehe,"Spaceshooter"); 


  Screens Gamescreen = LOGO;
  int framecounter = 0;

  Raumschiff *Spaceship  = new Raumschiff(250,500,3);
  Texture2D Schiff = LoadTexture("resources/schiff.png");
  Spaceship->tester();
  std::vector<Schuss*> schuesse{};

  //Alien init 

  std::vector<std::vector<Alien*>> Alienblock;
  Blockalien mainblock;
  mainblock.block = &Alienblock;
  mainblock.height = 0;
  mainblock.l = 0;
  mainblock.r = 0; 
  Vector2 incr;
  int aliencd = 0;
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
        //std::cout<< aliencd << std::endl;




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

      for(auto ib : schuesse)  {
        ib->Move();
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
            Alienblock[i][x]->Movel();
          }
          
        }
        alienmoveswitch = alienmoveswitch +1;
        } else if(alienmoveswitch < 0 && alienmoveswitch >= -5){
          for (int i = 0; i != alienrows; i++)
          {
            for (int x = 0; x < aliencount; x++)
            {
              Alienblock[i][x]->Mover();
            }
            }
          alienmoveswitch = alienmoveswitch +1;
        }
        else {
          for (int i = 0; i != alienrows; i++)
          {
            for (int x = 0; x < aliencount; x++)
            {
              Alienblock[i][x]->Moved();
            }
          }

          alienmoveswitch =  (alienmovereset == 1)  ? -5 : 1;
          alienmovereset = alienmovereset * -1;
        }
        mainblock.update();
        std::cout << mainblock.l <<  " "<<mainblock.r << " " <<mainblock.height << std::endl;
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

      //Alienblock
      for (int i = 0; i != alienrows; i++)
      {
        for (int x = 0; x < aliencount; x++)
        {
          std::vector<Alien*> b = Alienblock[i];
          b[x]->Draw();
        }
        }
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
