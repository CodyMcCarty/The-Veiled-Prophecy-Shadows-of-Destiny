#include "raylib.h"

int main()
{
    const char *title = "My Game";
    int viewHeight{720};
    int viewWidth{1280};

    InitWindow(viewWidth, viewHeight, title);
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        EndDrawing();
    }
}