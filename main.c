#include <raylib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_CHARS 128

int returnRandomNumber(int range, int min) {
    return rand() % range + min;
}

float calculateAccuracy(float paragraphCharacters, float mistakes) {
    // Accuracy = Characters in paragraph / Mistakes * 100%
    float accuracy = (paragraphCharacters / mistakes) * 100;

    return accuracy;
}

int main(void) {

    // Seeding random number generator
    srand(time(NULL));

    const int screenHeight = 720;
    const int screenWidth = 1280;

    // Sentences to type
    const char *source[128];
    source[0] = "Death to America! And butter sauce!";
    source[1] = "There is no escape from this worst gangster police state";
    source[2] = "Demo typing...";
    source[3] = "The roads of Northern Ireland will run red with the blood of the redcoats";

    Texture2D yuno;
    Rectangle textBox = { 0, (float)(screenHeight)/2, 255, 0 } ;

    /* Initialise window and audio */
    InitWindow(screenWidth, screenHeight, "Jrasb Typer");
    InitAudioDevice();

    char text[MAX_CHARS] = "\0";
    int letterCount = 0;
    int randomNumber = returnRandomNumber(4, 0);
    int mistakes = 0; 
    char accuracy = calculateAccuracy(strlen(source[randomNumber]), mistakes); 

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

                if (key != source[randomNumber][letterCount]) {
                    mistakes++;
                }

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
        DrawTexture(yuno, 100, 250, WHITE);

        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawText(text, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);
        DrawText(source[randomNumber], 0, 0, 20, MAROON);

        // Debug text
        DrawText(TextFormat("ACCURACY: %i%%", accuracy), 100, 100, 20, MAROON);
        DrawText(TextFormat("Source string length: %i", strlen(source[randomNumber])), 100, 150, 20, MAROON);
        DrawText(TextFormat("Letter count: %i", letterCount), 100, 200, 20, MAROON);
        DrawText(TextFormat("MISTAKES: %i", mistakes), 100, 250, 20, RED);
        DrawText(TextFormat("CURRENT LETTER: %c", source[randomNumber][letterCount]), 100, 300, 20, BLACK);

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}
