// Author: Jad Jason Fuhr 
// Student Number: C00290965

#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
#include "main.h"
#include <iostream>
#include <fstream>

#define MAX_RECTS 1000
#define GRID_SIZE 10

typedef struct Rect {
    Vector2 position;
    float width;
    float height;
    Color colour;
} Rect;

void saveFile(Rect rectangles[MAX_RECTS], const char* filename) {
    std::ofstream file(filename);
    if (!file) return;

    for (int i = 0; i < MAX_RECTS; ++i) {
        file << rectangles[i].width << " " << rectangles[i].height << " ";
        file << rectangles[i].colour.r << " " << rectangles[i].colour.g << " "
            << rectangles[i].colour.b << " " << rectangles[i].colour.a << " ";
        file << rectangles[i].position.x << " " << rectangles[i].position.y << "\n";
    }
}

void loadFile(Rect rectangles[MAX_RECTS], const char* filename) {
    std::ifstream file(filename);
    if (!file) return;

    for (int i = 0; i < MAX_RECTS; ++i) {
        file >> rectangles[i].width >> rectangles[i].height;
        file >> rectangles[i].colour.r >> rectangles[i].colour.g >> rectangles[i].colour.b >> rectangles[i].colour.a;
        file >> rectangles[i].position.x >> rectangles[i].position.y;
    }
}

Rectangle ToRayLibRect(const Rect& rect)
{
    return { rect.position.x, rect.position.y, rect.width, rect.height };
}

void AssignColor(Color& target, const Color& source) {
    target.r = source.r;
    target.g = source.g;
    target.b = source.b;
    target.a = source.a;
}

