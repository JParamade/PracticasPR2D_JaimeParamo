#include "../Header Files/CollisionChecks.h"

// Algorithm
#include <algorithm> 

// Math
#include <cmath>     

// Vector
#include "../Header Files/Vec2.h"

namespace Collision {
  bool CheckCircleCircle(const CVec2& _rPos1, float _fRadius1, const CVec2& _rPos2, float _fRadius2) {
    CVec2 vDirection = CVec2(_rPos1.GetX() - _rPos2.GetX(), _rPos1.GetY() - _rPos2.GetY());

    float fSquareDistance = (vDirection.GetX() * vDirection.GetX()) + (vDirection.GetY() * vDirection.GetY());

    float fRadiusSum = _fRadius1 + _fRadius2;

    return fSquareDistance <= fRadiusSum * fRadiusSum;
  }

  bool CheckCircleRect(const CVec2& _rCirclePos, float _fCircleRadius, const CVec2& _rRectPos, const CVec2& _rRectSize) {
    CVec2 vClosestPoint = CVec2(
      std::max(_rRectPos.GetX(), std::min(_rCirclePos.GetX(), _rRectPos.GetX() + _rRectSize.GetX())),
      std::max(_rRectPos.GetY(), std::min(_rCirclePos.GetY(), _rRectPos.GetY() + _rRectSize.GetY()))
    );

    CVec2 vDirection = CVec2(_rCirclePos.GetX() - vClosestPoint.GetX(), _rCirclePos.GetY() - vClosestPoint.GetY());

    float fSquareDistance = (vDirection.GetX() * vDirection.GetX()) + (vDirection.GetY() * vDirection.GetY());

    return fSquareDistance <= _fCircleRadius * _fCircleRadius;
  }

  bool CheckRectRect(const CVec2& _rRectPos1, const CVec2& _rRectSize1, const CVec2& _rRectPos2, const CVec2& _rRectSize2) {
    return !(
        _rRectPos1.GetX() + _rRectSize1.GetX() < _rRectPos2.GetX() ||
        _rRectPos2.GetX() + _rRectSize2.GetX() < _rRectPos1.GetX() ||
        _rRectPos1.GetY() + _rRectSize1.GetY() < _rRectPos2.GetY() ||
        _rRectPos2.GetY() + _rRectSize2.GetY() < _rRectPos1.GetY()
      );
  }

  bool CheckCirclePixels(const CVec2& _rCirclePos, float _fCircleRadius, const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels) {
    for (int iPixelY = 0; iPixelY < static_cast<int>(_rPixelsSize.GetY()); ++iPixelY) {
      for (int iPixelX = 0; iPixelX < static_cast<int>(_rPixelsSize.GetX()); ++iPixelX) {
        uint8_t iAlpha = _pPixels[(iPixelY * static_cast<int>(_rPixelsSize.GetX()) + iPixelX) * 4 + 3];
        if (iAlpha == 0) continue;

        CVec2 vPixelPos = CVec2(_rPixelsPos.GetX() + iPixelX, _rPixelsPos.GetY() + iPixelY);
        CVec2 vDirection = CVec2(vPixelPos.GetX() - _rCirclePos.GetX(), vPixelPos.GetY() - _rCirclePos.GetY());

        float fSquareDistance = (vDirection.GetX() * vDirection.GetX()) + (vDirection.GetY() * vDirection.GetY());

        if (fSquareDistance <= _fCircleRadius * _fCircleRadius) return true;
      }
    }

    return false;
  }

  bool CheckPixelsPixels(const CVec2& _rPixelsPos1, const CVec2& _rPixelsSize1, const uint8_t* _pPixels1, const CVec2& _rPixelsPos2, const CVec2& _rPixelsSize2, const uint8_t* _pPixels2) {
    if (!CheckRectRect(_rPixelsPos1, _rPixelsSize1, _rPixelsPos2, _rPixelsSize2)) return false; 

    float fLeft = std::max(_rPixelsPos1.GetX(), _rPixelsPos2.GetX());
    float fRight = std::min(_rPixelsPos1.GetX() + _rPixelsSize1.GetX(), _rPixelsPos2.GetX() + _rPixelsSize2.GetX());
    float fTop = std::max(_rPixelsPos1.GetY(), _rPixelsPos2.GetY());
    float fBottom = std::min(_rPixelsPos1.GetY() + _rPixelsSize1.GetY(), _rPixelsPos2.GetY() + _rPixelsSize2.GetY());

    for (int iPixelY = static_cast<int>(fTop); iPixelY < static_cast<int>(fBottom); ++iPixelY) {
      for (int iPixelX = static_cast<int>(fLeft); iPixelX < static_cast<int>(fRight); ++iPixelX) {
        int iPixelPosX1 = iPixelX - static_cast<int>(_rPixelsPos1.GetX());
        int iPixelPosY1 = iPixelY - static_cast<int>(_rPixelsPos1.GetY());
        int iPixelPosX2 = iPixelX - static_cast<int>(_rPixelsPos2.GetX());
        int iPixelPosY2 = iPixelY - static_cast<int>(_rPixelsPos2.GetY());

        uint8_t iAlpha1 = _pPixels1[(iPixelPosY1 * static_cast<int>(_rPixelsSize1.GetX()) + iPixelPosX1) * 4 + 3];
        uint8_t iAlpha2 = _pPixels2[(iPixelPosY2 * static_cast<int>(_rPixelsSize2.GetX()) + iPixelPosX2) * 4 + 3];

        if (iAlpha1 != 0 && iAlpha2 != 0) return true;
      }
    }
    
    return false;
  }

  bool CheckPixelsRect(const CVec2& _rPixelsPos, const CVec2& _rPixelsSize, const uint8_t* _pPixels, const CVec2& _rRectPos, const CVec2& _rRectSize) {
    for (int iPixelY = 0; iPixelY < static_cast<int>(_rPixelsSize.GetY()); ++iPixelY) {
      for (int iPixelX = 0; iPixelX < static_cast<int>(_rPixelsSize.GetX()); ++iPixelX) {
        uint8_t iAlpha = _pPixels[(iPixelY * static_cast<int>(_rPixelsSize.GetX()) + iPixelX) * 4 + 3];
        if (iAlpha == 0) continue;

        CVec2 vPixelPos = CVec2(_rPixelsPos.GetX() + iPixelX, _rPixelsPos.GetY() + iPixelY);

        if (vPixelPos.GetX() >= _rRectPos.GetX() && 
            vPixelPos.GetX() <= _rRectPos.GetX() + _rRectSize.GetX() && 
            vPixelPos.GetY() >= _rRectPos.GetY() && 
            vPixelPos.GetY() <= _rRectPos.GetY() + _rRectSize.GetY()) 
          return true;
      }
    }
    
    return false;
  }
}