#include "ball.h"
#include <raylib.h>

Ball::Ball() 
    : x(100)
    , y(100)
    , speedX(12)
    , speedY(12)
    , radius(18) 
{
}

void Ball::Update(int* p1score, int* p2score)
{
    Sound wallBounce = LoadSound("Wall_collsion.wav");
    Sound scorePoint = LoadSound("Goal.wav");
   
    x += speedX;
    y += speedY;
    
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    
    if ((x + radius >= screenWidth)  ) {
        PlaySound(scorePoint);
        (*p1score)++;
        x = screenWidth / 2;
        y = screenHeight / 2;
        return;
        
        
    }
    if(x - radius <= 0) {
        PlaySound(scorePoint);
        (*p2score)++;
        x = screenWidth / 2;
        y = screenHeight / 2;
        return;
        
        
    }
    
    if ((y + radius >= screenHeight) || (y - radius <= 0)) 
    {
        PlaySound(wallBounce);
        speedY *= -1;
     
    }
    if (hitCount >= 10) {
        IncreaseSpeed();
        hitCount = 0; 
    }
}
void Ball::IncreaseSpeed() {
    speedX *= 1.18; 
    speedY *= 1.18;
    return;
    
}

void Ball::Draw() const
{
    DrawCircle(x, y, radius, WHITE);
}