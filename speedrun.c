#include <stdlib.h>
#include "include/raylib.h"
#include <stdio.h>

int main(void)
{
    int screenWidth = 250;
    int screenHeight = 135;
     
    InitWindow(screenWidth, screenHeight, "Speedrun Timer");
    InitAudioDevice();
    bool settings_clicked = false;
    float time = 0.f;
    double deltaTime = 0;
    char *timestring = malloc(100);
    Vector2 mousePosition;
    bool should_start = false;
    Music music = LoadMusicStream("resources/Speedrun.mp3");
    Rectangle start = {50,25,50,50};
    Rectangle stop = {100,25,50,50};
    Rectangle restart = {150,25,50,50};
    Rectangle settings = {restart.x+50,10,45,13};
    Rectangle button6 = {50,25,10,10};
                PlayMusicStream(music);
    float GetMiddleX(Rectangle rec, char* Text)
                {           
                    return rec.x + rec.width/2 - MeasureText(Text, 10)/2;
                }
    float GetMiddleY(Rectangle rec, float divide)
                {           
                    return rec.y + rec.height / divide;
                }
    while (!WindowShouldClose())
    {
        deltaTime = GetFrameTime();
        screenHeight = GetScreenHeight();
        screenWidth = GetScreenWidth();
        mousePosition = GetMousePosition();
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition, settings)){
            settings_clicked = !settings_clicked;
            should_start = false;
        }
        if (should_start){
                UpdateMusicStream(music); 
                time += deltaTime;
            }
        sprintf(timestring,"%f",(float)time);
            if (!settings_clicked){
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition, start) || IsKeyPressed(KEY_F5))
                {
                    should_start = true;
                }
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition, stop) || IsKeyPressed(KEY_F6))
                {
                    should_start = false;
                }
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition, restart) || IsKeyPressed(KEY_F7))
                {
                    StopMusicStream(music);
                    PlayMusicStream(music);
                
                    time = 0;
                    should_start = false;
                }
                BeginDrawing();
                    ClearBackground(BLACK);
                    DrawRectangleRec(start,GREEN);
                    DrawRectangleRec(stop,RED);
                    DrawRectangleRec(restart,BLUE);
                    DrawRectangleRec(settings,GRAY);
                    DrawText(timestring, start.x, screenHeight - 50, 40, RAYWHITE);
                    DrawText("Start", GetMiddleX(start, "Start"), GetMiddleY(start,3), 10, BLACK);
                    DrawText("(F5)", GetMiddleX(start, "(F5)"), GetMiddleY(start,1.75), 10, BLACK);
                    DrawText("Stop", GetMiddleX(stop, "Stop"), GetMiddleY(stop,3), 10, BLACK);
                    DrawText("(F6)", GetMiddleX(stop, "(F6)"), GetMiddleY(stop,1.75), 10, BLACK);
                    DrawText("Reset", GetMiddleX(restart, "Reset"), GetMiddleY(restart,3), 10, BLACK);
                    DrawText("(F7)", GetMiddleX(restart, "(F7)"), GetMiddleY(restart,1.75), 10, BLACK);
                    DrawText("Settings", GetMiddleX(settings, "Settings"), settings.y+2, 10, BLACK);
                EndDrawing();
            }
            if (settings_clicked){
                BeginDrawing();
                    ClearBackground(GRAY);
                    DrawText("Settings",80,10,20,BLACK);
                    DrawRectangleRec(settings,BLACK);
                    DrawText("Back",GetMiddleX(settings,"Back"),settings.y +2 ,10,RAYWHITE);
                EndDrawing();
                
            }
    }
     CloseAudioDevice();
    CloseWindow();
    return 0;
}
