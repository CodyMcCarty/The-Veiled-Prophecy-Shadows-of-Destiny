#include "raylib.h"

class SDProp
{
 public:
  SDProp(Vector2 worldPos, Texture2D texture);
  void Render(Vector2 knightPos);

 private:
  Vector2 WorldPos{};
  Texture2D Texture{};
  float Scale{4.f};
};
