#include <raylib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CHARS 128

int returnRandomNumber(int range, int min) {
    return rand() % range + min;
}

float calcAndReturnAccuracy(int stringLength, int mistakes) {
    float accuracy = (100 / (stringLength / mistakes));

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

    Texture2D tealBackground;
    Rectangle textBox = { 0, (float)(screenHeight)/2, 255, 0 } ;

    /* Initialise window and audio */
    InitWindow(screenWidth, screenHeight, "Jrasb Typer");
    InitAudioDevice();

    char text[MAX_CHARS + 1] = "\0";
    int letterCount = 0;
    const int randomNumber = returnRandomNumber(4, 0);
    int mistakes = 0; 
    float accuracy; 


    /* TEXTURES */
    // yuno = LoadTexture("./resources/textures/yuno.png");

    /* IMAGES */
    tealBackground = LoadTexture("./resources/backgrounds/tealBackground.png");

    SetTargetFPS(144);

    /* Main game loop */
    while(!WindowShouldClose()) {
        // printf("begin loop randomNumber: %i", randomNumber);
        int unikey = GetCharPressed();
        int keypressed = GetKeyPressed();

    //    accuracy = calcAndReturnAccuracy(strlen(source[randomNumber]), mistakes); 

        while (unikey > 0) {
            if ((unikey >= 32) && (unikey <= 125) && (letterCount < MAX_CHARS)) {
                text[letterCount] = (char)unikey;
                printf("unikey: %c\n", (char)unikey);
                printf("keypressed: %c\n", (char)keypressed);
                text[letterCount+1] = '\0';
                letterCount++;
            }

            if ((char)unikey != source[randomNumber][letterCount - 1]) {
                mistakes++;

            }

            printf("to press key: %c\n", source[randomNumber][letterCount]);

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
        DrawTexture(tealBackground, 0, 0, WHITE);

        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawText(text, (int)textBox.x + 5, (int)textBox.y + 8, 30, MAROON);
        // Current sentece rendering
        DrawText(source[randomNumber], 0, 0, 20, MAROON);

        // Debug text
        DrawText(TextFormat("ACCURACY: %.2lf%%", accuracy), 100, 100, 20, MAROON);
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

/*
    DEVLOG 2023-03-22 12:35

    Figured out how to convert int keycodes/unicodes into characters.
    This was the sole cause of why my mistake counter didnt work properly.
    I am still trying to figure out the proper formula for the accuracy 
    caculation.
*/
