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

#include "FloatingMeasure.h"

CFloatingMeasure::CFloatingMeasure()
{
    _Init();
}

CFloatingMeasure::CFloatingMeasure(const CFloatingMeasure& other)
{
    _Init();
    Floating(other.Floating());
    Measure(other.Measure());
    _Precision(other.pfmPrecision);
}

CFloatingMeasure::CFloatingMeasure(const CDigFloat& OtherFloating, const CComplexMeasure& OtherMeasure)
{
    _Init();
    Floating(OtherFloating);
    Measure(OtherMeasure);
}
CFloatingMeasure::~CFloatingMeasure()
{
    SecureDeleteObjectPointer(pfmPrecision);
}

CFloatingMeasure& CFloatingMeasure::operator=(const CFloatingMeasure& other)
{
    Floating(other.Floating());
    Measure(other.Measure());
    _Precision(other.pfmPrecision);
    return *this;
    
}

bool CFloatingMeasure::operator==(const CFloatingMeasure& other) const
{
    // copy this and scale to other
    CFloatingMeasure tmpThis(*this);
    tmpThis.ScaleTo(other);
    
    // compare other and tmpthis
    return  tmpThis.Measure() == other.Measure() && 
            tmpThis.Floating() == other.Floating();
}

bool CFloatingMeasure::operator!=(const CFloatingMeasure& other) const
{
    return !(*this == other);
}
bool CFloatingMeasure::operator<(const CFloatingMeasure& other) const
{
    CFloatingMeasure Tempthis(*this);
    Tempthis.ScaleTo(other);
    return Tempthis.Floating() < other.Floating();
}

bool CFloatingMeasure::operator<=(const CFloatingMeasure& other) const
{
    CFloatingMeasure Tempthis(*this);
    Tempthis.ScaleTo(other);
    return Tempthis.Floating() <= other.Floating();
}

bool CFloatingMeasure::operator>=(const CFloatingMeasure& other) const
{
    CFloatingMeasure Tempthis(*this);
    Tempthis.ScaleTo(other);
    return Tempthis.Floating() >= other.Floating();
}

bool CFloatingMeasure::operator>(const CFloatingMeasure& other) const
{
    CFloatingMeasure Tempthis(*this);
    Tempthis.ScaleTo(other);
    return Tempthis.Floating() > other.Floating();
}

CFloatingMeasure& CFloatingMeasure::operator+=(const CFloatingMeasure& other)
{
    // in case of incompatibility --> make this invalid
    if(!Compatible(other) )
    {
        _Init();
        return *this;
    }
    
    // now we have Compatible measures: the order of the left CFloatingMeasure will be taken (i.e. this)
    CFloatingMeasure tmpOther(other);
    tmpOther.ScaleTo(*this);
    dfFloating += tmpOther.Floating();
    return *this;
    
}
CFloatingMeasure& CFloatingMeasure::operator-=(const CFloatingMeasure& other)
{
    // in case of incompatibility --> make this invalid
    if(!Compatible(other) )
    {
        _Init();
        return *this;
    }
    
    // now we have Compatible measures: the order of the left CFloatingMeasure will be taken (i.e. this)
    CFloatingMeasure tmpOther(other);
    tmpOther.ScaleTo(*this);
    dfFloating -= tmpOther.Floating();
    return *this;
    
    
}
CFloatingMeasure & CFloatingMeasure::operator*=(const CFloatingMeasure& other)
{
    cmMeasure *= other.Measure();
    dfFloating *= other.Floating() * cmMeasure.ReleaseExp10AndFactor();
    return *this;
}

CFloatingMeasure & CFloatingMeasure::operator/=(const CFloatingMeasure& other)
{
    cmMeasure /= other.Measure();
    dfFloating /= (other.Floating() * cmMeasure.ReleaseExp10AndFactor());
    return *this;
}

CFloatingMeasure CFloatingMeasure::operator+(const CFloatingMeasure& other)
{
    CFloatingMeasure Result(*this);
    Result+=other;
    return Result;
}

CFloatingMeasure CFloatingMeasure::operator-(const CFloatingMeasure& other)
{
    CFloatingMeasure Result(*this);
    Result-=other;
    return Result;
}

CFloatingMeasure CFloatingMeasure::operator*(const CFloatingMeasure& other)
{
    CFloatingMeasure Result(*this);
    Result*=other;
    return Result;
}

