#include <bits/time.h>
#include <raylib.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CHARS 128

int returnRandomNumber(int range, int min) {
    return rand() % range + min;
}

float calcAndReturnAccuracy(float stringLength, int mistakes) {
    float precisionPercentage = (((stringLength - mistakes) / stringLength) * 100);

    return precisionPercentage;
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
    source[4] = "Lorem ipsum dolor sit amet";
    source[5] = "This is but a mere demo, expect better in the future!";

    Texture2D tealBackground;
    Rectangle textBox = { 0, (float)(screenHeight)/2, 255, 0 } ;

    /* Initialise window and audio */
    InitWindow(screenWidth, screenHeight, "Jrasb Typer");
    InitAudioDevice();
    

    char text[MAX_CHARS + 1] = "\0";
    int letterCount = 0;
    /* Set range to amount of unique lines in source[] */
    const int randomNumber = returnRandomNumber(5, 0);
    int mistakes = 0; 
    float precisionPercentage;
    float frameTime;
    float stopwatch;

    /* load background */
    tealBackground = LoadTexture("./resources/backgrounds/tealBackground.png");

    SetTargetFPS(144);

    /* Main game loop */
    while(!WindowShouldClose()) {
        /* Gets unicode char when key is pressed */
        int unikey = GetCharPressed();
        frameTime = GetFrameTime();
        

        /* Updates precision value every single frame */
        precisionPercentage = calcAndReturnAccuracy(strlen(source[randomNumber]), mistakes);

        if ((letterCount) != strlen(source[randomNumber])) {
            stopwatch += frameTime;

            while (unikey > 0) {
                if ((unikey >= 32) && (unikey <= 125) && (letterCount < MAX_CHARS)) {
                    text[letterCount] = (char)unikey;
                    text[letterCount+1] = '\0';
                    letterCount++;
                }

                if ((char)unikey != source[randomNumber][letterCount - 1]) {
                    mistakes++;
                }

            unikey = GetCharPressed();
            }

            /* Backspace functionality */
            if (IsKeyPressed(KEY_BACKSPACE)) {
                letterCount--;
                if (letterCount < 0) letterCount = 0;
                text[letterCount] = '\0';
            }
        }

        /* KEY PRESS EVENTS HERE */
        if (IsKeyPressed(KEY_F11)) {
            ToggleFullscreen();
        }

        if (IsKeyDown(KEY_R) && IsKeyDown(KEY_LEFT_CONTROL)) {
            main();
            CloseWindow();
        }
        

        /* Drawing begins here*/
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawTexture(tealBackground, 0, 0, WHITE);

        
        // Current sentece rendering
        DrawText(source[randomNumber], (int)textBox.x + 5, (int)textBox.y + 8, 30, LIGHTGRAY);
        
        // Drawing typed text to screen
        DrawRectangleRec(textBox, LIGHTGRAY);
        DrawText(text, (int)textBox.x + 5, (int)textBox.y + 8, 30, DARKGRAY);

        // Debug text
        DrawText("ESC to exit", 0, 0, 20, MAROON);
        DrawText("F11 to fullscreen", screenWidth - 170, 0, 20, MAROON);
        DrawText(TextFormat("TIMER: %f", stopwatch), 100, 150, 20, MAROON);
        DrawText(TextFormat("ACCURACY: %.2lf%%", precisionPercentage), 100, 200, 20, MAROON);
        DrawText(TextFormat("MISTAKES: %i", mistakes), 100, 250, 20, RED);
        if (letterCount == strlen(source[randomNumber])) {
            DrawText("Well done! press Ctrl+R to reload the game!", 100, 400, 30, MAROON);
        }
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

/*
    DEVLOG 2023-03-29

    Figured out how to calculate the accuracy properly and found out why
    it wasn't correctly counting mistakes when counting. Turns out i was
    checking for keycodes, while i should have been using unicodes that get
    returned when using getCharPressed().

    Accuracy has been renamed to precisionPercentage, and has been altered when
    it comes to calculating said percentage:

    P% = (SL - M) / SL * 100%
    where:
        P% = Precision Percentage
        SL = String Length
        M = Mistakes
*/