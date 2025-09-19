#pragma once

// Collision
class CCollider;

// Graphics
#include "litegfx.h"

// Integer
#include <cstdint>

// Vector
#include "Vec2.h"

enum ECollisionType {
  COLLISION_NONE,
  COLLISION_CIRCLE,
  COLLISION_RECT,
  COLLISION_PIXELS
};

class CTexture {
public:
    CTexture(const char* _sFilename);
    ~CTexture();
    
    CTexture(const CTexture&) = delete;
    CTexture& operator=(const CTexture&) = delete;

    CTexture(CTexture&& _rOther) noexcept;
    CTexture& operator=(CTexture&& _rOther) noexcept;
    
    ltex_t* GetTexture() const;

private:
    void LoadTexture(const char* _sFilename);
    ltex_t* m_pTexture = nullptr;
};

class CSprite {
    typedef void (*CallbackFunc)(CSprite&, float);

public:
    CSprite(const ltex_t* _pTexture, int _iHFrames = 1, int _iVFrames = 1);
    ~CSprite();
    
    // Callback
    void SetCallback(CallbackFunc _fFunction);

    // Texture Data
    void SetUserData(void* _pData);
    const ltex_t* GetTexture() const;
    void SetTexture(const ltex_t* _pTexture, int _iHFrames = 1, int _iVFrames = 1);

    // Blending Mode & Color
    lblend_t GetBlend() const;
    void SetBlend(lblend_t _eMode);
    float GetRed() const;
    float GetGreen() const;
    float GetBlue() const;
    float GetAlpha() const;
    void SetColor(float _fR, float _fG, float _fB, float _fA);

    // Transform
    const CVec2& GetPosition() const;
    void SetPosition(const CVec2& _vPos);
    float GetAngle() const;
    void SetAngle(float _fAngle);
    const CVec2& GetScale() const;
    void SetScale(const CVec2& _vScale);
    CVec2 GetSize() const;
    const CVec2& GetPivot() const;
    void SetPivot(const CVec2& _vPivot);

    // Additional Data
    int GetHFrames() const;
    int GetVFrames() const;
    int GetFps() const;
    void SetFps(int _iFps);
    int GetCurrentFrame() const;
    void SetCurrentFrame(int _iFrame);

    // Execution Functions
    void Update(float _fDeltaTime);
    void Draw() const;

    // Collision
    void SetCollisionType(ECollisionType _eType);
    ECollisionType GetCollisionType() const;
    const CCollider* GetCollider() const;
    bool Collides(const CSprite& _rOther) const;

private:
    const ltex_t* m_pTexture;
    int m_iHFrames, m_iVFrames;
    int m_iCurrentFrame;
    float m_fFrameTime;
    int m_iFps;

    CallbackFunc m_fFunction;
    void* m_pData;

    lblend_t m_eMode;
    float m_fR, m_fG, m_fB, m_fA;

    CVec2 m_vPosition;
    float m_fAngle;
    CVec2 m_vScale;
    CVec2 m_vPivot;

    uint8_t* m_pPixelsBuffer = nullptr;

    ECollisionType m_eCollisionType;
    CCollider* m_pCollider;
};
