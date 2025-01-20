#pragma once

#include "litegfx.h"
#include "Vec2.h"

class CSprite {
    typedef void (*CallbackFunc)(CSprite&, float);
public:
    CSprite(const ltex_t* _pTexture, int _iHFrames = 1, int _iVFrames = 1);
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
    float GetCurrentFrame() const;
    void SetCurrentFrame(int _iFrame);

    // Execution Functions
    void Update(float _fDeltaTime);
    void Draw() const;
private:
    const ltex_t* m_pTexture;
    int m_iHFrames, m_iVFrames;
    float m_fCurrentFrame;
    int m_iFps;

    CallbackFunc m_fFunction;
    void* m_pData;

    lblend_t m_eMode;
    float m_fR, m_fG, m_fB, m_fA;

    CVec2 m_vPosition;
    float m_fAngle;
    CVec2 m_vScale;
    CVec2 m_vPivot;
};
