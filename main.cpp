#include "raylib.h"

int main()
{
    const char *title = "The Veiled Prophecy: Shadows of Destiny";
    int viewHeight{720};
    int viewWidth{1280};

    InitWindow(viewWidth, viewHeight, title);
    SetTargetFPS(60);

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 mapPos{0.0, 0.0};
        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    CloseWindow();
}