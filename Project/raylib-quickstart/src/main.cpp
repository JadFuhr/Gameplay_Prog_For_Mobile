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

int main()
{
    const int screenWidth = 800;

    const int screenHeight = 600;

    const int paletteWidth = 100;

    InitWindow(screenWidth, screenHeight, "Simple Drawing Package - Drag & Drop Rectangle");

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

        // Handle mouse input for 1x1 squares

        if (!rectToolActive && !eraserActive && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            float snappedX = (float)((int)mousePosition.x / GRID_SIZE) * GRID_SIZE;
            float snappedY = (float)((int)mousePosition.y / GRID_SIZE) * GRID_SIZE;

            if (mousePosition.x < screenWidth - paletteWidth)
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

        if (eraserActive && IsMouseButtonDown(MOUSE_LEFT_BUTTON))
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

            float rectWidth = fabsf(dragEnd.x - dragStart.x);
            float rectHeight = fabsf(dragEnd.y - dragStart.y);

            if (rectCount < MAX_RECTS)
            {
                rectangles[rectCount].position.x = fminf(dragStart.x, dragEnd.x);
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
            dragEnd = Vector2{ (float)((int)mousePosition.x / GRID_SIZE) * GRID_SIZE, (float)((int)mousePosition.y / GRID_SIZE) * GRID_SIZE };
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

            if (i == selectedColor && !eraserActive && !rectToolActive)
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
            for (int i = 0; i < MAX_RECTS; i++)
            {
                rectangles[i].colour = BLANK;
            }
        }

        // save button 

        if (GuiButton(saveButton, "Save"))
        {
            saveFile(rectangles, "saveFile.txt");
        }

        // load button 

        if (GuiButton(loadButton, "Load"))
        {
            loadFile(rectangles, "saveFile.txt");
        }

        if (eraserActive)       // highlight eraser tool
        {
            DrawRectangleLinesEx(eraserButton, 2, RED);
        }


        if (rectToolActive)     // highlight rect tool 
        {
            DrawRectangleLinesEx(rectToolButton, 2, GREEN);
        }

        for (int i = 0; i < rectCount; i++)
        {
            Rectangle rect = { rectangles[i].position.x, rectangles[i].position.y, rectangles[i].width, rectangles[i].height };
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