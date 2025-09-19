#pragma once

// Integer
#include <cstdint>

// Vector
class CVec2;

namespace Collision {
  bool CheckCircleCircle(const CVec2& _rPos1, float _fRadius1, const CVec2& _rPos2, float _fRadius2);
  bool CheckCircleRect(const CVec2& _rCirclePos, float _fCircleRadius, const CVec2& _rRectPos, const CVec2& _rRectSize);
  bool CheckRectRect(const CVec2& _rRectPos1, const CVec2& _rRectSize1, const CVec2& _rRectPos2, const CVec2& _rRectSize2);
  bool CheckCirclePixels(const CVec2& _rCirclePos, float _fCircleRadius, const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels);
  bool CheckPixelsPixels(const CVec2& _rPixelsPos1, const CVec2& _rPixelsSize1, const uint8_t* _pPixels1, const CVec2& _rPixelsPos2, const CVec2& _rPixelsSize2, const uint8_t* _pPixels2);
  bool CheckPixelsRect(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels, const CVec2& _rRectPos, const CVec2& _rRectSize);
}