#pragma once

#include "Collider.h"

// Vector
#include "Vec2.h"

class CCircleCollider : public CCollider {
public:
  CCircleCollider(const CVec2& _vCirclePos, float _fCircleRadius);
  ~CCircleCollider() = default;

  virtual bool Collides(const CCollider& _rOther) const override;
  virtual bool Collides(const CVec2& _rCirclePos, float _fCircleRadius) const override;
  virtual bool Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const override;
  virtual bool Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const override;

private:
  CVec2 m_vCirclePos;
  float m_fCircleRadius;
};