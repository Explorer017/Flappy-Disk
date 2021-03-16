#include <raylib-cpp.hpp>
#include <string>
#include <ctime>
//#include <iostream>
//using namespace std;

int screenWidth = 854;
int screenHeight = 480;

double deathModifier = 10;
double acceleration = 0.65;
double timestep = 0.1;
double Time= 0;
double velocity = 0;
double deltaTime;
double oldTime = clock();

bool gameBegin = false;

class pipe {
    public:
        int x;
        int height;
        pipe(){
            y = screenHeight-height;
        }
    private:
        int y;
};

double grav(double y) {
    y += timestep * (velocity + timestep * acceleration / 2) * deltaTime;
    velocity += timestep * acceleration * deltaTime;
    if (y <= 0) {
        y = 0;
    }
    else if (y >= ((screenHeight-50)+deathModifier)){
        y = screenHeight/2;
        velocity = 0;
        gameBegin = false;
    }
    return y;
}

void UpdateTime(){
    deltaTime = clock() - oldTime;
    double fps = (1 / deltaTime) * 1000;
    oldTime = clock();
    Time += timestep;
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
    int pipes_on_screen = 0;
    double y = (screenHeight/2)-(playerSize/2);



    // Main game loop
    while (!w.ShouldClose()) // Detect window close button or ESC key
    {
        // Update the time variables used for movement
        UpdateTime();

        // Check if the game has begun
        if (gameBegin) {
            // Gravity
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
        DrawText(("Downwards Velocity: " + std::to_string(velocity)).c_str(),0,25,20,GOLD);
        DrawText(("Time: " + std::to_string(Time)).c_str(),0,50,20,GOLD);
        DrawText(("FPS: " + std::to_string(GetFPS())).c_str(),0,75,20,GOLD);
        DrawRectangle((screenWidth/2)-(playerSize/2),y,playerSize,playerSize,RED);
        EndDrawing();


    }

    return 0;
}

