/*
 * MIT License
 * 
 * Copyright (c) 2020 Michael von Mengershausen
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#include "DigFloat.h"

CDigFloat::CDigFloat()
{
    _Init();
}

CDigFloat::CDigFloat(const CDigFloat& other)
{
    *this = other;
}

CDigFloat::CDigFloat(const double Val)
{
    _Init();
    Value(Val);
}


CDigFloat::~CDigFloat()
{

}

CDigFloat& CDigFloat::operator=(const CDigFloat& other)
{
    dValue = other.RawValue();
    dError = other.RawError();
    Precision(other.Precision());
    PrecisionActive(other.PrecisionActive());    
    return *this;
}

CDigFloat& CDigFloat::operator=(const double other)
{
    dValue = other;
    dError = DoubleMachineEpsilon(other);
    return *this;
}


bool CDigFloat::operator==(const CDigFloat& other) const
{
    double dTotalError = RawError() + other.RawError();
    
    // handle precision for other, too
    CDigFloat otherTemp(*this);
    
    // set value to other.Value() 
    otherTemp.Value(other.RawValue());
    
    // now compare
    return  fabs(Value() - otherTemp.Value()) <=  ( PrecisionActive() ? PrecisionResolution()/2. : dTotalError);
}
bool CDigFloat::operator==(const double other) const
{
    return this->operator==(CDigFloat(other));
}

bool CDigFloat::operator<(const CDigFloat& other) const
{
    // due to the numerical inaccuracy: take care that it is not equal 
    // corresponding to the implementation of operator!=
    return (*this!=other) && (RawValue()<other.RawValue());    
}

bool CDigFloat::operator<=(const CDigFloat& other) const
{ 
    return (*this==other) || (RawValue()<other.RawValue());  
}

bool CDigFloat::operator>=(const CDigFloat& other) const
{
    return (*this==other) || (RawValue()>other.RawValue());
}

bool CDigFloat::operator>(const CDigFloat& other) const
{
    // due to the numerical inaccuracy: take care that it is not equal in 
    // corresponding to the implementation of operator==
    return (*this!=other) && (RawValue()>other.RawValue());
}

bool CDigFloat::operator!=(const CDigFloat& other) const
{
    return !(*this==other);
}
CDigFloat& CDigFloat::operator*=(const CDigFloat& other)
{
    
    // at first calculate the complete error and store it
    dError = fabs(RawValue())*other.RawError() + fabs(other.RawValue())* RawError() + RawError() * other.RawError();

    // now we are ready to calculate the value
    dValue*= other.RawValue();
    
    return *this;    
    
}
CDigFloat & CDigFloat::operator/=(const CDigFloat& other)
{
    // check if non-zero
    if(other.RawValue() == 0)
    {
        dValue = myNAN;
        return *this;
    }
    
    // calculate the error from: 
    // I) (a1 + e1) / (a2 + e2)
    // where
    // a1: this->Value(), e1: this->Error()
    // a2: other.Value(), e2: other.Error()
    // reform I) / a2
    // --> II) (a1/a2 + e1/a2) / (1 + e2/a2)
    // assumption: 1 + e2/a2 ~ 1 --> 1/(1+e2/a2) ~ (1-e2/a2) (polynomial approximation according to Taylor)
    // --> III) (a1/a2 + e1/a2)*(1 - e2/a2)
    // --> IV) a1/a2 + e1/a2*(1 - e2/a2 - e2/a2)
    // setting I) = a1/a2 + etotal
    // yields:
    // etotal = e1/a2*(1 - 2*e2/a2)
    // we want to estimate the worst case: i.e. 2*e2/a2 > 0
    // --> etotal = e1/a2*(1+abs(2*e2/a2)) = e1/a2 * ( 1 + 2*e2 / abs(a2))
    dError = RawError()/other.RawValue()*(1+2*other.RawError()/fabs(other.RawValue()));
    
    // thats what we origianally wanted to calculate
    dValue /= other.RawValue();
    
    return *this;
}
CDigFloat & CDigFloat::operator+=(const CDigFloat& other)
{
    // first calculate the error
    dError += other.RawError();
    
    // now the value
    dValue += other.RawValue();
    
    return *this;
    
}
CDigFloat & CDigFloat::operator-=(const CDigFloat& other)
{   
    // first calculate the error
    dError += other.RawError();
    
    // now the value
    dValue -= other.RawValue();
    
    return *this;    
    
}
CDigFloat CDigFloat::operator*(const CDigFloat& other)
{
    CDigFloat dfResult(*this);
    dfResult*=other;
    return dfResult;
}
CDigFloat CDigFloat::operator+(const CDigFloat& other)
{
    CDigFloat dfResult(*this);
    dfResult+=other;
    return dfResult;
}
CDigFloat CDigFloat::operator-(const CDigFloat& other)
{
    CDigFloat dfResult(*this);
    dfResult-=other;
    return dfResult;
}
CDigFloat CDigFloat::operator/(const CDigFloat& other)
{
    CDigFloat dfResult(*this);
    dfResult/=other;
    return dfResult;
}

CDigFloat & CDigFloat::operator*=(const double other)
{
    return operator*=(CDigFloat(other));
}

CDigFloat & CDigFloat::operator/=(const double other)
{
    return operator/=(CDigFloat(other));
}

CDigFloat & CDigFloat::operator+=(const double other)
{
    return operator+=(CDigFloat(other));
}

CDigFloat & CDigFloat::operator-=(const double other)
{
    return operator-=(CDigFloat(other));
}

CDigFloat CDigFloat::operator*(const double other)
{
    CDigFloat dfResult(*this);
    dfResult*=other;
    return dfResult;

}

CDigFloat CDigFloat::operator/(const double other)
{
    CDigFloat dfResult(*this);
    dfResult/=other;
    return dfResult;
}

CDigFloat CDigFloat::operator+(const double other)
{
    CDigFloat dfResult(*this);
    dfResult+=other;
    return dfResult;
}

CDigFloat CDigFloat::operator-(const double other)
{
    CDigFloat dfResult(*this);
    dfResult-=other;
    return dfResult;
}

void CDigFloat::Value(const double Val)
{   
    dValue = Val;
    dError = DoubleMachineEpsilon(Val);
}

void CDigFloat::_Init()
{
    dError = 0;
    dValue = myNAN;
    Precision(10);
    PrecisionActive(false);
}

string CDigFloat::Print(bool bWithError /*= true*/) const
{
    return RawPrint(Precision(),bWithError);
}

string CDigFloat::RawPrint(const int UserPrecision,bool bWithError /*= true*/) const
{
    
    ostringstream oss;
    oss << fixed << setprecision(UserPrecision) << Value() ;
    if ( bWithError)
        oss << pm << Error();
    return oss.str();
}
string CDigFloat::DebugOut()
{
    ostringstream oss;
    oss << "CDigFloat valid: " << Bool2String(Valid()) << endl
        << "Raw =" <<  RawPrint(20, true) << endl 
        << "precision (" << Precision() << ") : " << Print() << endl
        << "precision active: " << (PrecisionActive() ? "true" : "false")  << endl 
        << "resolution = " << dPrecisionResolution << endl
        << "rounded value: " << setprecision(40) << Round2Precision(dValue,Precision()) << endl 
        << "rounded error: " << setprecision(40) << Round2Precision(dError,Precision()) << endl ;
        
    return oss.str();
}
