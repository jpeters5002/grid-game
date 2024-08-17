#include <iostream>
#include <raylib.h>

#include "bouncing_pellet.hpp"
#include "character.hpp"
#include "script_handler.hpp"

void Draw2DGrid(int topLeftX, int topLeftY, int width, int height,
    int numCellsX, int numCellsY){
    double cellWidth = (double)width / numCellsX;
    double cellHeight = (double)height / numCellsY;
    
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
    double windowWidth_f {(double)windowWidth};
    double windowHeight_f {(double)windowHeight};
    
    double borderWidth {windowWidth_f / 3};
    double borderHeight {windowHeight_f - 100};
    double borderXPos {(windowWidth_f - borderWidth) / 2};
    double borderYPos {(windowHeight_f - borderHeight) / 2};
    
    const GridCellIndex grid_dimensions(5, 10);
    const int fps = 60;
    InitWindow(windowWidth, windowHeight, "Game");
    SetTargetFPS(fps);

    BouncingPellet bp(3.0, 9.0, 70.8);
    std::string buffer;
    script::ScriptHandler sh(buffer);
    Character c(sh, GridCellIndex(grid_dimensions.x / 2, grid_dimensions.y - 2), Angle(AngleType::Wind8, Wind8::U));

    while(WindowShouldClose() == false)
    {
        while(int userInput = GetKeyPressed())
        {
            switch (userInput) {
                case KEY_BACKSPACE:
                    if(!buffer.empty())
                        buffer.pop_back();
                    break;
                case KEY_F3:
                    c.QueueNextCommand();
                    break;
                default:
                    break;
            }
        }
        if (IsKeyPressedRepeat(KEY_BACKSPACE))
            if (!buffer.empty())
                buffer.pop_back();
        while(int userInput = GetCharPressed())
        {
            buffer.push_back((char)userInput);
        }
        BeginDrawing();
        //Updating
        bp.Move(grid_dimensions, fps);
        c.Update(fps);
        c.Move(grid_dimensions, fps);

        //Drawing
        Rectangle border = Rectangle{(float)borderXPos, (float)borderYPos, (float)borderWidth,
            (float)borderHeight};

        ClearBackground(BLACK);
        Draw2DGrid(borderXPos, borderYPos, borderWidth, borderHeight,
            grid_dimensions.x, grid_dimensions.y);
        DrawRectangleLinesEx(border, 3, GREEN);

        bp.Draw(DrawPosition(borderXPos, borderYPos), (double)borderWidth / grid_dimensions.x, (double)borderHeight / grid_dimensions.y);
        c.Draw(DrawPosition(borderXPos, borderYPos), (double)borderWidth / grid_dimensions.x, (double)borderHeight / grid_dimensions.y);
        DrawText(buffer.c_str(), 0, 0, 24, WHITE);
        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
