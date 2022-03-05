/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// L_Down               motor         12              
// L_Up                 motor         11              
// R_Down               motor         19              
// R_Up                 motor         20              
// L_ArmSpin            motor         1               
// R_ArmSpin            motor         10              
// ClawSpin             motor         15              
// GroupTest            motor_group   4, 5            
// Pump                 digital_out   A               
// Tail                 motor         18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <stdio.h>
#include <stdlib.h>

using namespace vex;
using namespace std;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
float velocityMult = 1.0;
float sideArmMult  = 0.8;
float sideArmFlip  = 1.0;
float clawFlip     = 1.0;
float timeToSpawn  = 0.0f;
vector<vector<int>> board(24, vector<int>(10, 0));  // Tetris board

bool allowButtons  = true;
float timeToPrint  = 100;   // 200 miliseconds divided by 20 miliseconds


//  --- Velocity Functions ---
void FlipArms(){
  sideArmFlip *= -1;
  allowButtons = false;
}

void FlipClaw(){
  wait(100, msec);
  clawFlip    *= -1;
  allowButtons = false;
}

void IncreaseVelocity(){
  wait(100, msec);
  // The reason for this IF statement is just in case the velocity has been flipped
  if (velocityMult >= 0){
    velocityMult += 0.1 / 14;
  }
  else{
    velocityMult -= 0.1 / 14;
  }

  allowButtons = false;
}

void DecreaseVelocity(){
  wait(100, msec);
  // The reason for this IF statement is just in case the velocity has been flipped
  if (velocityMult >= 0){
    velocityMult -= 0.1 / 14;
  }
  else{
    velocityMult += 0.1 / 14;
  }

  allowButtons = false;
}

void IncreaseArmSpeed(){
  wait(100, msec);
  if (sideArmMult >= 0){
    sideArmMult += 0.1 / 14;
  }
  else{
    sideArmMult -= 0.1 / 14;
  }

  allowButtons = false;
}

void DecreaseArmSpeed(){
  wait(100, msec);
  if (sideArmMult <= 0){
    sideArmMult -= 0.1 / 14;
  }
  else{
    sideArmMult += 0.1 / 14;
  }

  allowButtons = false;
}


void AllowButtons(){
  allowButtons = true;
}


//  --- Printing Debug Function ---
void PrintToScreen(){
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);

  Brain.Screen.print("Current Velocity: ");
  //Brain.Screen.print(velocityMult * 100);
  //Brain.Screen.print("%");

  Brain.Screen.newLine();

  Brain.Screen.print("VelocityMult: ");
  Brain.Screen.print(velocityMult);

  Brain.Screen.newLine();

  Brain.Screen.print("Side Arm Mult: ");
  Brain.Screen.print(sideArmMult);

  Brain.Screen.newLine();

  Brain.Screen.print("Side Arm Flip: ");
  Brain.Screen.print(sideArmFlip);

  Brain.Screen.newLine();

  Brain.Screen.print("Claw Flip: ");
  Brain.Screen.print(clawFlip);    

  Brain.Screen.newLine();
  Brain.Screen.newLine();


  Brain.Screen.setCursor(7, 1);
  Brain.Screen.clearLine();

  Brain.Screen.print("Time to Print: ");
  Brain.Screen.print(timeToPrint);

  Brain.Screen.newLine();
  Brain.Screen.print("Game Mode: ");
}


//  --- Movement Functions ---
void Movement(float vMove, float hMove){
  L_Up.setVelocity(vMove + hMove, percent);
  R_Up.setVelocity(vMove - hMove, percent);
  L_Down.setVelocity(vMove + hMove, percent);
  R_Down.setVelocity(vMove - hMove, percent);

  L_Up.spin(vex::forward);
  R_Up.spin(vex::forward);
  L_Down.spin(vex::forward);
  R_Down.spin(vex::forward);
}

void ArmMovement(float armMove){
  L_ArmSpin.setVelocity(-armMove, percent);
  R_ArmSpin.setVelocity(-armMove, percent);

  L_ArmSpin.spin(vex::forward);
  R_ArmSpin.spin(vex::forward);
}

void ClawMovement(){
  if (Controller1.ButtonR1.pressing()){
    //ClawSpin.setVelocity(75, percent);
    Pump.set(true);
  }
  else if (Controller1.ButtonR2.pressing()){
    Pump.set(false);
  }
  //else{
    //ClawSpin.setVelocity(0, percent);
  //}

  //ClawSpin.spin(vex::forward);
}

void TailDown(){
  Tail.setVelocity(100, pct);
  Tail.spin(fwd);
}

void TailMove(double velocity){
  Tail.setVelocity(velocity, pct);
  Tail.spin(fwd);
}

float clawMove = 0.0;
void ClawDown(){
  clawMove = 100;
}

void ClawUp(){
  clawMove = -100;
}

void ClawNone(){
  clawMove = 0.0;
}

//  Tetris Functions. Ignore it lol
void AddPiece(){
  // Let's only add Line pieces for now:
  board[0][5] = 1;
  board[1][5] = 1;
  board[2][5] = 1;
  board[3][5] = 1;
}

