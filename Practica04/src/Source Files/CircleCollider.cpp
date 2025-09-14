#include "../Header Files/CircleCollider.h"

bool CCircleCollider::Collides(const CCollider& _rOther) const {
  return false;
}

bool CCircleCollider::Collides(const CVec2& _rCirclePos, float _fCircleRadius) const {
  return false;
}

bool CCircleCollider::Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const {
  return false;
}

bool CCircleCollider::Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const {
  return false;
}