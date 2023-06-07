#include <iostream>

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
  const float MapScale{4.0};
  const float Ocean{50.f * MapScale};

  SDCharacter Knight;
  Knight.SetResolution(ViewWidth, ViewHeight);

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Draw Map
    MapPos = Vector2Scale(Knight.GetWorldPos(), -1.f);
    DrawTextureEx(Map, MapPos, 0.f, MapScale, WHITE);

    Knight.Tick(GetFrameTime());
    // TODO: improve Check map bounds
    if (Knight.GetWorldPos().x + (0.5f * ViewWidth) < Ocean ||
        Knight.GetWorldPos().y + (0.5f * ViewHeight) < Ocean ||
        Knight.GetWorldPos().x + ViewWidth > Map.width * MapScale + Ocean ||
        Knight.GetWorldPos().y + ViewHeight > Map.width * MapScale + Ocean)
    {
      Knight.UndoMovement();
    }
    EndDrawing();
  }
  CloseWindow();
}
