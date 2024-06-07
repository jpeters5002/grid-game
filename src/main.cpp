#include <iostream>
#include <raylib.h>

#include "bouncing_pellet.hpp"
#include "character.hpp"

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
    
    const GridCellIndex grid_dimensions(5, 10);
    const int fps = 60;
    InitWindow(windowWidth, windowHeight, "Game");
    SetTargetFPS(fps);

    BouncingPellet bp(3.0, 9.0, 70.8);
    Character c(GridCellIndex(grid_dimensions.x / 2, grid_dimensions.y - 2), Angle(AngleType::Wind8, Wind8::U));
    
    while(WindowShouldClose() == false)
    {
        BeginDrawing();
        //Updating
        bp.Move(grid_dimensions, fps);
        c.Update(fps);

        //Drawing
        Rectangle border = Rectangle{borderXPos, borderYPos, borderWidth,
            borderHeight};

        ClearBackground(BLACK);
        Draw2DGrid(borderXPos, borderYPos, borderWidth, borderHeight,
            grid_dimensions.x, grid_dimensions.y);
        DrawRectangleLinesEx(border, 3, GREEN);

        bp.Draw(DrawPosition(borderXPos, borderYPos), (float)borderWidth / grid_dimensions.x, (float)borderHeight / grid_dimensions.y);
        c.Draw(DrawPosition(borderXPos, borderYPos), (float)borderWidth / grid_dimensions.x, (float)borderHeight / grid_dimensions.y);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
