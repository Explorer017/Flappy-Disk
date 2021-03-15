/*******************************************************************************************
*
*   raylib [text] example - raylib font loading and usage
*
*   NOTE: raylib is distributed with some free to use fonts (even for commercial pourposes!)
*         To view details and credits for those fonts, check raylib license file
*
*   This example has been created using raylib 1.7 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2017 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <vector>

#include "raylib-cpp.hpp"

#define MAX_FONTS   8

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 800;
    int screenHeight = 450;

    raylib::Window w(screenWidth, screenHeight, "raylib [text] example - raylib fonts");
    raylib::Color background(RAYWHITE);
    raylib::Color textColor(DARKGRAY);

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    raylib::Font fonts[MAX_FONTS] = {
        raylib::Font("resources/fonts/alagard.png"),
        raylib::Font("resources/fonts/pixelplay.png"),
        raylib::Font("resources/fonts/mecha.png"),
        raylib::Font("resources/fonts/setback.png"),
        raylib::Font("resources/fonts/romulus.png"),
        raylib::Font("resources/fonts/pixantiqua.png"),
        raylib::Font("resources/fonts/alpha_beta.png"),
        raylib::Font("resources/fonts/jupiter_crash.png")
    };

    std::string messages[MAX_FONTS] = { "ALAGARD FONT designed by Hewett Tsoi",
                                "PIXELPLAY FONT designed by Aleksander Shevchuk",
                                "MECHA FONT designed by Captain Falcon",
                                "SETBACK FONT designed by Brian Kent (AEnigma)",
                                "ROMULUS FONT designed by Hewett Tsoi",
                                "PIXANTIQUA FONT designed by Gerhard Grossmann",
                                "ALPHA_BETA FONT designed by Brian Kent (AEnigma)",
                                "JUPITER_CRASH FONT designed by Brian Kent (AEnigma)" };

    const int spacings[MAX_FONTS] = { 2, 4, 8, 4, 3, 4, 4, 1 };

    Vector2 positions[MAX_FONTS];

    for (int i = 0; i < MAX_FONTS; i++)
    {
        positions[i].x = screenWidth/2 - MeasureTextEx(fonts[i], messages[i].c_str(), fonts[i].baseSize*2, spacings[i]).x/2;
        positions[i].y = 60 + fonts[i].baseSize + 45*i;
    }

    // Small Y position corrections
    positions[3].y += 8;
    positions[4].y += 2;
    positions[7].y -= 8;

    raylib::Color colors[MAX_FONTS] = { MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, LIME, GOLD, RED };
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!w.ShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            background.ClearBackground();

            textColor.DrawText("free fonts included with raylib", 250, 20, 20);
            textColor.DrawLine(220, 50, 590, 50);

            for (int i = 0; i < MAX_FONTS; i++)
            {
                fonts[i].DrawText(messages[i].c_str(), positions[i], fonts[i].baseSize*2, spacings[i], colors[i]);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    //--------------------------------------------------------------------------------------

    return 0;
}
