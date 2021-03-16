#include <raylib-cpp.hpp>
#include <string>
//#include <iostream>
//using namespace std;

int screenWidth = 854;
int screenHeight = 480;

double deathModifier = 10;
double acceleration = 1;
double timestep = 1;
double time = 0;
double velocity = 0;
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
    time += timestep;
    y += timestep * (velocity + timestep * acceleration / 2);
    velocity += timestep * acceleration;
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
        // Update
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
        DrawText(("Velocity: " + std::to_string(velocity)).c_str(),0,25,20,GOLD);
        DrawRectangle((screenWidth/2)-(playerSize/2),y,playerSize,playerSize,RED);
        EndDrawing();


    }

    return 0;
}

