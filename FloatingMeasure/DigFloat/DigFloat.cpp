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
    // I) (a1 + e1) * (a2 + e2)
    // where
    // a1: this->Value(), e1: this->Error()
    // a2: other.Value(), e2: other.Error()
    // the error part is (I) - a1*a2
    // --> etotal = a1*e2 + a2*e1 + e1*e2
    // as e1 is always +- something: every single term can be positive
    // for the calculation of the maximum --> always take the absolute value of each term
    // --> max(etotal) = abs(a1*e2) + abs(a2*e1) + abs(e1*e2)
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
    // subtract a1/a2 from I)
    // --> etotal = (a2*e1 - a1*e2) / (a2 * (a2 + e2) )
    // as e1 is always +- something: every single term can be positive
    // for the calculation of the maximum --> always take the absolute value of each term
    // --> etotal = ( abs(a2*e1) + abs(a1*e2) ) / (abs(a2)*abs(a2-e2))
    dError = (fabs( RawError()*other.RawValue()) + fabs(  RawValue()*other.RawError() )) / 
                  ( fabs(other.RawValue()) * (fabs( other.RawValue()) - fabs(other.RawError()) ) );
     
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
    return RawPrint(PrecisionActive() ? Precision() : DF_DEFAULT_PRINT_PRECISION,bWithError);
}

string CDigFloat::RawPrint(const int UserPrecision,bool bWithError /*= true*/) const
{
    
    ostringstream oss;
    
    // ostringstream cant handle negative precision
    oss << fixed << setprecision((UserPrecision > 0 ) ? UserPrecision : 0 ) << Round2Precision(dValue, Precision());
    if ( bWithError)
        oss << plmi << RawError();
    return oss.str();
}
string CDigFloat::DebugOut()
{
    ostringstream oss;
    oss << "CDigFloat valid: " << Bool2String(Valid()) << endl
        << "Raw =" <<  RawPrint(DF_RAW_PRINT_PRECISION, true) << endl 
        << "precision (" << Precision() << ") : " << Print() << endl
        << "precision active: " << (PrecisionActive() ? "true" : "false")  << endl 
        << "resolution = " << dPrecisionResolution << endl
        << "rounded value: " << setprecision(DF_RAW_PRINT_PRECISION) << Round2Precision(dValue,Precision()) << endl 
        << "rounded error: " << setprecision(DF_RAW_PRINT_PRECISION) << Round2Precision(dError,Precision()) << endl;
        
    return oss.str();
}

    /////////////////////////////////////////////////////
    // external functions for comfortable 
    // use 
    /////////////////////////////////////////////////////
CDigFloat abs(const CDigFloat& DF)
{ 
    CDigFloat dfResult(DF); 
    dfResult.RawValue(fabs(DF.RawValue())); 
    return dfResult;
}

CDigFloat log(const CDigFloat& DF, const CDigFloat& dfBase /*= 0*/)
{ 
    
    CDigFloat dfResult;
    
    // invalid result for:
    // DF < 0 --> log is not defined for negative argument
    // dfBase < 0 --> log is not defined for negative bases
    // dfBase == 1 --> there is only the infinite solution in case for DF == 1, otherwise there is no solution
    //                 both cases cannot be provided as a single value
    if( DF < 0 || dfBase < 0 ||  dfBase == 1)
        return dfResult;
    
    // in case DF == 1 --> return zero
    if( DF == 1 ) 
    {
        dfResult = 0;
        return dfResult;
    }
        
    
    // initalize result by argument
    dfResult = DF;
    
    // default divisor for log base is 1 --> i.e. natural logarithm
    CDigFloat dfLogBaseDivisor(dfBase == 0 ? 1 : logl(dfBase.RawValue()));
    
    // calculate the error for calculating the natural logarithm:
    // difference of the natural logarithm of:
    // min = value - error 
    // max = value + error
    double dError;
    // do it for base divisor: take the maximum error from:
    // a) log calculation
    // b) simply setting the base divisor to the value log(base)
    if(dfBase.ValueMinLimit() > 0){
        dError = logl(dfBase.ValueMaxLimit())-logl(dfBase.ValueMinLimit());
        if(dfLogBaseDivisor.Error() < dError)
            dfLogBaseDivisor.dError = dError;
    }
    
    // do the same for nat log of argument
    // in case the min is < 0 --> Error = myNan
    dfResult = logl(DF.RawValue());
    dError = myNAN;
    if(DF.ValueMinLimit() > 0){
        dError = logl(DF.ValueMaxLimit())-logl(DF.ValueMinLimit());
        if(dfResult.Error() < dError)
            dfResult.dError = dError;
    }
    
    // now turn to base: applying divisor
    dfResult /= dfLogBaseDivisor;
    
    // do not forget to set error to nan in case it could not be calculated
    if( isnan(dError) )
        dfResult.dError = myNAN;
    
    return dfResult;
}


CDigFloat pow(const CDigFloat& dfBase, const CDigFloat& dfExp)
{ 
    CDigFloat dfResult;
    dfResult.RawValue( pow(dfBase.RawValue(), dfExp.RawValue()));
    
    // calculate brute force the maximal error:
    dfResult.dError = max(max (pow( dfBase.ValueMaxLimit(),dfExp.ValueMaxLimit()), pow(dfBase.ValueMaxLimit(), dfExp.ValueMinLimit())),
                          max (pow( dfBase.ValueMinLimit(),dfExp.ValueMaxLimit()), pow(dfBase.ValueMinLimit(), dfExp.ValueMinLimit()))) -
                      min(min (pow( dfBase.ValueMaxLimit(),dfExp.ValueMaxLimit()), pow(dfBase.ValueMaxLimit(), dfExp.ValueMinLimit())),
                          min (pow( dfBase.ValueMinLimit(),dfExp.ValueMaxLimit()), pow(dfBase.ValueMinLimit(), dfExp.ValueMinLimit())));
                    
     
    return dfResult;
}
