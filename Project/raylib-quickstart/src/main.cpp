#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define MAX_RECTS 1000
#define GRID_SIZE 10

typedef struct Rect {
    Vector2 position;

    float width;

    float height;

    Color colour;

} Rect;

int main()
{

    // Initialization

    const int screenWidth = 800;

    const int screenHeight = 600;

    const int paletteWidth = 100;


    InitWindow(screenWidth, screenHeight, "Simple Drawing Package - Rectangle Mode with Eraser");

    // Variables
    Rect rectangles[MAX_RECTS];

    int rectCount = 0;

    Color currentColor = BLACK;  // Default color for drawing rectangles

    bool eraserActive = false;  // Eraser tool toggle

    // Define a simple color palette
    Color palette[] = { BLACK, RED, GREEN, BLUE, YELLOW, ORANGE, PURPLE, MAROON };

    int paletteSize = sizeof(palette) / sizeof(palette[0]);

    int selectedColor = 0;

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        Vector2 mousePosition = GetMousePosition();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            // Snap mouse position to the grid

            float snappedX = (float)((int)mousePosition.x / GRID_SIZE) * GRID_SIZE;
            float snappedY = (float)((int)mousePosition.y / GRID_SIZE) * GRID_SIZE;

            if (mousePosition.x < screenWidth - paletteWidth)
            {
                if (eraserActive)
                {
                    for (int i = 0; i < rectCount; i++)
                    {
                        //initializes rect with the position (x, y) and size of the rectangle stored at index i

                        Rectangle rect = { rectangles[i].position.x, rectangles[i].position.y, rectangles[i].width, rectangles[i].height };

                        if (CheckCollisionPointRec(mousePosition, rect))
                        {
                            // Shift remaining rectangles down to fill the gap

                            for (int j = i; j < rectCount - 1; j++)
                            {
                                rectangles[j] = rectangles[j + 1];
                            }
                            rectCount--;  // Reduce the rectangle count

                            break;  // Exit the loop after erasing
                        }
                    }
                }
                else
                {
                    // Drawing logic: Add a new rectangle
                    bool exists = false;
                    for (int i = 0; i < rectCount; i++)
                    {
                        if (rectangles[i].position.x == snappedX && rectangles[i].position.y == snappedY)
                        {
                            rectangles[i].colour = currentColor;  // Update color if it exists
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
        }

        // Handle palette and eraser selection
        for (int i = 0; i < paletteSize; i++)
        {
            // Position buttons vertically in the color palette area
            Rectangle colorButton = { screenWidth - paletteWidth + 10, 10 + 40 * i, 30, 30 };

            // Draw the button for each color
            if (GuiButton(colorButton, "")) // Detect interaction
            {
                currentColor = palette[i];
                selectedColor = i;
                eraserActive = false;  // Deactivate eraser when a color is selected
            }

            // Highlight the selected color
            if (i == selectedColor && !eraserActive)
            {
                DrawRectangleLinesEx(colorButton, 2, BLACK);  // Draw black border for the selected color
            }
        }

        // Eraser button
        Rectangle eraserButton = { screenWidth - paletteWidth + 10, 10 + 40 * paletteSize, 60, 30 };

        // Detect eraser button interaction
        if (GuiButton(eraserButton, "Eraser"))
        {
            eraserActive = true;
        }

        // Highlight the eraser button if active
        if (eraserActive)
        {
            DrawRectangleLinesEx(eraserButton, 2, RED);
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw the grid

        for (int x = 0; x < screenWidth - paletteWidth; x += GRID_SIZE)
        {
            for (int y = 0; y < screenHeight; y += GRID_SIZE)
            {
                DrawRectangleLines(x, y, GRID_SIZE, GRID_SIZE, LIGHTGRAY);
            }
        }

        // Draw the color palette area on the right

        DrawRectangle(screenWidth - paletteWidth, 0, paletteWidth, screenHeight, LIGHTGRAY);


        for (int i = 0; i < paletteSize; i++)
        {
            Rectangle colorButton = { screenWidth - paletteWidth + 10, 10 + 40 * i, 30, 30 };

            DrawRectangleRec(colorButton, palette[i]);

            if (i == selectedColor && !eraserActive)
            {
                DrawRectangleLinesEx(colorButton, 2, BLACK);
            }
            

        }


        if (eraserActive)
            {
                DrawRectangleLinesEx(eraserButton, 2, RED);  // Highlight eraser button
            }

        DrawRectangleRec(eraserButton, LIGHTGRAY);

        DrawText("Eraser", eraserButton.x + 5, eraserButton.y + 5, 15, BLACK);

        // Draw all stored rectangles

        for (int i = 0; i < rectCount; i++)
        {
            DrawRectangleRec({ rectangles[i].position.x, rectangles[i].position.y, rectangles[i].width, rectangles[i].height }, rectangles[i].colour);
        }

        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}