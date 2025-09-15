#pragma once

#include "Collider.h"

// Integer
#include <cstdint>

// Vector
#include "Vec2.h"

class CPixelsCollider : public CCollider {
public:
  virtual bool Collides(const CCollider& _rOther) const override;
  virtual bool Collides(const CVec2& _rCirclePos, float _fCircleRadius) const override;
  virtual bool Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const override;
  virtual bool Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const override;

private:
  CVec2 m_vPixelsPos;
  CVec2 m_vPixelsSize;
  const uint8_t* m_pPixels = nullptr;
};