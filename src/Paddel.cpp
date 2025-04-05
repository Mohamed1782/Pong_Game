#include "Paddel.h"
#include <raylib.h>
const int screenWidth = GetScreenWidth();
const int screenHeight = GetScreenHeight();
Paddel::Paddel(int x, int y,int up, int down, Color color) 
    : POSx(x)
    , POSy(y)
    , width(25)
    , height(120)
    , speedY(10)
    , up(up)
    , down(down)
    , paddleColor(color)
{
}
void Paddel::Draw() const
{
    DrawRectangle(POSx, POSy,25,120,  paddleColor);
}
void Paddel::Update() 
{    

    
    if (IsKeyDown(up)) {
        POSy = POSy - speedY;
    }
    if (IsKeyDown(down)) {
        POSy = POSy + speedY;
    }
    if (POSy < 0) {
        POSy = 0;
    }
    if (POSy > 960) {
        POSy = 960;
    }

}
     

