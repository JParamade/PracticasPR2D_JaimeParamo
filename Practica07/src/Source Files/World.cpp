#include "../Header Files/World.h"

// Collision
#include "../Header Files/Collider.h"
#include "../Header Files/RectCollider.h"

// Math
#include <cmath>

CWorld::CWorld(float _fClearRed, float _fClearGreen, float _fClearBlue, const ltex_t* _pBack0, const ltex_t* _pBack1, const ltex_t* _pBack2, const ltex_t* _pBack3)
  : m_fClearRed(_fClearRed)
  , m_fClearGreen(_fClearGreen)
  , m_fClearBlue(_fClearBlue)
  , m_lWorldSprites(nullptr)
  , m_uSpriteCount(0)
  , m_vMapSize({ 0.f, 0.f })
  , m_vTileSize({ 0.f, 0.f })
  , m_vTilesetSize({ 0.f, 0.f })
  , m_oTilesetTexture()
  , m_pTilesetTexture(nullptr)
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

void CWorld::CenterCameraOn(const CVec2& _rTarget, const CVec2& _rScreenSize) {
  CVec2 vCameraPosition = _rTarget - _rScreenSize * .5f;

  float fLevelWidth = static_cast<float>(m_lLayers[3].m_pBackground->width);
  float fLevelHeight = static_cast<float>(m_lLayers[3].m_pBackground->height);

  float fMaxX = fLevelWidth - _rScreenSize.GetX();
  float fMaxY = fLevelHeight - _rScreenSize.GetY();

  if (vCameraPosition.GetX() < 0.f) vCameraPosition.SetX(0.f);
  if (vCameraPosition.GetX() > fMaxX) vCameraPosition.SetX(fMaxX);

  if (vCameraPosition.GetY() < 0.f) vCameraPosition.SetY(0.f);
  if (vCameraPosition.GetY() > fMaxY) vCameraPosition.SetY(fMaxY);

  SetCameraPosition(vCameraPosition);
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
  lgfx_setblend(BLEND_ALPHA);

  // Draw background sprites.
  for (int i = 0; i < 4; ++i) {
    if (m_lLayers[i].m_pBackground) {
      CVec2 vOffset = m_lLayers[i].m_vScrollOffset;
      vOffset += m_vCameraPosition * m_lLayers[i].m_fScrollRatio;

      float fCoordU0 = vOffset.GetX() / m_lLayers[i].m_pBackground->width;
      float fCoordV0 = vOffset.GetY() / m_lLayers[i].m_pBackground->height;
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
  lgfx_setorigin(m_vCameraPosition.GetX(), m_vCameraPosition.GetY());

  // Draw map tiles.
  for (int iY = 0; iY < static_cast<int>(m_vMapSize.GetY()); ++iY) {
    for (int iX = 0; iX < static_cast<int>(m_vMapSize.GetX()); ++iX) {
      int iTileId = m_lTiles[iY * m_vMapSize.GetX() + iX];
      if (iTileId > 0) {
        int iTilesetColumns = static_cast<int>(m_vTilesetSize.GetX()) / static_cast<int>(m_vTileSize.GetX());
        int iTilesetRow = (iTileId - 1) / iTilesetColumns;
        int iTilesetColumn = (iTileId - 1) % iTilesetColumns;

        float fCornerPosX = iTilesetColumn * m_vTileSize.GetX();
        float fCornerPosY = iTilesetRow * m_vTileSize.GetY();

        float fPositionX = iX * m_vTileSize.GetX();
        float fPositionY = iY * m_vTileSize.GetY();

        float fCoordU0 = fCornerPosX / m_vTilesetSize.GetX();
        float fCoordV0 = fCornerPosY / m_vTilesetSize.GetY();
        float fCoordU1 = (fCornerPosX + m_vTileSize.GetX()) / m_vTilesetSize.GetX();
        float fCoordV1 = (fCornerPosY + m_vTileSize.GetY()) / m_vTilesetSize.GetY();

        ltex_drawrotsized(
          m_pTilesetTexture, 
          fPositionX + m_vTileSize.GetX() * 0.5f,
          fPositionY + m_vTileSize.GetY() * 0.5f,
          0.f,
          .5f, .5f,
          m_vTileSize.GetX(), m_vTileSize.GetY(), 
          fCoordU0, fCoordV0, fCoordU1, fCoordV1
        );
      }
    }
  }

  // Draw sprites.
  for (unsigned int uIndex = 0; uIndex < m_uSpriteCount; ++uIndex) {
    m_lWorldSprites[uIndex]->Draw();
  }

  // Reset origin.
  lgfx_setorigin(0, 0);
}

bool CWorld::LoadMap(const char* _sFilename, uint16_t _uFirstColliderId) {
  pugi::xml_document oDocument;
  
  pugi::xml_parse_result oResult = oDocument.load_file(_sFilename);
  if (!oResult) {
    static_cast<void>(fprintf(stderr, "Failed to load map: %s.\n", oResult.description()));
    return false;
  }

  pugi::xml_node oMapNode = oDocument.child("map");
  if (!oMapNode) {
    fprintf(stderr, "Invalid TMX file: missing <map>\n");
    return false;
  }

  m_vMapSize = CVec2(oMapNode.attribute("width").as_float(), oMapNode.attribute("height").as_float());
  m_vTileSize = CVec2(oMapNode.attribute("tilewidth").as_float(), oMapNode.attribute("tileheight").as_float());

  pugi::xml_node oTilesetNode = oMapNode.child("tileset");
  if (oTilesetNode) {
    pugi::xml_node oImageNode = oTilesetNode.child("image");
    if (oImageNode) {
      std::string sSource = oImageNode.attribute("source").as_string();

      std::string sBasePath = ExtractPath(_sFilename);
      std::string sTilesetPath = sBasePath + sSource;

      m_oTilesetTexture = CTexture(sTilesetPath.c_str());
      m_pTilesetTexture = m_oTilesetTexture.GetTexture();
      if (!m_pTilesetTexture) {
        fprintf(stderr, "Failed to load tileset texture: %s\n", sTilesetPath.c_str());
        return false;
      }

      m_vTilesetSize = CVec2(oImageNode.attribute("width").as_float(), oImageNode.attribute("height").as_float());
    }
  }

  pugi::xml_node oLayerNode = oMapNode.child("layer");
  if (oLayerNode) {
    pugi::xml_node oDataNode = oLayerNode.child("data");
    if (oDataNode) {
      m_lTiles.reserve(m_vMapSize.GetX() * m_vMapSize.GetY());

      for (pugi::xml_node oTileNode = oDataNode.child("tile"); oTileNode; oTileNode = oTileNode.next_sibling("tile")) {
        int iGID = oTileNode.attribute("gid").as_int();
        m_lTiles.push_back(iGID);
      }
    }
  }

  return true;
}

CVec2 CWorld::GetMapSize() const {
  return CVec2(m_vMapSize.GetX() * m_vTileSize.GetX(), m_vMapSize.GetY() * m_vTileSize.GetY());
}

bool CWorld::MoveSprite(CSprite& _rSprite, const CVec2& _rAmount) {
  bool bCollision = false;

  CVec2 vOldPos = _rSprite.GetPosition();

  _rSprite.SetPosition({ vOldPos.GetX() + _rAmount.GetX(), vOldPos.GetY() });
  if (CheckTileCollision(_rSprite)) {
    _rSprite.SetPosition({ vOldPos.GetX(), _rSprite.GetPosition().GetY() });
    bCollision = true;
  }

  _rSprite.SetPosition({ _rSprite.GetPosition().GetX(), vOldPos.GetY() + _rAmount.GetY() });
  if (CheckTileCollision(_rSprite)) {
    _rSprite.SetPosition({ _rSprite.GetPosition().GetX(), vOldPos.GetY() });
    bCollision = true;
  }

  return bCollision;
}

bool CWorld::CheckTileCollision(const CSprite& _rSprite) const {
  if (!_rSprite.GetCollider()) return false;

  CVec2 vSpriteSize = _rSprite.GetSize();
  CVec2 vSpritePos = _rSprite.GetPosition();

  const CCollider* pSpriteCollider = _rSprite.GetCollider();

  float fLeft = vSpritePos.GetX() - vSpriteSize.GetX() * _rSprite.GetPivot().GetX();
  float fTop = vSpritePos.GetY() - vSpriteSize.GetY() * _rSprite.GetPivot().GetY();
  float fRight = fLeft + vSpriteSize.GetX();
  float fBottom = fTop + vSpriteSize.GetY();

  int iStartX = static_cast<int>(std::floor(fLeft / m_vTileSize.GetX()));
  int iEndX = static_cast<int>(std::floor((fRight - 1) / m_vTileSize.GetX()));
  int iStartY = static_cast<int>(std::floor(fTop / m_vTileSize.GetY()));
  int iEndY = static_cast<int>(std::floor((fBottom - 1) / m_vTileSize.GetY()));

  for (int iIndexY = iStartY; iIndexY <= iEndY; ++iIndexY) {
    for (int iIndexX = iStartX; iIndexX <= iEndX; ++iIndexX) {
      if (iIndexX < 0 || iIndexY < 0 || iIndexX >= m_vMapSize.GetX() || iIndexY >= m_vMapSize.GetY())
        continue;

      int iTileId = m_lTiles[iIndexY * m_vMapSize.GetX() + iIndexX];

      if (iTileId > 0) {
        CVec2 vTilePos(iIndexX * m_vTileSize.GetX(), iIndexY * m_vTileSize.GetY());
        CRectCollider oTileCollider(vTilePos, m_vTileSize);

        if (pSpriteCollider->Collides(oTileCollider)) return true;
      }
    }
  }

  return false;
}