#include "../Header Files/CircleCollider.h"

// Collision
#include "../Header Files/CollisionChecks.h"

CCircleCollider::CCircleCollider(const CVec2& _vCirclePos, float _fCircleRadius)
  : m_vCirclePos(_vCirclePos)
  , m_fCircleRadius(_fCircleRadius)
{}

bool CCircleCollider::Collides(const CCollider& _rOther) const {
  return _rOther.Collides(m_vCirclePos, m_fCircleRadius);
}

bool CCircleCollider::Collides(const CVec2& _rCirclePos, float _fCircleRadius) const {
  return Collision::CheckCircleCircle(_rCirclePos, _fCircleRadius, m_vCirclePos, m_fCircleRadius);
}

bool CCircleCollider::Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const {
  return Collision::CheckCircleRect(m_vCirclePos, m_fCircleRadius, _rRectPos, _rRectSize);
}

bool CCircleCollider::Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const {
  return Collision::CheckCirclePixels(m_vCirclePos, m_fCircleRadius, _rPixelsPos, _rPixelsSize, _pPixels);
}