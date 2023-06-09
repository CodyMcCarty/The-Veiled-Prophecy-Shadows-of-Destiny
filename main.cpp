#include <string>

#include "SDCharacter.h"
#include "SDEnemy.h"
#include "SDProp.h"
#include "raylib.h"
#include "raymath.h"

int main()
{
  // TODO: change the name of the exe file
  const char* Title = "The Veiled Prophecy: Shadows of Destiny";
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

  SDEnemy Goblin01{Vector2{1300.f, 850.f},
                   LoadTexture("characters/goblin_idle_spritesheet.png"),
                   LoadTexture("characters/goblin_run_spritesheet.png")};
  SDEnemy Slime01{Vector2{1900.f, 1250.f},
                  LoadTexture("characters/slime_idle_spritesheet.png"),
                  LoadTexture("characters/slime_run_spritesheet.png")};
  SDEnemy Goblin02{Vector2{1800.f, 1350.f},
                   LoadTexture("characters/goblin_idle_spritesheet.png"),
                   LoadTexture("characters/goblin_run_spritesheet.png")};

  SDEnemy* Enemies[]{&Goblin01, &Goblin02, &Slime01};

  for (SDEnemy* enemy : Enemies)
  {
    enemy->SetTarget(&Knight);
  }

  while (!WindowShouldClose())
  {
    BeginDrawing();
    ClearBackground(WHITE);

    // Draw Map
    MapPos = Vector2Scale(Knight.GetWorldPos(), -1.f);
    DrawTextureEx(Map, MapPos, 0.f, MapScale, WHITE);

    Knight.Tick(GetFrameTime());
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

    // Draw HP or GameOver
    if (!Knight.GetAlive())
    {
      DrawText("Game Over!", 55.f, 45.f, 40, RED);
      EndDrawing();
      continue;
    }
    else
    {
      std::string HP = "Health: ";
      HP.append(std::to_string(Knight.GetHealth()), 0, 2);
      DrawText(HP.c_str(), 55.f, 45.f, 40, RED);
    }

    for (SDEnemy* enemy : Enemies)
    {
      enemy->Tick(GetFrameTime());

      if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
      {
        if (CheckCollisionRecs(enemy->GetCollision(),
                               Knight.GetWeaponCollision()))
        {
          enemy->SetAlive(false);
        }
      }
    }

    EndDrawing();
  }
  CloseWindow();
}
