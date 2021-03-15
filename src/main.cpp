#include <raylib-cpp.hpp>
#include <string>
//#include <iostream>
//using namespace std;

int screenWidth = 854;
int screenHeight = 480;

double acceleration = 1;
double timestep = 1;
double time = 0;
double velocity = 0;

double grav(double y) {
    time += timestep;
    y += timestep * (velocity + timestep * acceleration / 2);
    velocity += timestep * acceleration;
    if (y <= 0) {
        y = 0;
    }
    return y;
}

void jump(double y){
    velocity = -15;
}

int main() {
    
    // Initialization


    raylib::Color textColor(LIGHTGRAY);
    raylib::Window w(screenWidth, screenHeight, "Flappy Disk [ALPHA 0.1.0]");
    
    SetTargetFPS(60);

    int playerSize = 50;
    double y = (screenHeight/2)-(playerSize/2);
    bool gameBegin = false;


    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update
        if (gameBegin) {
            y = grav(y);
            if (IsKeyPressed(KEY_SPACE)) {jump(y);}
        }
        else {
            DrawText("Press [SPACE] to start", 20, (screenHeight/2)+playerSize+10,30,RED);
            if (IsKeyPressed(KEY_SPACE)) {gameBegin = true;
                                          jump(y);}
            
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(("Y: " + std::to_string(y)).c_str(),0,0,20,GOLD);
        DrawRectangle((screenWidth/2)-(playerSize/2),y,playerSize,playerSize,RED);
        EndDrawing();


    }

    return 0;
}

