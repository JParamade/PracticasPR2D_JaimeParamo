#include "../Header Files/RectCollider.h"

// Collision
#include "../Header Files/CollisionChecks.h"

CRectCollider::CRectCollider(const CVec2& _vRectPos, const CVec2& _vRectSize) 
  : m_vRectPos(_vRectPos)
  , m_vRectSize(_vRectSize)
{}

bool CRectCollider::Collides(const CCollider& _rOther) const {
  return _rOther.Collides(m_vRectPos, m_vRectSize);
}

bool CRectCollider::Collides(const CVec2& _rCirclePos, float _fCircleRadius) const {
  return Collision::CheckCircleRect(_rCirclePos, _fCircleRadius, m_vRectPos, m_vRectSize);
}

bool CRectCollider::Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const {
  return Collision::CheckRectRect(_rRectPos, _rRectSize, m_vRectPos, m_vRectSize);
}

bool CRectCollider::Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const {
  return Collision::CheckPixelsRect(_rPixelsPos, _rPixelsSize, _pPixels, m_vRectPos, m_vRectSize);
}