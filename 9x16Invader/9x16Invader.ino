/*
  Space Invader, a shoot-them-up game for LOL Shield for Arduino
  Copyright 2009/2010 Benjamin Sonntag <benjamin@sonntag.fr> http://benjamin.sonntag.fr/
  
  History:
  	2009-12-30 - V0.0 Initial code at Berlin during 26C3
  	2009-12-31 - V1.0 Score Drawing, at Berlin after 26C3 ;) 

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330,
  Boston, MA 02111-1307, USA.
*/

#include "Figure.h"
#include "Font.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_IS31FL3731.h>

Adafruit_IS31FL3731 ledmatrix = Adafruit_IS31FL3731();

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif


/* -----------------------------------------------------------------  */
/* -----------------------------------------------------------------  */
/*         SPACE INVADER CODE !!!                                     */
/* -----------------------------------------------------------------  */
/* -----------------------------------------------------------------  */


// Number of fire we can use before having to wait
#define MAXFIRE 3
// Number of lives you have : 
#define STARTLIVES 4
// Maximum number of ennemies at one : 
#define MAXENNEMIES 8
// Speed of ennemies arrival :  (between 0 & 20, 20 = rare, 0 = often )
#define ENNEMIESRATE 6


/** The score of the user (number of points = speed of each killed ennemy - number of ennemies missed) */
int score=0;
/** Position of the ship between 1 & 7 */
byte shippos=4;
/** Number of lives of the user */
byte lives;

/** Position of the bullets of the ship, [0]=x [1]=y */
byte firepos[9][2]={
  {0,0},  {0,0},  {0,0},  {0,0},  {0,0},  {0,0},  {0,0},  {0,0},  {0,0}
};
/** Position and speed of the ennemies [0]=x [1]=y [2]=speed [3]=speed counter */
byte ennemypos[8][4]={
  {0,0,0,0},  {0,0,0,0},  {0,0,0,0},  {0,0,0,0},  {0,0,0,0},  {0,0,0,0},  {0,0,0,0},  {0,0,0,0}
};


/* -----------------------------------------------------------------  */
/** Draw the ship at its current position.
 * @param set 1 or 0 to set or clear the led.
 */
void drawShip(uint8_t c=1) {
//    LedSign::Set(0,shippos-1, c); 
    ledmatrix.drawPixel(0, shippos-1, c);
//    LedSign::Set(0,shippos, c); 
    ledmatrix.drawPixel(0, shippos, c);
//    LedSign::Set(0,shippos+1, c); 
    ledmatrix.drawPixel(0, shippos+1, c);
//    LedSign::Set(1,shippos, c); 
    ledmatrix.drawPixel(1, shippos, c);
}


/* -----------------------------------------------------------------  */
/** Draw the number of lives remaining at the top left of the screen
 */
void drawLives() {
  for(byte i=0;i<STARTLIVES;i++) {
//    LedSign::Set(13-i,0,(i<lives)?1:0); 
    ledmatrix.drawPixel(13-i, 0, (i<lives)?1:0);
  }
}



/* -----------------------------------------------------------------  */
/** end of the game, draw the Scores using a scrolling
 */
void endGame() {
  for(byte x=4;x<=8;x++) 
    for(byte y=0;y<=8;y++) 
//      LedSign::Set(x,y,0);
      ledmatrix.drawPixel(x, y, 0);
  
//  Figure::Scroll90(score);
  
  for(byte i=0;i<30;i++) {
   drawShip(0);
   delay(5*(30-i));
   drawShip(0);
   delay(5*(30-i));
  }
}



/* -----------------------------------------------------------------  */
/** Initialize a new game (lives, screen, score, ship ...)
 */
void initGame() {
   lives=STARTLIVES;
   score=0;
   shippos=4;
//   LedSign::Clear();
   drawLives();
   drawShip();
}


/* -----------------------------------------------------------------  */
/** Check the variator to know the position of the ship.
 * Move and redraw the ship in case of change.
 */
void moveShip()
{
  // Ship have 7 positions. Let's use a third of the variator position.
  int newshpos=7-(analogRead(5)/72); // we reverse the command (variator wrongly connected ;) )
  if (newshpos>7) newshpos=7;
  if (newshpos<1) newshpos=1;
  if (newshpos!=shippos) {
    drawShip(0);
    for(byte i=0;i<8;i++)
//      LedSign::Set(0,i,0);
      ledmatrix.drawPixel(0, i, 0);
    shippos=newshpos;
    drawShip(1);
  }
}


/* -----------------------------------------------------------------  */
/** Check the fire button and fire if it has been pushed.
 * Please note that we use a static status to check that the user 
 * pull the button between each fire.
 */
void fireShip()
{
  static byte status=0;
  if (status==0) {
    // Ship may fire 10 times (not more...)
    if (analogRead(4)>1000) {
        // FIRE ! 
        status=1;
        for(byte i=0;i<MAXFIRE;i++) {
          if (firepos[i][0]==0) {
              firepos[i][0]=2; firepos[i][1]=shippos;
              break;
          }
        }
    }
  } else {
    if (analogRead(4)<1000) status=0;
  }
}


