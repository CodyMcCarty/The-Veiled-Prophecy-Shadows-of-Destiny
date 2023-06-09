#include "SDCharacter.h"

#include "raymath.h"

SDCharacter::SDCharacter(int viewWidth, int viewHeight)
    : ViewWidth(viewWidth), ViewHeight(viewHeight)
{
  SpriteWidth = Texture.width / MaxFrames;
  SpriteHeight = Texture.height;
}

Vector2 SDCharacter::GetScreenPos()
{
  return Vector2{
      (static_cast<float>(ViewWidth) / 2.0f) - Scale * (0.5f * SpriteWidth),
      (static_cast<float>(ViewHeight) / 2.0f) - Scale * (0.5f * SpriteHeight)};
}

/*
Updated location method.
Location 0,0 is top,left of map and mapSize+mapScale
i.e. ~4000,4000 is bottom,right
*/
Vector2 SDCharacter::GetLocation()
{
  Vector2 pos{WorldPos.x + Scale * (0.5f * SpriteWidth),
              WorldPos.y + Scale * (0.5f * SpriteHeight)};
  return Vector2Add(pos, GetScreenPos());
}

void SDCharacter::Tick(float deltaTime)
{
  if (!GetAlive()) return;

  if (IsKeyDown(KEY_A)) Velocity.x -= 1.0;
  if (IsKeyDown(KEY_D)) Velocity.x += 1.0;
  if (IsKeyDown(KEY_W)) Velocity.y -= 1.0;
  if (IsKeyDown(KEY_S)) Velocity.y += 1.0;
  // TODO: should be normalized right after?
  // TODO: Remove Debug speed
  Speed = IsKeyDown(KEY_LEFT_SHIFT) ? 20.f : 4.f;

  SDBaseCharacter::Tick(deltaTime);

  // draw sword
  Vector2 swordOrigin{};
  Vector2 swordOffset{};
  float swordRotation{};
  if (RightLeft > 0.f)
  {
    swordOrigin = {0.f, Weapon.height * Scale};
    swordOffset = {35.f, 55.f};
    weaponCollision = {GetScreenPos().x + swordOffset.x,
                       GetScreenPos().y + swordOffset.y - Weapon.height * Scale,
                       Weapon.width * Scale, Weapon.height * Scale};
    swordRotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
  }
  else
  {
    swordOrigin = {Weapon.width * Scale, Weapon.height * Scale};
    swordOffset = {25.f, 55.f};
    weaponCollision = {GetScreenPos().x + swordOffset.x - Weapon.width * Scale,
                       GetScreenPos().y + swordOffset.y - Weapon.height * Scale,
                       Weapon.width * Scale, Weapon.height * Scale};
    swordRotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
  }

  Rectangle swordSource{0.f, 0.f, static_cast<float>(Weapon.width) * RightLeft,
                        static_cast<float>(Weapon.height)};
  Rectangle swordDest{GetScreenPos().x + swordOffset.x,
                      GetScreenPos().y + swordOffset.y, Weapon.width * Scale,
                      Weapon.height * Scale};
  DrawTexturePro(Weapon, swordSource, swordDest, swordOrigin, swordRotation,
                 WHITE);

  DrawRectangleLines(weaponCollision.x, weaponCollision.y,
                     weaponCollision.width, weaponCollision.height, RED);
}
