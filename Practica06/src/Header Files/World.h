#pragma once

// Graphics
#include "litegfx.h"

// Sprite
#include "Sprite.h"

// Vector
#include "Vec2.h"

struct SLayer {
  const ltex_t* m_pBackground = nullptr;

  float m_fScrollRatio = 0.f;

  CVec2 m_vScrollSpeed = { 0.f, 0.f };
  CVec2 m_vScrollOffset = { 0.f, 0.f };
};

class CWorld {
public:
  CWorld(
    float _fClearRed = .15f, float _fClearGreen = .15f, float _fClearBlue = .15f,
    const ltex_t* _pBack0 = nullptr, const ltex_t* _pBack1 = nullptr,
    const ltex_t* _pBack2 = nullptr, const ltex_t* _pBack3 = nullptr
  );
  ~CWorld();

  float GetClearRed() const;
  float GetClearGreen() const;
  float GetClearBlue() const;

  const ltex_t* GetBackground(size_t _uLayer) const;

  float GetScrollRatio(size_t _uLayer) const;
  void SetScrollRatio(size_t _uLayer, float _fRatio);
  const CVec2& GetScrollSpeed(size_t _uLayer) const;
  void SetScrollSpeed(size_t _uLayer, const CVec2& _rSpeed);

  const CVec2& GetCameraPosition() const;
  void SetCameraPosition(const CVec2& _rPos);

  void AddSprite(CSprite& _rSprite);
  void RemoveSprite(CSprite& _rSprite);

  void Update(float _fDeltaTime);
  void Draw(const CVec2& _rScreenSize);

private:
  float m_fClearRed;
  float m_fClearGreen;
  float m_fClearBlue;

  SLayer m_lLayers[4];

  CVec2 m_vCameraPosition;

  CSprite** m_lWorldSprites;
  unsigned int m_uSpriteCount;
};