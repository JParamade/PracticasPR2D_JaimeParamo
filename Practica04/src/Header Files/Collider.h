#pragma once

// Integer
#include <cstdint>

// Vector
class CVec2;

class CCollider {
protected:
  virtual bool Collides(const CCollider& _rOther) const = 0;
  virtual bool Collides(const CVec2& _rCirclePos, float _fCircleRadius) const = 0;
  virtual bool Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const = 0;
  virtual bool Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const = 0;
};