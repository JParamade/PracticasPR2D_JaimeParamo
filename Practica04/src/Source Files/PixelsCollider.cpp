#include "../Header Files/PixelsCollider.h"

bool CPixelsCollider::Collides(const CCollider& _rOther) const {
  return _rOther.Collides(m_vPixelsPos, m_vPixelsSize, m_pPixels);
}

bool CPixelsCollider::Collides(const CVec2& _rCirclePos, float _fCircleRadius) const {
  return false;
}

bool CPixelsCollider::Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const {
  return false;
}

bool CPixelsCollider::Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const {
  return false;
}