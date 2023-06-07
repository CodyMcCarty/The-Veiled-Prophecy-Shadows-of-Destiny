#include "raylib.h"

class SDProp
{
 public:
  SDProp(Vector2 worldPos, Texture2D texture);
  void Render(Vector2 knightPos);

 private:
  Texture2D Texture{};
  Vector2 WorldPos{};
  float Scale{4.f};
};
