#include <raylib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CHARS 128

int returnRandomNumber(int range, int min) {
    return rand() % range + min;
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
    const int randomNumber = returnRandomNumber(4, 0);
    int mistakes = 0; 
    float accuracy; 

    yuno = LoadTexture("./resources/textures/yuno.png");

    SetTargetFPS(10);

    /* Main game loop */
    while(!WindowShouldClose()) {
        // printf("begin loop randomNumber: %i", randomNumber);
        int unikey = GetCharPressed();
        int keypressed = GetKeyPressed();

        // accuracy = (((float)strlen(&source[randomNumber][letterCount]))/mistakes)*100;

        while (unikey > 0) {
            if ((unikey >= 32) && (unikey <= 125) && (letterCount < MAX_CHARS)) {
                text[letterCount] = (char)unikey;
                text[letterCount+1] = '\0';
                letterCount++;
            }

            if (keypressed != source[randomNumber][letterCount]) {
                mistakes++;
                printf("%i\n", unikey);
                printf("%i\n", keypressed);
            }

        unikey = GetCharPressed();
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
        DrawText(text, (int)textBox.x + 5, (int)textBox.y + 8, 30, MAROON);
        // Current sentece rendering
        DrawText(source[randomNumber], 0, 0, 20, MAROON);

        // Debug text
        DrawText(TextFormat("ACCURACY: %i%%", accuracy), 100, 100, 20, MAROON);
        DrawText(TextFormat("Source string length: %i", strlen(source[randomNumber])), 100, 150, 20, MAROON);
        DrawText(TextFormat("Letter count: %i", letterCount), 100, 200, 20, MAROON);
        DrawText(TextFormat("MISTAKES: %i", mistakes), 100, 250, 20, RED);
        DrawText(TextFormat("CURRENT LETTER: %c", source[randomNumber][letterCount]), 100, 300, 20, BLACK);
        // DrawText(TextFormat("CURRENT PRESSED KEY: %c", key), 100, 350, 20, BLUE);

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}

/*
    DEVLOG 2023-03-22

    It would appear that somewhere along the process of calculating the 
    accuracy, something goes horribly wrong. I did check and it is not the fact
    that the randomNumber changes with every single delta time. I have however
    figured out what the getCharPressed() and getKeyPressed() functions return.
    
    The getCharPressed() function returns the unicode of the current key being
    pressed whereas getKeyPressed() returns the keycode itself. (Both of these
    as int)

    I am currently trying to figure out how to go between the characters in the
    strings I have prepared, and the unicode/keycode so that the mistake 
    counter doesn't go up with every single keystroke.
*/