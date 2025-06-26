
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









int main(){

  InitWindow(Screenbreite,Screenhoehe,"Spaceshooter"); 


  Screens Gamescreen = LOGO;
  int framecounter = 0;

  Raumschiff *Spaceship  = new Raumschiff(250,500,3);
  Texture2D Schiff = LoadTexture("resources/schiff.png");
  Spaceship->tester();

  std::vector<Schuss*> schuesse{};

  //Alien init 
  std::vector<std::vector<Alien>> Alienblock = {};
  for(int i = Row1 ; i!= End ; i++){

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
      //Schiff bewegung 
      if(IsKeyDown(KEY_A)) Spaceship->Movel();   
      if(IsKeyDown(KEY_D)) Spaceship->Mover(Screenbreite-48);   





      //Schiffaktionen
      if(IsKeyPressed(KEY_R)){
            schuesse.push_back(Spaceship->shoot());
      } 

      //Schussaktion + loeschen 
      auto it = remove_if(schuesse.begin(),schuesse.end(), [](Schuss *x){
        return x->isdead();
      }) ;
      for(auto x = it; x!= schuesse.end();x++){
        delete *x;
      }
      schuesse.erase(it,schuesse.end());
      for(auto ib : schuesse)  {
        ib->Move();
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

      for(auto i : schuesse){
        i->Draw();
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
