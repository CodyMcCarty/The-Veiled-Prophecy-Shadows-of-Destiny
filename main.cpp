#include <iostream>

#include "SDCharacter.h"
#include "SDProp.h"
#include "raylib.h"
#include "raymath.h"

int main()
{
  // TODO: change the name of the exe file
  const char *Title = "The Veiled Prophecy: Shadows of Destiny";
  int ViewWidth{1280};
  int ViewHeight{720};

  InitWindow(ViewWidth, ViewHeight, Title);
  SetTargetFPS(60);

  Texture2D Map = LoadTexture("nature_tileset/WorldMap.png");
  Vector2 MapPos{0.0, 0.0};
  const float MapScale{4.0};
  const float Ocean{45.f * MapScale};

  SDCharacter Knight{ViewWidth, ViewHeight};

  SDProp Props[2]{
      SDProp{Vector2{800.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
      SDProp{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Draw Map
    MapPos = Vector2Scale(Knight.GetWorldPos(), -1.f);
    DrawTextureEx(Map, MapPos, 0.f, MapScale, WHITE);

    Knight.Tick(GetFrameTime());
    // if (Knight.GetWorldPos().x + (0.5f * ViewWidth) < Ocean ||
    //     Knight.GetWorldPos().y + (0.5f * ViewHeight) < Ocean ||
    //     Knight.GetWorldPos().x + ViewWidth > Map.width * MapScale + Ocean ||
    //     Knight.GetWorldPos().y + ViewHeight > Map.width * MapScale + Ocean)
    // {
    //   //   Knight.UndoMovement();
    // }
    if (Knight.GetLocation().x < Ocean || Knight.GetLocation().y < Ocean ||
        Knight.GetLocation().x > Map.width * MapScale - Ocean ||
        Knight.GetLocation().y > Map.width * MapScale - Ocean)
    {
      Knight.UndoMovement();
    }

    // Draw Props
    for (SDProp prop : Props)
    {
      prop.Render(Knight.GetWorldPos());
      // check prop collision
      if (CheckCollisionRecs(prop.GetCollision(Knight.GetWorldPos()),
                             Knight.GetCollision()))
      {
        Knight.UndoMovement();
      }
    }

    // Debug Location
    std::cout << Knight.GetLocation().x << " , " << Knight.GetLocation().y
              << std::endl;

    EndDrawing();
  }
  CloseWindow();
}
