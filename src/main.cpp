#include <raylib-cpp/raylib-cpp.hpp>
#include <string>
#include <ctime>
#include <stdlib.h>
#include "pipe.h"
#include <iostream>
//using namespace std;

int score;

int deathModifier = 10;
double acceleration = 0.4;
double timestep = 0.1;
double Time= 0;
double velocity = 0;
bool gameBegin = false;
bool inGame = true;
double deltaTime;
double oldTime = clock();

int pipeSpeed = 25;

bool pipePass;
bool pipe2Pass;


double grav(double y) {
    y += timestep * (velocity + timestep * acceleration / 2) * deltaTime;
    velocity += timestep * acceleration * deltaTime;
    if (y <= 0) {
        y = 0;
    }
    return y;
}

void jump(double y){
    velocity = -10;
}

void UpdateTime(){
    deltaTime = clock() - oldTime;
    std::cout << "greg";
    double fps = (1 / deltaTime) * 1000;
    oldTime = clock();
    Time += timestep;
}

Rectangle player{(screenWidth/2)-(35/2),(screenHeight/2)-(35/2), 35,35};

pipe Pipe = {screenWidth,resetPipe(screenHeight)};
pipe Pipe2 = {screenWidth + (screenWidth/2),resetPipe(screenHeight) };

void die(){
    
    inGame = false;

}

int greg;

int main() {
    
    // Initialization


    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Flappy Disk [ALPHA 0.2.0]");
    
    SetTargetFPS(75);

    Texture2D flop = LoadTexture("./assets/floppy.png");

    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update the time variables used for movement
        UpdateTime();

        // Check if the game has begun
        if (gameBegin) {
            if (inGame){            // Gravity
            player.y = grav(player.y);
            // Check for jumping
            if (IsKeyPressed(KEY_SPACE)) {jump(player.y);}
            if (Pipe.x < 0-100){ Pipe.x = screenWidth; Pipe.height = resetPipe(screenHeight); pipePass = false;}
            Pipe.x = Pipe.x - (pipeSpeed * deltaTime / 100);
            Pipe.drawPipe(screenHeight);

            if (Pipe2.x < 0-100){ Pipe2.x = screenWidth; Pipe2.height = resetPipe(screenHeight); pipe2Pass = false;}
            Pipe2.x = Pipe2.x - (pipeSpeed * deltaTime / 100);
            Pipe2.drawPipe(screenHeight);

            if (player.y >= ((screenHeight-50)+deathModifier)){
                die();
             }
            } 
            else if (!inGame) {
                Pipe.drawPipe(screenHeight);
                Pipe2.drawPipe(screenHeight);
                DrawText("OH NO! You died!", 20, (screenHeight/2)+player.width+10,50,RED);
                if (IsKeyPressed(KEY_SPACE)) {
                    player.y = screenHeight/2;
                    velocity = 0;
                    Pipe.x = screenWidth;
                    Pipe.height = resetPipe(screenHeight);
                    Pipe2.x = screenWidth + (screenWidth/2);
                    Pipe2.height = resetPipe(screenHeight);
                    inGame = true;
                    gameBegin = false;
                    score = 0;
                    pipePass = false;
                    pipe2Pass = false;
                }
            }
        }
        else {
            DrawText("Press [SPACE] to start", 20, (screenHeight/2)+player.width+10,30,GOLD);
            if (IsKeyPressed(KEY_SPACE)) {gameBegin = true;
                                          inGame = true;
                                          jump(player.y);}
        } 
        if (CheckCollisionRecs(player, Pipe.Rec1) || CheckCollisionRecs(player, Pipe.Rec2)|| CheckCollisionRecs(player, Pipe2.Rec1)|| CheckCollisionRecs(player, Pipe2.Rec2)){
            die();
        }
        if (player.x > Pipe.x){
            if (!pipePass){
                score ++;
                pipePass = true;
            }
        } else if (player.x > Pipe2.x){
            if (!pipe2Pass){
                score ++;
                pipe2Pass = true;
            }
        }
        
        
        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        //DrawText(("Y: " + std::to_string(player.y)).c_str(),0,0,20,GOLD);
        //DrawText(("Downwards Velocity: " + std::to_string(velocity)).c_str(),0,25,20,GOLD);
        //DrawText(("Time: " + std::to_string(Time)).c_str(),0,50,20,GOLD);
        //DrawText(("FPS: " + std::to_string(GetFPS())).c_str(),0,75,20,GOLD);
        //DrawText(("PipeX: " + std::to_string(Pipe.x)).c_str(),0,100,20,GOLD);
        //DrawText(("Pipe2X: " + std::to_string(Pipe2.x)).c_str(),0,125,20,GOLD);
        //DrawText(("Last Deltatime: " + std::to_string(deltaTime)).c_str(),0,150,20,GOLD);
       // DrawRectangle((screenWidth/2)-(playerSize/2),y,playerSize,playerSize,RED);
        //DrawRectangleRec(player,RED);
        //DrawTextureRec(flop,player,{player.x,player.y},WHITE);
        DrawTextureEx(flop,{player.x,player.y},0,1,WHITE);
        DrawText((std::to_string(score)).c_str(),(screenWidth/2)-(40/2)+(25/2),20,40,GOLD);
        EndDrawing();

    }

    return 0;
}

