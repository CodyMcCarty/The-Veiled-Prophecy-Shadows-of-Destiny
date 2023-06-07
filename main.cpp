#include <iostream>

#include "raylib.h"
#include "raymath.h"

class SDCharacter
{
 public:
 private:
};

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
  float MoveSpeed{4.0};
  // TODO: make knight or a character struct or class
  Texture2D KnightIdle = LoadTexture("characters/knight_idle_spritesheet.png");
  Texture2D KnightRun = LoadTexture("characters/knight_run_spritesheet.png");
  Texture2D Knight = KnightIdle;
  float KnightScale{4.0};
  Vector2 KnightPos{
      ((float)ViewWidth / 2.0f) -
          KnightScale * (0.5f * (float)Knight.width / 6.0f),
      ((float)ViewHeight / 2.0f) - KnightScale * (.05f * (float)Knight.height)};
  // 1:facing right -1:facing left
  float RightLeft{1.f};  // TODO: make it a bool?
  // animation vars
  float RunningTime{};
  int Frame{};
  const int MaxFrames{6};
  const float UpdateTime{1.f / 12.f};

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
      RightLeft = direction.x < 0.f ? -1.f : 1.f;
      Knight = KnightRun;
    }
    else
    {
      Knight = KnightIdle;
    }

    // Draw Map
    DrawTextureEx(Map, MapPos, 0.0, 4.0, WHITE);

    // Update animation frame
    RunningTime += GetFrameTime();
    if (RunningTime >= UpdateTime)
    {
      Frame++;
      RunningTime = 0.f;
      if (Frame > MaxFrames) Frame = 0;
    }

    // Draw Knight
    Rectangle knightSource{Frame * (float)Knight.width / 6.f, 0.f,
                           RightLeft * (float)Knight.width / 6.f,
                           (float)Knight.height};
    Rectangle knightDest{KnightPos.x, KnightPos.y,
                         (float)Knight.width / 6.f * KnightScale,
                         (float)Knight.height * KnightScale};
    DrawTexturePro(Knight, knightSource, knightDest, Vector2{}, 0.f, WHITE);

    EndDrawing();
  }
  CloseWindow();
}