/* -----------------------------------------------------------------  */
/** Crash : called when an ennemy touched the ship (failure!)
 */
void crash() {
   drawShip(1);
   delay(150);
   drawShip(0);
   delay(150);
   drawShip(1);
   delay(150);
   drawShip(0);
   delay(150);

   for(byte i=0;i<MAXENNEMIES;i++)
     if (ennemypos[i][0]!=0) {
//       LedSign::Set(ennemypos[i][0],ennemypos[i][1],0);
       ledmatrix.drawPixel(ennemypos[i][0], ennemypos[i][1], 0);
       ennemypos[i][0]=0;
     }
   for(byte i=0;i<MAXFIRE;i++)
     firepos[i][0]=0;

   lives--;
   if (lives==0) {
     endGame();
     initGame();
   } else {
//     LedSign::Clear();
     drawLives();
     drawShip();   
   }
}


/* -----------------------------------------------------------------  */
/** Add ennemies at the top randomly, with random speed too
 */
void addEnnemies()
{
  if (random(0,ENNEMIESRATE)==0) {
    // ENNEMY COMING !
        for(byte i=0;i<MAXENNEMIES;i++) {
          if (ennemypos[i][0]==0) {
              ennemypos[i][0]=13; ennemypos[i][1]=random(1,8);
              ennemypos[i][2]=random(2,5); // Speed of ennemies between 1 and 5 (5=slower)
              ennemypos[i][3]=0;
              break;
          }
        }
    }
}


/* -----------------------------------------------------------------  */
/** Move the ennemies, and check the collision with the ship
 */
void moveEnnemies()
{
  for(byte i=0;i<MAXENNEMIES;i++) {
    if (ennemypos[i][0]!=0) {
      ennemypos[i][3]++;
      if (ennemypos[i][2]==ennemypos[i][3]) {
        ennemypos[i][3]=0;
//        LedSign::Set(ennemypos[i][0],ennemypos[i][1],0);  
        ledmatrix.drawPixel(ennemypos[i][0],ennemypos[i][1],0);
        ennemypos[i][0]--;
        // collision with the top of the ship
        if (ennemypos[i][0]==1 && shippos==ennemypos[i][1]) { 
          crash();
        } else {
          if (ennemypos[i][0]==0) { // Collision detection
            ennemypos[i][0]=0;
            if (score>0) score-=1;
            if (shippos==ennemypos[i][1] || shippos-1==ennemypos[i][1] || shippos+1==ennemypos[i][1]) {
              crash();
            } else {              
//              LedSign::Set(ennemypos[i][0],ennemypos[i][1],0);   
              ledmatrix.drawPixel(ennemypos[i][0],ennemypos[i][1],0);              
            }
          }
        }
      } else {
//        LedSign::Set(ennemypos[i][0],ennemypos[i][1],1);    
        ledmatrix.drawPixel(ennemypos[i][0],ennemypos[i][1],1);             
      }
    }
  }
}


/* -----------------------------------------------------------------  */
/** Move the bullets, draw them, and check the collision with
 * ennemies. 
 */
void moveFires()
{
  for(byte i=0;i<MAXFIRE;i++) {
    if (firepos[i][0]!=0) {
//      LedSign::Set(firepos[i][0],firepos[i][1],0);  
        ledmatrix.drawPixel(firepos[i][0],firepos[i][1],0);    
      firepos[i][0]++;
      // Let's detect collision with ennemies : 
      for(byte j=0;j<MAXENNEMIES;j++) {
        if (ennemypos[j][0]!=0) {
          if ((ennemypos[j][0]==firepos[i][0] || ennemypos[j][0]==firepos[i][0]+1) && ennemypos[j][1]==firepos[i][1]) {  
              // Ennemy destroyed
//              LedSign::Set(ennemypos[j][0],ennemypos[j][1],0);
              ledmatrix.drawPixel(ennemypos[j][0],ennemypos[j][1],0);                 
              ennemypos[j][0]=0;
              firepos[i][0]=0;
              score+=(6-ennemypos[j][2]); // Change it in case of ennemy speed change ;) score is 5-speed
          }
        }
      }
      if (firepos[i][0]==14) {
        firepos[i][0]=0;
      } else {
//        LedSign::Set(firepos[i][0],firepos[i][1],1);
        ledmatrix.drawPixel(firepos[i][0],firepos[i][1],1);                 
      }
    }
  }
}


/* -----------------------------------------------------------------  */
/** MAIN program Setup
 */
void setup()                    // run once, when the sketch starts
{
  Serial.begin(9600);
  if (! ledmatrix.begin()) 
  {
    Serial.println("IS31 not found");
    while (1);
  }
  Serial.println("IS31 found!");
  
  randomSeed(analogRead(2));  
  
  initGame();
  drawShip();
}


/* -----------------------------------------------------------------  */
/** MAIN program Loop
 */
void loop()                     // run over and over again
{
  moveShip();
  fireShip();
  moveFires();
  moveEnnemies();
  addEnnemies();
  delay(100);
}