int main()
{
    const int screenWidth = 800;

    const int screenHeight = 600;

    const int paletteWidth = 100;

    InitWindow(screenWidth, screenHeight, "Pixel Paint Thingy - Jad Fuhr");

    Rect rectangles[MAX_RECTS];

    int rectCount = 0;

    Color currentColor = BLACK;

    bool eraserActive = false;

    bool rectToolActive = false;

    Color palette[] = { BLACK, RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, MAROON };

    int paletteSize = sizeof(palette) / sizeof(palette[0]);

    int selectedColor = 0;

    bool isDragging = false;

    Vector2 dragStart = { 0, 0 };

    Vector2 dragEnd = { 0, 0 };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mousePosition = GetMousePosition();

        int rectIndex = -1;

        if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON))       // right click to access colour picker 
        {
            for (int i = 0; i < MAX_RECTS; i++)
            {
                if (CheckCollisionPointRec(mousePosition, ToRayLibRect(rectangles[i])))     // checks collison on block at mouse pos and calls ToRayLibRect
                {
                    rectIndex = i;
                    break; // Stop checking once a collision is found
                }
            }

            if (rectIndex >= 0)
            {
                AssignColor(currentColor, rectangles[rectIndex].colour);

            }

        }

        // Handle mouse input for 1x1 squares

        if (!rectToolActive && !eraserActive && IsMouseButtonDown(MOUSE_LEFT_BUTTON))           // if rect tool and eraser tool arent active 
        {
            float snappedX = (float)((int)mousePosition.x / GRID_SIZE) * GRID_SIZE;     
            float snappedY = (float)((int)mousePosition.y / GRID_SIZE) * GRID_SIZE;

            if (mousePosition.x < screenWidth - paletteWidth)       // checks if mouse pos is in the grid and not in the palette 
            {
                bool exists = false;

                for (int i = 0; i < rectCount; i++)     
                {
                    if (rectangles[i].position.x == snappedX && rectangles[i].position.y == snappedY)
                    {
                        rectangles[i].colour = currentColor;
                        exists = true;
                        break;
                    }
                }
                if (!exists && rectCount < MAX_RECTS)
                {
                    rectangles[rectCount].position.x = snappedX;
                    rectangles[rectCount].position.y = snappedY;
                    rectangles[rectCount].width = GRID_SIZE;
                    rectangles[rectCount].height = GRID_SIZE;
                    rectangles[rectCount].colour = currentColor;
                    rectCount++;
                }
            }
        }

        // Eraser functionality

        if (eraserActive && IsMouseButtonDown(MOUSE_LEFT_BUTTON))       // eraser is active and left click pressed 
        {
            for (int i = 0; i < rectCount; i++)
            {
                Rectangle rect = { rectangles[i].position.x, rectangles[i].position.y, rectangles[i].width, rectangles[i].height };

                if (CheckCollisionPointRec(mousePosition, rect))
                {
                    // Shift all subsequent rectangles down one position in the array

                    for (int j = i; j < rectCount - 1; j++)
                    {
                        rectangles[j] = rectangles[j + 1];
                    }
                    rectCount--; // Decrease the rectangle count

                    i--;         // Adjust the index to account for the shift
                }
            }
        }




        // Handle drag-and-drop rectangle creation

        if (rectToolActive && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (mousePosition.x < screenWidth - paletteWidth)
            {
                isDragging = true;
                dragStart = Vector2{ (float)((int)mousePosition.x / GRID_SIZE) * GRID_SIZE, (float)((int)mousePosition.y / GRID_SIZE) * GRID_SIZE };
            }
        }

        if (rectToolActive && IsMouseButtonReleased(MOUSE_LEFT_BUTTON) && isDragging)
        {
            dragEnd = Vector2{ (float)((int)mousePosition.x / GRID_SIZE) * GRID_SIZE, (float)((int)mousePosition.y / GRID_SIZE) * GRID_SIZE };

            float rectWidth = fabsf(dragEnd.x - dragStart.x);       // calculates absolut value for the width while dragging 
            float rectHeight = fabsf(dragEnd.y - dragStart.y);      // calculates absolute value for height while dragging 

            if (rectCount < MAX_RECTS)
            {
                rectangles[rectCount].position.x = fminf(dragStart.x, dragEnd.x);       // fminf returns the smaller value of two float values 
                rectangles[rectCount].position.y = fminf(dragStart.y, dragEnd.y);
                rectangles[rectCount].width = rectWidth;
                rectangles[rectCount].height = rectHeight;
                rectangles[rectCount].colour = currentColor;
                rectCount++;
            }

            isDragging = false;
        }

        if (isDragging)
        {
            dragEnd = Vector2{ (float)((int)mousePosition.x / GRID_SIZE) * GRID_SIZE, (float)((int)mousePosition.y / GRID_SIZE) * GRID_SIZE };  // updating the end position (dragEnd) of the drag based on the current mouse position
        }

        // Palette and tool selection

        // Highlighting buttons logic

        Rectangle eraserButton = { screenWidth - paletteWidth + 10, 10 + 40 * paletteSize, 60, 30 };

        Rectangle rectToolButton = { screenWidth - paletteWidth + 10, 10 + 40 * (paletteSize + 1), 60, 30 };

        Rectangle resetGridButton = { screenWidth - paletteWidth + 10, 10 + 40 * (paletteSize + 2),60,30 };

        Rectangle saveButton = { screenWidth - paletteWidth + 10, 10 + 40 * (paletteSize + 3),60,30 };

        Rectangle loadButton = { screenWidth - paletteWidth + 10, 10 + 40 * (paletteSize + 4),60,30 };

        BeginDrawing();
        ClearBackground(RAYWHITE);


        // Drawing color palette and handling color selection

        for (int i = 0; i < paletteSize; i++)
        {
            Rectangle colorButton = { screenWidth - paletteWidth + 10, 10 + 40 * i, 30, 30 };

            if (GuiButton(colorButton, ""))
            {
                currentColor = palette[i];
                selectedColor = i;
                eraserActive = false;
                rectToolActive = false;
            }

            if (i == selectedColor && !eraserActive && !rectToolActive)     // defaults starting colour to black 
            {
                DrawRectangleLinesEx(colorButton, 2, BLACK);
            }
        }

        for (int x = 0; x < screenWidth - paletteWidth; x += GRID_SIZE)
        {
            for (int y = 0; y < screenHeight; y += GRID_SIZE)
            {
                DrawRectangleLines(x, y, GRID_SIZE, GRID_SIZE, LIGHTGRAY);
            }
        }

        DrawRectangle(screenWidth - paletteWidth, 0, paletteWidth, screenHeight, LIGHTGRAY);

        for (int i = 0; i < paletteSize; i++)
        {
            Rectangle colorButton = { screenWidth - paletteWidth + 10, 10 + 40 * i, 30, 30 };
            DrawRectangleRec(colorButton, palette[i]);
            if (i == selectedColor && !eraserActive && !rectToolActive)
            {
                DrawRectangleLinesEx(colorButton, 2, BLACK);
            }
        }

        // eraser button

        if (GuiButton(eraserButton, "Eraser"))
        {
            eraserActive = true;
            rectToolActive = false;
            selectedColor = -1;
        }

        // rectangle button

        if (GuiButton(rectToolButton, "Rectangle"))
        {
            rectToolActive = true;
            eraserActive = false;
            selectedColor = -1;
        }

        // reset grid button

        if (GuiButton(resetGridButton, "Reset"))
        {
            for (int i = 0; i < MAX_RECTS; i++)     // for loop to go throught the rects and reset them all to blank colour if reset is pressed 
            {
                rectangles[i].colour = BLANK;
            }
        }

        // save button 

        if (GuiButton(saveButton, "Save"))
        {
            saveFile(rectangles, "saveFile.txt");       // calls save file function when save button is pressed 
        }

        // load button 

        if (GuiButton(loadButton, "Load"))
        {
            loadFile(rectangles, "saveFile.txt");       // calls load file function when load button is pressed 
        }

        if (eraserActive)       // highlight eraser tool
        {
            DrawRectangleLinesEx(eraserButton, 2, RED);
        }


        if (rectToolActive)     // highlight rect tool 
        {
            DrawRectangleLinesEx(rectToolButton, 2, RED);
        }

        for (int i = 0; i < rectCount; i++)     // draw grid
        {
            
            Rectangle rect = { rectangles[i].position.x, rectangles[i].position.y, rectangles[i].width, rectangles[i].height };

            //Rectangle rect2 = { rectangles[i].position.x, rectangles[i].position.y, rectangles[i].width, rectangles[i].height };

           // Color cellBackground = ((i) % 2 == 0) ? Color{ 220, 220, 220, 255 } : Color{ 180, 180, 180, 255 };  // dark grey background 
            //DrawRectangleRec(rect2, cellBackground);        // draw dark grey cells


            DrawRectangleRec(rect, rectangles[i].colour);
        }

        if (isDragging)
        {
            float previewWidth = fabsf(dragEnd.x - dragStart.x);
            float previewHeight = fabsf(dragEnd.y - dragStart.y);

            DrawRectangleLines(fminf(dragStart.x, dragEnd.x), fminf(dragStart.y, dragEnd.y), previewWidth, previewHeight, currentColor);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}