#include <iostream>

#include "raylib.h"
#include "raymath.h"

class SDCharacter
{
 public:
  Vector2 GetWorldPos() { return WorldPos; }
  void SetResolution(int Width, int Height);
  void Tick(float DeltaTime);
  void SetScale(float scale) { Scale = scale; }

 private:
  Texture2D Idle{LoadTexture("characters/knight_idle_spritesheet.png")};
  Texture2D Run{LoadTexture("characters/knight_run_spritesheet.png")};
  Texture2D Texture{Idle};
  float Scale{4.f};
  Vector2 ScreenPos{};
  Vector2 WorldPos{};
  // 1:facing right -1:facing left
  float RightLeft{1.f};  // TODO: make it a bool?
  // animation vars
  float RunningTime{};
  int Frame{};
  const int MaxFrames{6};
  const float UpdateTime{1.f / 12.f};
  const float Speed{4.f};
};

void SDCharacter::SetResolution(int Width, int Height)
{
  ScreenPos = {
      ((float)Width / 2.0f) - Scale * (0.5f * (float)Texture.width / 6.0f),
      ((float)Height / 2.0f) - Scale * (.05f * (float)Texture.height)};
}

void SDCharacter::Tick(float DeltaTime)
{
  Vector2 direction{};
  if (IsKeyDown(KEY_A)) direction.x -= 1.0;
  if (IsKeyDown(KEY_D)) direction.x += 1.0;
  if (IsKeyDown(KEY_W)) direction.y -= 1.0;
  if (IsKeyDown(KEY_S)) direction.y += 1.0;
  // TODO: should be normalized right after
  if (Vector2Length(direction) != 0.0)
  {
    WorldPos =
        Vector2Add(WorldPos, Vector2Scale(Vector2Normalize(direction), Speed));
    RightLeft = direction.x < 0.f ? -1.f : 1.f;
    Texture = Run;
  }
  else
  {
    Texture = Idle;
  }

  // Update animation frame
  RunningTime += DeltaTime;
  if (RunningTime >= UpdateTime)
  {
    Frame++;
    RunningTime = 0.f;
    if (Frame > MaxFrames) Frame = 0;
  }

  // Draw Character
  Rectangle Source{Frame * (float)Texture.width / 6.f, 0.f,
                   RightLeft * (float)Texture.width / 6.f,
                   (float)Texture.height};
  Rectangle Dest{ScreenPos.x, ScreenPos.y, (float)Texture.width / 6.f * Scale,
                 (float)Texture.height * Scale};
  DrawTexturePro(Texture, Source, Dest, Vector2{}, 0.f, WHITE);
}

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
