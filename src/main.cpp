#include <raylib.h>
#include "ball.h"
#include "Paddel.h"


int p1score=0,p2score=0;
const Color blue = {92, 149, 247, 255};
const Color bale_white ={255, 255, 255, 75};
const Color red = {240,62,162, 255};
enum GameState { START_SCREEN, SCORE_INPUT, GAMEPLAY ,GAME_OVER};
GameState currentState = START_SCREEN;

int scoreInput = 0;
int letterCount = 0;
int selectedFinalScore = 0;
bool mouseOnText = false;
Rectangle inputBox = { 860, 400, 140, 50 };
Rectangle playButton = {880, 500, 120, 50};

int main() 
{
    int* p1scorePointer = &p1score;
    int* p2scorePointer = &p2score;
    const Color Navy = {11,18,36, 255};

    InitAudioDevice(); 
    InitWindow(1920, 1080, "Pong Game"); 
    const int screenWidth = 1920;
    const int screenHeight = 1080;
    Texture2D startScreenImage = LoadTexture("Pong_horizontal_cover1920.png");

    Sound paddleHit = LoadSound("paddel_collsion.mp3");
    Sound buttonclick = LoadSound("Button.wav");

    Ball ball;
    Paddel Left_Paddel(20,480,KEY_W,KEY_S,blue);   
    Paddel Right_Paddel(1880,480,KEY_UP,KEY_DOWN,red);

    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Navy);

        switch (currentState) {
            case START_SCREEN: {
                DrawTexture(startScreenImage, 0, 0, WHITE);
                int textX = 820; 
                int textY = 870; 
                int textWidth = MeasureText("Start Game", 50); 
                int textHeight = 50; 
                Rectangle startButton = { (float)textX, (float)textY, (float)textWidth, (float)textHeight };
                DrawText("Start Game", textX, textY, 50, WHITE);

                if (CheckCollisionPointRec(GetMousePosition(), startButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    PlaySound(buttonclick);
                    currentState = SCORE_INPUT;
                }
            } break;

            case SCORE_INPUT: {
                DrawText("Enter Final Score:", 750, 300, 30, WHITE);
                mouseOnText = CheckCollisionPointRec(GetMousePosition(), inputBox);
                DrawRectangleRec(inputBox, mouseOnText ? LIGHTGRAY : DARKGRAY);
                DrawText(TextFormat("%i", scoreInput), (int)inputBox.x + 10, (int)inputBox.y + 10, 30, BLACK);

                if (mouseOnText) {
                    int key = GetCharPressed();
                    while (key > 0) {
                        if (key >= '0' && key <= '9') {
                            if (scoreInput < 10) { 
                                scoreInput = scoreInput * 10 + (key - '0');
                            }
                        }
                        key = GetCharPressed();
                    }

                    if (IsKeyPressed(KEY_BACKSPACE)) {
                        scoreInput /= 10;
                    }
                }

                Rectangle playButton = {880, 500, 120, 50};
                DrawText("Play", (int)playButton.x, (int)playButton.y, 40, WHITE);

                if ((CheckCollisionPointRec(GetMousePosition(), playButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))) {
                    if (scoreInput > 0) {
                        PlaySound(buttonclick);
                        selectedFinalScore = scoreInput;
                        currentState = GAMEPLAY;
                    }
                }
            } break;

            case GAMEPLAY: {  
                ball.Update(p1scorePointer, p2scorePointer);
                Left_Paddel.Update();
                Right_Paddel.Update();

                if (CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius, 
                    Rectangle{(float)Left_Paddel.POSx,(float)Left_Paddel.POSy,(float)Left_Paddel.width,(float)Left_Paddel.height })) {
                    PlaySound(paddleHit);
                    ball.hitCount++;
                    ball.speedX *= -1;
                } 
                if (CheckCollisionCircleRec(Vector2{ball.x,ball.y},ball.radius, 
                    Rectangle{(float)Right_Paddel.POSx,(float)Right_Paddel.POSy,(float)Right_Paddel.width,(float)Right_Paddel.height })) 
                {
                    PlaySound(paddleHit);
                    ball.hitCount++;
                    ball.speedX *= -1;
                }

                ClearBackground(Navy);
                DrawCircle(960, 540, 280, bale_white);
                DrawLine(960, 0, 960, 1080, bale_white);    
                DrawText(TextFormat("%i", *p2scorePointer), 1050 ,60, 80, bale_white);  
                DrawText(TextFormat("%i", *p1scorePointer),  830,60, 80, bale_white);  

                Left_Paddel.Draw();
                Right_Paddel.Draw();
                ball.Draw();

                if(p1score == selectedFinalScore || p2score == selectedFinalScore)
                {
                    if (p1score == selectedFinalScore || p2score == selectedFinalScore) 
                    {
                        currentState = GAME_OVER;
                    }
                }
            } break;
            case GAME_OVER: {
                ClearBackground(Navy);
                Left_Paddel.Draw();
                Right_Paddel.Draw();
                DrawCircle(960, 540, 280, bale_white);
                DrawLine(960, 0, 960, 1080, bale_white);
                DrawText(TextFormat("%i", p2score), 1050 ,60, 80, bale_white);  
                DrawText(TextFormat("%i", p1score), 830,60, 80, bale_white);  
            
                if(p2score > p1score) {
                    DrawText("Red Wins!", (screenWidth/2)-250, (screenHeight/2)-50, 110, red);
                } else if (p1score > p2score) {
                    DrawText("Blue Wins!", (screenWidth/2)-270, (screenHeight/2)-50, 110, blue);
                }
            
                DrawText("Press R to Restart", 765, 620, 40, WHITE);
                if (IsKeyPressed(KEY_R)) {
                    currentState = SCORE_INPUT;
                    scoreInput = 0;
                    p1score = 0;
                    p2score = 0;
                }
            } break;   
        }
        EndDrawing();
    }
}
