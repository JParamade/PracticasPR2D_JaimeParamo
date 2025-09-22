#pragma once

#include "Collider.h"

// Vector
#include "Vec2.h"

class CRectCollider : public CCollider {
public:
  CRectCollider(const CVec2& _vRectPos, const CVec2& _vRectSize);
  ~CRectCollider() = default;

  virtual bool Collides(const CCollider& _rOther) const override;
  virtual bool Collides(const CVec2& _rCirclePos, float _fCircleRadius) const override;
  virtual bool Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const override;
  virtual bool Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const override;

private:
  CVec2 m_vRectPos;
  CVec2 m_vRectSize;
};