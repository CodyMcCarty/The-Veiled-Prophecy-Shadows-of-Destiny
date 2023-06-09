#pragma once
#include "SDBaseCharacter.h"
#include "raylib.h"

class SDCharacter : public SDBaseCharacter
{
 public:
  SDCharacter(int ResolutionWidth, int ResolutionHeight);
  Vector2 GetLocation();
  virtual Vector2 GetScreenPos() override;
  Rectangle GetWeaponCollision() { return weaponCollision; }
  float GetHealth() const { return Health; }
  void TakeDamage(float damage);
  virtual void Tick(float DeltaTime) override;

 private:
  int ViewWidth{};
  int ViewHeight{};
  Texture2D Weapon{LoadTexture("characters/weapon_sword.png")};
  Rectangle weaponCollision{};
  float Health{100.f};
};
