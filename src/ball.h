#pragma once

class Ball
{
public:
    Ball();
    void Update(int* p1score, int* p2score);
    void Draw() const;
    float x;
    float y;
    int speedX;
    int speedY;
    int radius;
    int hitCount; 
    void Reset();
    void IncreaseSpeed();
};