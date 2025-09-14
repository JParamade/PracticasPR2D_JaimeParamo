#pragma once

#include "Collider.h"

class CCircleCollider : public CCollider {
protected:
  virtual bool Collides(const CCollider& _rOther) const override;
  virtual bool Collides(const CVec2& _rCirclePos, float _fCircleRadius) const override;
  virtual bool Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const override;
  virtual bool Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const override;
};