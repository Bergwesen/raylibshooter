
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






int main(){

  InitWindow(Screenbreite,Screenhoehe,"Spaceshooter"); 

  int score = 0;
  //schiffs leben
  //bloecke init

  Block uno = Block(einsblockx,blocky);
  Block duo = Block(duoblockx,blocky);
  Block trio = Block(trioblockx,blocky);
reset: 
  int leben = 3;

  int rowmove = 0;


  Screens Gamescreen = LOGO;
  int framecounter = 0;
  srand(time(NULL));
  Raumschiff *Spaceship  = new Raumschiff(schiffx,schiffy,4);
  int schusscd = 0;
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
  int rowcount = 0;

  int alienimgheight = Alienblock[0][0]->getheight();
  int allienimgwidth = Alienblock[0][0]->getwidth();


  //Besser und moduluarer fuer die Bloecke initialisierung
  std::vector<Block *> Bloecke(Blockcount);



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
        //std::cout<< aliencd << std::endl;



      mainblock.update(mainblock.l,mainblock.r,mainblock.height,Alienblock);

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

      for( auto& ib : schuesse)  {
        if(ib->schusskolision(mainblock) == 1){
          std::cout<< " HIT asdfaf " << std::endl;
          int asf = (ib->getx() - alienblockx) / allienimgwidth;
          int asdf = (ib->gety() - alienblocky)/alienimgheight;
          std::cout<< " real hit " << asf << " und " << asdf << std::endl;
          Vector2 k = ib->schusslocater(Alienblock); 
          std::cout<< Alienblock.size()<< " "<< Alienblock[0].size() <<" HIT "<< k.x <<" , " << k.y << std::endl;
          if(k.x != -1 && k.y != -1){
            if(Alienblock[k.y][k.x]->tot()){
                score = score +10;
            }
            }
          std::cout<<" it " << std::endl;
        } else{
          break;
        }

      }

      // hoehen stopp



      //Alien bewegung

      if (aliencd >= 5){
        aliencd = 0;
        std::cout<< "moveswitch "<< rowmove << " " << alienmoveswitch << std::endl;
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
            //  if(Alienblock[i][x] != NULL){
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
              //std::cout<< Alienblock[i][x]->geth() <<" und " << uno.gety()<<std::endl; 
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
        /*  if(alienmovereset == 1){
            alienmoveswitch = -5;
            alienmovereset = -1;
          }else {
            alienmovereset = 1;
            alienmoveswitch = 1;
          } */ 
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

      alienschusscd = 0;
      }
     // }
   if(dschuesse.size() != 0){
      auto it = remove_if(dschuesse.begin(),dschuesse.end(), [](Schuss *x){
        return x->isdead();
      }) ;
      dschuesse.erase(it,dschuesse.end());
      }
      for( auto& ib : dschuesse)  {
        ib->dMove();
      }


      // Block hit check 
      if(uno.tot() && duo.tot() && trio.tot()){ 
        //Gamescreen = ENDING;
      }
      for(auto i : dschuesse){
        if( i->getx() >= einsblockx &&  i->getx()<= einsblockx+uno.getwidth()){
          std::cout<< i->gety() << " von das test "<< blocky-uno.getheight() << std::endl;
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
            //da es ein geordneter vektor ist sollte der vordere vekor am laengste laufen und somit weiter unten sein
            break;
          }
        }
      }

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
        goto reset;
      }else if(chose == 1) {
        //free befehle ?
        std::cout<<"aaaaaaaaaaaaa"<<std::endl;
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
      DrawText(TextFormat("Leben : %d ",leben),50, 750,20,WHITE);
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
