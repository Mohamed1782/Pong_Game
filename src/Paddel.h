#pragma once
#include <raylib.h>
class Paddel
{
public:
    Paddel(int x, int y,int up, int down,Color paddleColor ); 
    void Update();
    void Draw() const;

    int POSx;
    int POSy;
    int width;
    int height;
    int speedY;
    int up;
    int down;
    Color paddleColor;
    
};

