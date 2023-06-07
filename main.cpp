#include "SDCharacter.h"
#include "raylib.h"
#include "raymath.h"

int main()
{
  // TODO: change the name of the exe file
  const char *Title = "The Veiled Prophecy: Shadows of Destiny";
  int ViewHeight{720};
  int ViewWidth{1280};

  InitWindow(ViewWidth, ViewHeight, Title);
  SetTargetFPS(60);

  Texture2D Map = LoadTexture("nature_tileset/WorldMap.png");
  Vector2 MapPos{0.0, 0.0};

  SDCharacter Knight;
  Knight.SetResolution(ViewWidth, ViewHeight);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Draw Map
    MapPos = Vector2Scale(Knight.GetWorldPos(), -1.f);
    DrawTextureEx(Map, MapPos, 0.0, 4.0, WHITE);

    Knight.Tick(GetFrameTime());

    EndDrawing();
  }
  CloseWindow();
}
