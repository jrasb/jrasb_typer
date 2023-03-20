#include <raylib.h>
#include <stdlib.h>

#define MAX_CHARS 128

int main(void) {
    const int screenHeight = 720;
    const int screenWidth = 1280;

    Texture2D yuno;
    Rectangle textBox = { 0, 180, 255, 0 } ;

    /* Initialise window and audio */
    InitWindow(screenWidth, screenHeight, "Jrasb Typer");
    InitAudioDevice();

    char text[MAX_CHARS] = "\0";
    int letterCount = 0;

    yuno = LoadTexture("./resources/textures/yuno.png");

    SetTargetFPS(144);

    /* Main game loop */
    while(!WindowShouldClose()) {
        int key = GetCharPressed();

        while (key > 0) {

            if ((key >= 32) && (key <= 125) && (letterCount < MAX_CHARS)) {
                text[letterCount] = (char)key;
                text[letterCount+1] = '\0';
                letterCount++;
            }

            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            text[letterCount] = '\0';
        }

        /* KEY PRESS EVENTS HERE */
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }


        /* Drawing begins here*/
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(yuno, 100, 250, RAYWHITE);

        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawText(text, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
