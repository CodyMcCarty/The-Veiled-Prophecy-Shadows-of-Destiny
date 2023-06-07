#include <iostream>

#include "raylib.h"
#include "raymath.h"

int main()
{
  const char *Title = "The Veiled Prophecy: Shadows of Destiny";
  int ViewHeight{720};
  int ViewWidth{1280};

  InitWindow(ViewWidth, ViewHeight, Title);
  SetTargetFPS(60);

  Texture2D Map = LoadTexture("nature_tileset/WorldMap.png");
  Vector2 MapPos{0.0, 0.0};
  float MoveSpeed{4.0};
  // TODO: make knight or a character struct or class
  Texture2D Knight = LoadTexture("characters/knight_idle_spritesheet.png");
  float KnightScale{4.0};
  Vector2 KnightPos{
      ((float)ViewWidth / 2.0f) -
          KnightScale * (0.5f * (float)Knight.width / 6.0f),
      ((float)ViewHeight / 2.0f) - KnightScale * (.05f * (float)Knight.height)};

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Update MapPos
    Vector2 direction{};
    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;
    if (Vector2Length(direction) != 0.0)
    {
      MapPos = Vector2Subtract(
          MapPos, Vector2Scale(Vector2Normalize(direction), MoveSpeed));
    }

    // Draw Map
    DrawTextureEx(Map, MapPos, 0.0, 4.0, WHITE);

    // Draw Knight
    Rectangle knightSource{0.f, 0.f, (float)Knight.width / 6.f,
                           (float)Knight.height};
    Rectangle knightDest{KnightPos.x, KnightPos.y,
                         (float)Knight.width / 6.f * KnightScale,
                         (float)Knight.height * KnightScale};
    DrawTexturePro(Knight, knightSource, knightDest, Vector2{}, 0.f, WHITE);

    EndDrawing();
  }
  CloseWindow();
}
