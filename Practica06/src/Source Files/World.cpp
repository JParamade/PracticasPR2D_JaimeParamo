#include "../Header Files/World.h"

CWorld::CWorld(float _fClearRed, float _fClearGreen, float _fClearBlue, const ltex_t* _pBack0, const ltex_t* _pBack1, const ltex_t* _pBack2, const ltex_t* _pBack3) 
  : m_fClearRed(_fClearRed)
  , m_fClearGreen(_fClearGreen)
  , m_fClearBlue(_fClearBlue)
{
  m_lLayers[0].m_pBackground = _pBack0;
  m_lLayers[1].m_pBackground = _pBack1;
  m_lLayers[2].m_pBackground = _pBack2;
  m_lLayers[3].m_pBackground = _pBack3;
}

float CWorld::GetClearRed() const {
  return m_fClearRed;
}

float CWorld::GetClearGreen() const {
  return m_fClearGreen;
}

float CWorld::GetClearBlue() const {
  return m_fClearBlue;
}

const ltex_t* CWorld::GetBackground(size_t _iLayer) const {
  return m_lLayers[_iLayer].m_pBackground;
}
 
float CWorld::GetScrollRatio(size_t _iLayer) const {
  return m_lLayers[_iLayer].m_fScrollRatio;
}

void CWorld::SetScrollRatio(size_t _iLayer, float _fRatio) {
  m_lLayers[_iLayer].m_fScrollRatio = _fRatio;
}

const CVec2& CWorld::GetScrollSpeed(size_t _iLayer) const {
  return m_lLayers[_iLayer].m_vScrollSpeed;
}

void CWorld::SetScrollSpeed(size_t _iLayer, const CVec2& _rSpeed) {
  m_lLayers[_iLayer].m_vScrollSpeed = _rSpeed;
}

const CVec2& CWorld::GetCameraPosition() const {
  return m_vCameraPosition;
}

void CWorld::SetCameraPosition(const CVec2& _rPos) {
  m_vCameraPosition = _rPos;
}

void CWorld::AddSprite(CSprite& _rSprite) {

}

void CWorld::RemoveSprite(CSprite& _rSprite) {

}

void CWorld::Update(float _fDeltaTime) {

}

void CWorld::Draw(const CVec2& _rScreenSize) {

}