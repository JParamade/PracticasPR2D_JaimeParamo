#include "../Header Files/PixelsCollider.h"

// Collision
#include "../Header Files/CollisionChecks.h"

CPixelsCollider::CPixelsCollider(const CVec2& _vPixelsPos, const CVec2& _vPixelsSize, const uint8_t* _pPixels) 
  : m_vPixelsPos(_vPixelsPos)
  , m_vPixelsSize(_vPixelsSize)
  , m_pPixels(_pPixels)
{}

bool CPixelsCollider::Collides(const CCollider& _rOther) const {
  return _rOther.Collides(m_vPixelsPos, m_vPixelsSize, m_pPixels);
}

bool CPixelsCollider::Collides(const CVec2& _rCirclePos, float _fCircleRadius) const {
  return Collision::CheckCirclePixels(_rCirclePos, _fCircleRadius, m_vPixelsPos, m_vPixelsSize, m_pPixels);
}

bool CPixelsCollider::Collides(const CVec2& _rRectPos, const CVec2& _rRectSize) const {
  return Collision::CheckPixelsRect(m_vPixelsPos, m_vPixelsSize, m_pPixels, _rRectPos, _rRectSize);
}

bool CPixelsCollider::Collides(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) const {
  return Collision::CheckPixelsPixels(_rPixelsPos, _rPixelsSize, _pPixels, m_vPixelsPos, m_vPixelsSize, m_pPixels);
}