// Tetris Drawing loop
void Draw(int height, int width){
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);

  // Block size = 4x4
  // Padding = 1
  int blockSize = 8;
  int xPad = 8;
  int yPad = 8;
  int bPad = 1;

  Brain.Screen.setFillColor(black);
  for (int i = 0; i < height; i++){
    for (int e = 0; e < width; e++){
      if (board[i][e] == 0){
        Brain.Screen.drawRectangle(xPad + (blockSize * e) + bPad, yPad + (blockSize * i) * bPad, blockSize, blockSize);
      }
      else{
        Brain.Screen.setFillColor(white);
        Brain.Screen.drawRectangle(xPad + (blockSize * e) + bPad, yPad + (blockSize * i) * bPad, blockSize, blockSize);
        Brain.Screen.setFillColor(black);
      }
    }
  }
}

// Main Tetris Update Loop
void Update(int height, int width){
  // Looping through each block to check collisions is inefficient. Instead, we can just check for the block's collisions.
  // The "Moving" block should have a separate ID from the "Static" blocks.

  if (timeToSpawn <= 0){
    AddPiece();
    timeToSpawn = 1000.0f;
  }
  else{
    timeToSpawn -= 20;
  }

  for (int y = 23; y > 0; y--){
    for (int x = 0; x < 10; x++){
      if (board[y + 1][x] == 1){
        
      }
      if (board[y - 1][x] == 1){
        board[y - 1][x] = 0;
        board[y][x] = 1;
      }
    }
  }

  Draw(height, width);
}



//  --- Main Robot Functions ---
void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void autonomous(void) {
  float unitMult = 4.0f;
  float rotMult  = 1.0f;
  
  motor_group All   = motor_group(R_Down, L_Down);
  motor_group Right = motor_group(R_Down, R_Up);
  motor_group Left  = motor_group(L_Down, L_Up);
  motor_group Arms  = motor_group(R_ArmSpin, L_ArmSpin);

  All.setVelocity(100, percent);
  Right.setVelocity(100, percent);
  Left.setVelocity(100, percent);
  Arms.setVelocity(100, percent);
  
  /*
  All.spinFor(4.0f * unitMult, rotationUnits::deg, true);     // This is a blocking code
  //All.spinFor(1.5f * unitMult, rotationUnits::deg, true);

  Right.spinFor(5.0f * rotMult, rotationUnits::deg, true);   // This is a non-blocking code
  //Left.spinFor( 5.0f * rotMult, rotationUnits::deg, true);

  All.spinFor(1.0f * unitMult, rotationUnits::deg, true);
  */

  All.spinFor(vex::forward, 2.0, vex::seconds);
}


void usercontrol(void) {
  // -- Initializing Tetris Intructions --
  // Brain Screen Size:  480 x 272 pixels
  // Tetris Board Size:  10 x 24 spaces
  // Block size: 4 x 4 pixels

  bool gameMode = false;
  int width  = 10;
  int height = 24;

  float dTime = 20;
  float printTime = 0;
  //float timeToSpawn = 1000;

  bool swapped = false;
  //  -- End of local variables --

  while (1) {
    //  --- Main Robot Loop ---
    if (!gameMode){
      float vMove = Controller1.Axis3.position(percent) * velocityMult;
      float hMove = Controller1.Axis4.position(percent) * velocityMult * 0.5;

      float armMove = Controller1.Axis2.position(percent) * sideArmMult * sideArmFlip;

      Movement(vMove, hMove);
      ArmMovement(armMove);
      ClawMovement();  // Don't have enough time rn, so I'm putting both speeds together

      // Debug Button Presses
      Controller1.ButtonUp.pressed(IncreaseVelocity);
      Controller1.ButtonDown.pressed(DecreaseVelocity);

      Controller1.ButtonRight.pressed(IncreaseArmSpeed);
      Controller1.ButtonLeft.pressed(DecreaseArmSpeed);

      Controller1.ButtonL1.pressed(TailDown);

      if (Controller1.ButtonL2.pressing()){
        TailMove(100);
      }
      else {
        TailMove(0);
      }

      //Controller1.ButtonL1.pressed(autonomous);

      if (Controller1.ButtonX.pressing() && !swapped){
        if (velocityMult > 0){
          velocityMult *= -1;
        }
      }
      else if (Controller1.ButtonY.pressing()){
        if (velocityMult < 0){
          velocityMult *= -1;
        }
      }

      if (printTime <= 0){
        PrintToScreen();
        printTime = 50;
      }
      else{
        printTime -= 1;
      }
      
      if (Controller1.ButtonA.pressing()){
        gameMode = true;
      }
    }
    //  --- Main Tetris Game Loop ---
    else{
      // Updating for the Game
      if (dTime <= 0){
        Update(height, width);

        dTime = 20;
      }
      else{
        dTime -= 1;
      }

      if (Controller1.ButtonB.pressing()){
        gameMode = false;
      }
    }

    wait(20, msec); 
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}