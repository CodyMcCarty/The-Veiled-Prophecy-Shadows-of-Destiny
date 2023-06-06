#include "raylib.h"

int main()
{
    const char *title = "The Veiled Prophecy: Shadows of Destiny";
    int viewHeight{720};
    int viewWidth{1280};

    InitWindow(viewWidth, viewHeight, title);
    SetTargetFPS(60);

    Texture2D map = LoadTexture("nature_tileset/WorldMap.png");
    Vector2 mapPos{0.0, 0.0};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y += 1.0;
        if (IsKeyDown(KEY_S)) direction.y -= 1.0;

        DrawTextureEx(map, mapPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    CloseWindow();
}
