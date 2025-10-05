#pragma once

// PugiXML
#include "pugixml.hpp"

// Graphics
#include "litegfx.h"

// Sprite
#include "Sprite.h"

// STL
#include <vector>

// Vector
#include "Vec2.h"

struct SLayer {
  const ltex_t* m_pBackground = nullptr;

  float m_fScrollRatio = 0.f;

  CVec2 m_vScrollSpeed = { 0.f, 0.f };
  CVec2 m_vScrollOffset = { 0.f, 0.f };
};

inline std::string ExtractPath(const std::string& _rFilename)
{
  std::string sFilenameCopy = _rFilename;
  while (sFilenameCopy.find("\\") != std::string::npos) sFilenameCopy.replace(sFilenameCopy.find("\\"), 1, "/");
  
  sFilenameCopy = sFilenameCopy.substr(0, sFilenameCopy.rfind('/'));
  if (sFilenameCopy.size() > 0) sFilenameCopy += "/";

  return sFilenameCopy;
}

class CWorld {
public:
  CWorld(
    float _fClearRed = .15f, float _fClearGreen = .15f, float _fClearBlue = .15f,
    const ltex_t* _pBack0 = nullptr, const ltex_t* _pBack1 = nullptr,
    const ltex_t* _pBack2 = nullptr, const ltex_t* _pBack3 = nullptr
  );
  ~CWorld();

  float GetClearRed() const;
  float GetClearGreen() const;
  float GetClearBlue() const;

  const ltex_t* GetBackground(size_t _uLayer) const;

  float GetScrollRatio(size_t _uLayer) const;
  void SetScrollRatio(size_t _uLayer, float _fRatio);
  const CVec2& GetScrollSpeed(size_t _uLayer) const;
  void SetScrollSpeed(size_t _uLayer, const CVec2& _rSpeed);

  const CVec2& GetCameraPosition() const;
  void SetCameraPosition(const CVec2& _rPos);
  void CenterCameraOn(const CVec2& _rTarget, const CVec2& _rScreenSize);

  void AddSprite(CSprite& _rSprite);
  void RemoveSprite(CSprite& _rSprite);

  void Update(float _fDeltaTime);
  void Draw(const CVec2& _rScreenSize);

  bool LoadMap(const char* _sFilename, uint16_t _uFirstColliderId);
  CVec2 GetMapSize() const;

  bool MoveSprite(CSprite& _rSprite, const CVec2& _rAmount);
  bool CheckTileCollision(const CSprite& _rSprite) const;

private:
  // Background Color
  float m_fClearRed;
  float m_fClearGreen;
  float m_fClearBlue;

  // Background Textures
  SLayer m_lLayers[4];

  // Camera
  CVec2 m_vCameraPosition;

  // Sprites
  CSprite** m_lWorldSprites;
  unsigned int m_uSpriteCount;

  // Map
  CVec2 m_vMapSize;
  CVec2 m_vTileSize;
  CVec2 m_vTilesetSize;

  // Tileset
  std::vector<int> m_lTiles;
  CTexture m_oTilesetTexture;
  const ltex_t* m_pTilesetTexture;
};