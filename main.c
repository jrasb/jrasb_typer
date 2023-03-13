#include <raylib.h>
#include <stdlib.h>

int main(void) {
    int screenHeight = 720;
    int screenWidth = 1280;

    Texture2D backgroundImage;

    InitWindow(screenWidth, screenHeight, "Raylib!");

    backgroundImage = LoadTexture("./resources/textures/yuno.png");
    
    SetTargetFPS(144);

    while(!WindowShouldClose()) {
        /*KEY PRESS EVENTS HERE*/
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(backgroundImage, 100, 100, WHITE);
        
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}