CFloatingMeasure CFloatingMeasure::operator/(const CFloatingMeasure& other)
{
    CFloatingMeasure Result(*this);
    Result/=other;
    return Result;
}

CFloatingMeasure& CFloatingMeasure::operator*=(const double& other)
{
    dfFloating*=other;
    return *this;
}

CFloatingMeasure& CFloatingMeasure::operator/=(const double& other)
{
    dfFloating/=other;
    return *this;
}

CFloatingMeasure CFloatingMeasure::operator*(const double& other)
{
    CFloatingMeasure result(*this);
    result*=other;
    return result;
}

CFloatingMeasure CFloatingMeasure::operator/(const double& other)
{
    CFloatingMeasure result(*this);
    result/=other;
    return result;
}

void CFloatingMeasure::Normalize()
{
    cmMeasure.Normalize();
    dfFloating *= cmMeasure.ReleaseExp10AndFactor();
}

void CFloatingMeasure::Simplify()
{
    cmMeasure.Simplify();
    dfFloating *= cmMeasure.ReleaseExp10AndFactor();
}

void CFloatingMeasure::ScaleTo(const CFloatingMeasure& other)
{
    if(!Compatible(other))
    {   
        // invalidate content
        _Init();
    }
    else
    {
        cmMeasure.ScaleTo(other.Measure());
        dfFloating *= cmMeasure.ReleaseExp10AndFactor();
    }
    
}
void CFloatingMeasure::ScaleTo(const CComplexMeasure& other)
{
    if(!Compatible(other))
    {   
        // invalidate content
        _Init();
    }
    else
    {
        cmMeasure.ScaleTo(other);
        dfFloating *= cmMeasure.ReleaseExp10AndFactor();
    }

}

void CFloatingMeasure::Measure(const CComplexMeasure& other)
 { 
     // set the measure
     cmMeasure = other;
     
     // rescale the precision, too to the new measure
     _Precision(pfmPrecision);
     
}
void CFloatingMeasure::Precision(const CFloatingMeasure& UserPrecision)
{
    // allocate if necessary
    if( pfmPrecision == nullptr )
        pfmPrecision = new CFloatingMeasure();
    
    // set to precision
    pfmPrecision->operator=(UserPrecision);
    
    // ScaleTo actual measure
    pfmPrecision->ScaleTo(Measure());
    
    // do the following only if the precision has a compatible measure
    // otherwise CFloatingMeasure::ScaleTo will reset *pfmPrecision to invalid values
    // see CFloatingMeasure::_Init()
    if( pfmPrecision->Valid())
    {
        // calculate the resolution in digits
        int nDigits = Floating().Precision();
        double dValueToDeriveDigitsFrom = fabs(pfmPrecision->Floating().RawValue());
        if( dValueToDeriveDigitsFrom > 0 )
            nDigits = (int)(-log(dValueToDeriveDigitsFrom)/log(10.)+0.99999);
        
        // set to new precision
        dfFloating.Precision(nDigits);
    }
}
CFloatingMeasure CFloatingMeasure::Precision() const
{
    CFloatingMeasure Result;
    if( pfmPrecision != nullptr )
        Result = *pfmPrecision;
    return Result;
}

void CFloatingMeasure::_Init()
{
    dfFloating._Init();
    cmMeasure._Init();
    pfmPrecision = nullptr;
}
void CFloatingMeasure::_Precision(const CFloatingMeasure* pOtherPrecision)
{
    // delete own precision
    if(pOtherPrecision == nullptr)
        SecureDeleteObjectPointer(pfmPrecision);
    else
        Precision(*pOtherPrecision);
}


string CFloatingMeasure::PrintShort()
{
    ostringstream oss;
    oss << dfFloating.Print(false) << "*" << cmMeasure.PrintAllShort();
    return oss.str();
}
string CFloatingMeasure::DebugOut()
{
    ostringstream oss;
    oss << "floating measure valid : " << Bool2String(Valid()) << endl
        << "precision fm: " ;
    if(pfmPrecision != nullptr)
        oss << pfmPrecision->PrintShort();
    else
        oss << "unset";
    
    oss << endl << dfFloating.DebugOut() << endl 
                << cmMeasure.DebugOut();
    return oss.str();

}

