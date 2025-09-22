#include "../Header Files/World.h"

CWorld::CWorld(float _fClearRed, float _fClearGreen, float _fClearBlue, const ltex_t* _pBack0, const ltex_t* _pBack1, const ltex_t* _pBack2, const ltex_t* _pBack3)
  : m_fClearRed(_fClearRed)
  , m_fClearGreen(_fClearGreen)
  , m_fClearBlue(_fClearBlue)
  , m_lWorldSprites(nullptr)
  , m_uSpriteCount(0)
{
  m_lLayers[0].m_pBackground = _pBack0;
  m_lLayers[1].m_pBackground = _pBack1;
  m_lLayers[2].m_pBackground = _pBack2;
  m_lLayers[3].m_pBackground = _pBack3;
}

CWorld::~CWorld() {
  delete[] m_lWorldSprites;
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

const ltex_t* CWorld::GetBackground(size_t _uLayer) const {
  return m_lLayers[_uLayer].m_pBackground;
}

float CWorld::GetScrollRatio(size_t _uLayer) const {
  return m_lLayers[_uLayer].m_fScrollRatio;
}

void CWorld::SetScrollRatio(size_t _uLayer, float _fRatio) {
  m_lLayers[_uLayer].m_fScrollRatio = _fRatio;
}

const CVec2& CWorld::GetScrollSpeed(size_t _uLayer) const {
  return m_lLayers[_uLayer].m_vScrollSpeed;
}

void CWorld::SetScrollSpeed(size_t _uLayer, const CVec2& _rSpeed) {
  m_lLayers[_uLayer].m_vScrollSpeed = _rSpeed;
}

const CVec2& CWorld::GetCameraPosition() const {
  return m_vCameraPosition;
}

void CWorld::SetCameraPosition(const CVec2& _rPos) {
  m_vCameraPosition = _rPos;
}

void CWorld::AddSprite(CSprite& _rSprite) {
  // Create new array with one more element.
  CSprite** m_lNewArray = new CSprite * [m_uSpriteCount + 1];

  // Copy sprites to the new array.
  for (unsigned int uIndex = 0; uIndex < m_uSpriteCount; ++uIndex) {
    m_lNewArray[uIndex] = m_lWorldSprites[uIndex];
  }

  // Add new sprite to the array.
  m_lNewArray[m_uSpriteCount] = &_rSprite;

  // Clean old array.
  delete[] m_lWorldSprites;

  // Copy sprites to the old array.
  m_lWorldSprites = m_lNewArray;

  // Increment sprite count.
  m_uSpriteCount++;
}

void CWorld::RemoveSprite(CSprite& _rSprite) {
  // If there are no sprites return.
  if (m_uSpriteCount == 0) return;

  // Search the input sprite in the array.
  unsigned int uAuxIndex = m_uSpriteCount;
  for (unsigned int uIndex = 0; uIndex < m_uSpriteCount; ++uIndex) {
    if (m_lWorldSprites[uIndex] == &_rSprite) uAuxIndex = uIndex;
  }

  // If the input sprite is not contained in the array return.
  if (uAuxIndex == m_uSpriteCount) return;

  // Create new array with one less element. 
  CSprite** m_lNewArray = nullptr;
  if (m_uSpriteCount > 1) {
    m_lNewArray = new CSprite * [m_uSpriteCount - 1];

    for (unsigned int uIndex = 0, j = 0; uIndex < m_uSpriteCount; ++uIndex) {
      if (uIndex != uAuxIndex) m_lNewArray[j++] = m_lWorldSprites[uIndex];
    }
  }

  // Clean old array.
  delete[] m_lWorldSprites;

  // Copy sprites to the old array.
  m_lWorldSprites = m_lNewArray;

  // Decrement sprite count.
  m_uSpriteCount--;
}

void CWorld::Update(float _fDeltaTime) {
  // Update background layers.
  for (int uIndex = 0; uIndex < 4; ++uIndex) {
    m_lLayers[uIndex].m_vScrollOffset += m_lLayers[uIndex].m_vScrollSpeed * _fDeltaTime;
  }
  
  // Update all sprites.
  for (unsigned int uIndex = 0; uIndex < m_uSpriteCount; ++uIndex) {
    m_lWorldSprites[uIndex]->Update(_fDeltaTime);
  }
}

void CWorld::Draw(const CVec2& _rScreenSize) {
  // Paint background color.
  lgfx_clearcolorbuffer(m_fClearRed, m_fClearGreen, m_fClearBlue);

  // Draw background sprites.
  for (int i = 0; i < 4; ++i) {
    if (m_lLayers[i].m_pBackground) {
      float fTexOffsetX = m_lLayers[i].m_vScrollOffset.GetX() + m_vCameraPosition.GetX() * m_lLayers[i].m_fScrollRatio;
      float fTexOffsetY = m_lLayers[i].m_vScrollOffset.GetY() + m_vCameraPosition.GetY() * m_lLayers[i].m_fScrollRatio;

      float fCoordU0 = fTexOffsetX / m_lLayers[i].m_pBackground->width;
      float fCoordV0 = fTexOffsetY / m_lLayers[i].m_pBackground->height;
      float fCoordU1 = fCoordU0 + _rScreenSize.GetX() / m_lLayers[i].m_pBackground->width;
      float fCoordV1 = fCoordV0 + _rScreenSize.GetY() / m_lLayers[i].m_pBackground->height;

      ltex_drawrotsized(
        m_lLayers[i].m_pBackground,
        _rScreenSize.GetX() * .5f,
        _rScreenSize.GetY() * .5f,
        0.f,
        .5f, .5f,
        _rScreenSize.GetX(),
        _rScreenSize.GetY(),
        fCoordU0, fCoordV0, fCoordU1, fCoordV1
      );
    }
  }

  // Adjust camera position.
  lgfx_setorigin(-m_vCameraPosition.GetX(), -m_vCameraPosition.GetY());

  // Draw sprites.
  for (unsigned int uIndex = 0; uIndex < m_uSpriteCount; ++uIndex) {
    m_lWorldSprites[uIndex]->Draw();
  }

  // Reset origin.
  lgfx_setorigin(0, 0);
}