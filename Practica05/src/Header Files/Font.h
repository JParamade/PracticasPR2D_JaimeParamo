#pragma once

// Font
#include "stb_truetype.h" 

// Graphics
#include "litegfx.h"

// Vector
#include "Vec2.h"

class CFont {
protected:
  CFont();
  ~CFont();

public:
  static CFont* Load(const char* _sFilename, float _fHeight);
  float GetHeight() const;
  CVec2 GetTextSize(const char* _sText) const;
  void Draw(const char* _sText, const CVec2& _rPos) const;

private:
  ltex_t* m_pTexture = nullptr;
  unsigned char* m_sAlphaMap;

  float m_fFontHeight;
  CVec2 m_vTextSize;
  
  stbtt_bakedchar m_oCharData[96];
};