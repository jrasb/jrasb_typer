#include <raylib.h>
#include <stdlib.h>

char paragraphs[] = {
    "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua."
};

int main(void) {
    const int screenHeight = 720;
    const int screenWidth = 1280;

    Texture2D yuno;

    /* Initialise window and audio */
    InitWindow(screenWidth, screenHeight, "Jrasb Typer");
    InitAudioDevice();

    yuno = LoadTexture("./resources/textures/yuno.png");

    SetTargetFPS(144);

    /* Main game loop */
    while(!WindowShouldClose()) {

        /* KEY PRESS EVENTS HERE */
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        /* Drawing begins here*/
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawTexture(yuno, 0, 0, WHITE);
        
        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
