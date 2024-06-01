#include <iostream>
#include <raylib.h>

void Draw2DGrid(int topLeftX, int topLeftY, int width, int height,
    int numCellsX, int numCellsY){
    float cellWidth = (float)width / numCellsX;
    float cellHeight = (float)height / numCellsY;
    
    for(int x = 1; x < numCellsX; x++)
    {
        DrawLine(topLeftX + x * cellWidth, topLeftY, topLeftX + x * cellWidth,
            topLeftY + height, WHITE);
    }
    
    for(int y = 1; y < numCellsY; y++)
    {
        DrawLine(topLeftX, topLeftY + y * cellHeight, topLeftX + width,
            topLeftY + y * cellHeight, WHITE);
    }
    //DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color); 
}

int main()
{
    int windowWidth {1920};
    int windowHeight {1080};
    float windowWidth_f {(float)windowWidth};
    float windowHeight_f {(float)windowHeight};
    
    float borderWidth {windowWidth_f / 3};
    float borderHeight {windowHeight_f - 100};
    float borderXPos {(windowWidth_f - borderWidth) / 2};
    float borderYPos {(windowHeight_f - borderHeight) / 2};
    
    InitWindow(windowWidth, windowHeight, "Game");
    SetTargetFPS(60);
    
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        //Updating
        
        //Drawing
        Rectangle border = Rectangle{borderXPos, borderYPos, borderWidth,
            borderHeight};
        
        ClearBackground(BLACK);
        Draw2DGrid(borderXPos, borderYPos, borderWidth, borderHeight,
            5, 10);
        DrawRectangleLinesEx(border, 3, GREEN);
        
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
