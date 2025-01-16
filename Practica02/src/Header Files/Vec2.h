#pragma once

class CVec2 {
public:
    // Constructors
    CVec2();
    CVec2(float _fX, float _fY);
    CVec2(const CVec2& _rOther) = default;

    // Arithmetic Operators
    CVec2& operator=(const CVec2& _rOther);
    
    CVec2 operator+(const CVec2& _rOther) const;
    CVec2 operator-(const CVec2& _rOther) const;
    CVec2 operator*(float _fValue) const;
    CVec2 operator/(float _fValue) const;
    
    CVec2& operator+=(const CVec2& _rOther);
    CVec2& operator-=(const CVec2& _rOther);
    CVec2& operator*=(float _fValue);
    CVec2& operator/=(float _fValue);

    // Logic Operators
    bool operator==(const CVec2& _rOther) const;
    bool operator!=(const CVec2& _rOther) const;

    // Methods
    float GetX() const;
    float GetY() const;
    void SetX(float _fValue);
    void SetY(float _fValue);
    
    float Magnitude() const;
    CVec2& Normalize();
    CVec2 Normalized() const;
    CVec2 Abs() const;
    
    float Dot(const CVec2& _rOther) const;
    float Angle(const CVec2& _rOther) const;
    float Distance(const CVec2& _rOther) const;
    
    CVec2& Add(const CVec2& _rOther);
    CVec2& Add(float _fX, float _fY);
    CVec2& Sub(const CVec2& _rOther);
    CVec2& Sub(float _fX, float _fY);
    CVec2& Mul(float _fValue);
    CVec2& Div(float _fValue);
private:
    float m_fX;
    float m_fY;
};
