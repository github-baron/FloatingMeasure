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
#include <iostream>


CDigFloat::CDigFloat()
{
    _Init();
}

CDigFloat::CDigFloat(const CDigFloat& other)
{
    *this = other;
}

CDigFloat::CDigFloat(const DF_VALUE_TYPE Val)
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

CDigFloat& CDigFloat::operator=(const DF_VALUE_TYPE other)
{
    dValue = other;
    dError = DoubleMachineEpsilon(other);
    return *this;
}


bool CDigFloat::operator==(const CDigFloat& other) const
{
//     LOGTRACE("ErrorLogger","Test checking logging");
 
    LOGTRACE(LS_DigFloat+"operatorCompare","called with args:");
    LOGTRACE(LS_DigFloat+"operatorCompare",string("CDigFloat other:"));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("\tvalue            =") + other.RawPrint(20));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("\t                 =") + to_string(other.Precision()));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("\tprecision active =") + Bool2String(other.PrecisionActive()));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("this:") + RawPrint(10));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("\tvalue            =") + RawPrint(20));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("\t                 =") + to_string(Precision()));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("\tprecision active =") + Bool2String(PrecisionActive()));
    
    DF_VALUE_TYPE dTotalError = RawError() + other.RawError();
    LOGTRACE(LS_DigFloat+"operatorCompare",string("calculated total error = ") + Double2String(dTotalError));
    
    // handle precision for other, too
    CDigFloat otherTemp(*this);
    
    // set value to other.Value() 
    otherTemp.Value(other.RawValue());
    
    LOGTRACE(LS_DigFloat+"operatorCompare",string("corrected precision for other: "));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("\tvalue            =") + otherTemp.RawPrint(20));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("\t                 =") + to_string(otherTemp.Precision()));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("\tprecision active =") + Bool2String(otherTemp.PrecisionActive()));
    
    
    LOGTRACE(LS_DigFloat+"operatorCompare",string("comparison of : |diff| <= [precision/2] + totalError"));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("|diff| = " + Double2String(fabs(RawValue()-otherTemp.RawValue()))));
    LOGTRACE(LS_DigFloat+"operatorCompare",string("right side  = " + Double2String(( PrecisionActive() ? PrecisionResolution()/2. : 0) + dTotalError)));
    
    // now compare: take into account: in case of active precision there is also the same error which must be
    // considered for comparison
    return  fabs(RawValue() - otherTemp.RawValue()) <=  ( PrecisionActive() ? PrecisionResolution()/2. : 0) + dTotalError;
}
bool CDigFloat::operator==(const DF_VALUE_TYPE other) const
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
    return !operator==(other);
}
CDigFloat& CDigFloat::operator*=(const CDigFloat& other)
{
    // calculate the error from half the error range
    DF_VALUE_TYPE dErrorCalc = fabs(ValueMaxLimit()*other.ValueMaxLimit()- ValueMinLimit()*other.ValueMinLimit())/2.;

    // now we are ready to calculate the value and calculating the error  by setting the DoubleMachineEpsilon(value)
    (*this) = dValue* other.RawValue();
    
    // now set error to calculated error in case it is larger
    if(dErrorCalc > RawError())
        dError = dErrorCalc;
    
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
    
    // calculate the error from half the error range
    double dErrorHalfRange = fabs((ValueMaxLimit()/other.ValueMinLimit()) - (ValueMinLimit()/other.ValueMaxLimit())) / 2.;
    
    // thats what we origianally wanted to calculate
    (*this) = dValue / other.RawValue();
    
    // now set the error to max. of "half range error" and "DoubleMachineEpsilon(value)"
    if(dError < dErrorHalfRange)
        dError = dErrorHalfRange;
    
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

CDigFloat & CDigFloat::operator*=(const DF_VALUE_TYPE other)
{
    return operator*=(CDigFloat(other));
}

CDigFloat & CDigFloat::operator/=(const DF_VALUE_TYPE other)
{
    return operator/=(CDigFloat(other));
}

CDigFloat & CDigFloat::operator+=(const DF_VALUE_TYPE other)
{
    return operator+=(CDigFloat(other));
}

CDigFloat & CDigFloat::operator-=(const DF_VALUE_TYPE other)
{
    return operator-=(CDigFloat(other));
}

CDigFloat CDigFloat::operator*(const DF_VALUE_TYPE other)
{
    CDigFloat dfResult(*this);
    dfResult*=other;
    return dfResult;

}

CDigFloat CDigFloat::operator/(const DF_VALUE_TYPE other)
{
    CDigFloat dfResult(*this);
    dfResult/=other;
    return dfResult;
}

CDigFloat CDigFloat::operator+(const DF_VALUE_TYPE other)
{
    CDigFloat dfResult(*this);
    dfResult+=other;
    return dfResult;
}

CDigFloat CDigFloat::operator-(const DF_VALUE_TYPE other)
{
    CDigFloat dfResult(*this);
    dfResult-=other;
    return dfResult;
}

void CDigFloat::Value(const DF_VALUE_TYPE Val)
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
    oss << fixed << setprecision((UserPrecision > 0 ) ? UserPrecision : 0 ) << dValue;
    if ( bWithError)
        oss << scientific << plmi  << RawError();
    return oss.str();
}
string CDigFloat::DebugOut() const
{
    ostringstream oss;
    oss << "CDigFloat valid: " << Bool2String(Valid()) << endl
        << "Raw =" <<  RawPrint(DF_RAW_PRINT_PRECISION, true) << endl 
        << "precision (" << Precision() << ") : " << Print() << endl
        << "precision active: " << (PrecisionActive() ? "true" : "false")  << endl 
        << "resolution = " << dPrecisionResolution << endl
        << "rounded value: " << scientific << setprecision(DF_RAW_PRINT_PRECISION) << Round2Precision(dValue,Precision()) << endl 
        << "rounded error: " << scientific << setprecision(DF_RAW_PRINT_PRECISION) << Round2Precision(dError,Precision()) << endl;
        
    return oss.str();
}

    /////////////////////////////////////////////////////
    // external functions for comfortable 
    // use 
    /////////////////////////////////////////////////////
CDigFloat sgn(const CDigFloat& DF)
{
    int nSign = 1;
    if( DF.RawValue() < 0)
        nSign = -1;
    return CDigFloat(nSign);
}
CDigFloat abs(const CDigFloat& DF)
{ 
    CDigFloat dfResult(DF); 
    dfResult = fabs(DF.RawValue()); 
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
    DF_VALUE_TYPE dError;
    // do it for base divisor: take the maximum error from:
    // a) log calculation
    // b) simply setting the base divisor to the value log(base)
    if(dfBase.ValueMinLimit() > 0){
        dError = (logl(dfBase.ValueMaxLimit())-logl(dfBase.ValueMinLimit()))/2.;
        if(dfLogBaseDivisor.Error() < dError)
            dfLogBaseDivisor.dError = dError;
    }
    
    
    // calculate the nat. log of argument:
    dfResult = logl(DF.RawValue());
    
    // calculate the error by half of the error range
    if( DF.ValueMinLimit() > 0)
    {
        // calculate the "half error range" error
        DF_VALUE_TYPE dError = fabs(logl(DF.ValueMaxLimit()) - logl(DF.ValueMinLimit()))/2.;
        
        //  take the max error of "simple value setting" and "half error range"
        if( dfResult.RawError() < dError)
            dfResult.dError = dError;
    
    }
    
    // now turn to base: applying divisor
    dfResult /= dfLogBaseDivisor;
    
    return dfResult;
}


CDigFloat pow(const CDigFloat& dfBase, const CDigFloat& dfExp)
{ 
    CDigFloat dfResult;
    // set value and error (by simply calculating the DoubleMachineEpsilon ( value))
    dfResult = ( pow(dfBase.RawValue(), dfExp.RawValue()));
    
    // calculate the error by the half of the total error range
    DF_VALUE_TYPE dError = (max(max (pow( dfBase.ValueMaxLimit(),dfExp.ValueMaxLimit()), pow(dfBase.ValueMaxLimit(), dfExp.ValueMinLimit())),
                          max (pow( dfBase.ValueMinLimit(),dfExp.ValueMaxLimit()), pow(dfBase.ValueMinLimit(), dfExp.ValueMinLimit()))) -
                      min(min (pow( dfBase.ValueMaxLimit(),dfExp.ValueMaxLimit()), pow(dfBase.ValueMaxLimit(), dfExp.ValueMinLimit())),
                          min (pow( dfBase.ValueMinLimit(),dfExp.ValueMaxLimit()), pow(dfBase.ValueMinLimit(), dfExp.ValueMinLimit())))) / 2.;
    
    // now take the max error of "simple value setting" and "half error range"
    if( dfResult.RawError() < dError)
        dfResult.dError = dError;                    
     
    return dfResult;
}

CDigFloat exp(const CDigFloat& dfExp)
{
    CDigFloat dfResult;
    // set value and error (by simply calculating the DoubleMachineEpsilon ( value))
    dfResult = exp(dfExp.RawValue());
   
    // calculate the error by the half of the total error range
    DF_VALUE_TYPE dError = exp(dfExp.ValueMaxLimit())-exp(dfExp.ValueMinLimit());
                    
    // now take the max error of "simple value setting" and "half error range"
    if( dfResult.RawError() < dError)
        dfResult.dError = dError;                    
     
    return dfResult;
    
}


CDigFloat sqrt(const CDigFloat& DF)
{
    CDigFloat dfResult;
    
    // set value and error (by simply calculating the DoubleMachineEpsilon ( value))
    dfResult = sqrt(DF.RawValue());
    
    // calculate the error by the half of the total error range
    DF_VALUE_TYPE dError = (sqrt(DF.ValueMaxLimit()) - sqrt(DF.ValueMinLimit()))/2.;
    
    // now take the max error of "simple value setting" and "half error range"
    if( dfResult.RawError() < dError)
        dfResult.dError = dError;
    
    return dfResult;
}

CDigFloat max(const CDigFloat& one, const CDigFloat& other)
{
    if(one > other)
        return one;
    else
        return other;
}


CDigFloat min(const CDigFloat& one, const CDigFloat& other)
{
    if(one < other)
        return one;
    else
        return other;
}

CDigFloat operator+(const CDigFloat& One, const CDigFloat& Other)
{
    CDigFloat Result = One;
    Result += Other;
    return Result;    
}

CDigFloat operator-(const CDigFloat& One)
{
    return One*-1;
}

CDigFloat operator-(const CDigFloat& One, const CDigFloat& Other)
{
    CDigFloat Result = One;
    Result -= Other;
    return Result;
}


CDigFloat operator*(const CDigFloat& One, const CDigFloat& Other)
{
    CDigFloat Result = One;
    Result *= Other;
    return Result;
}

CDigFloat operator/(const CDigFloat& One, const CDigFloat& Other)
{
    CDigFloat Result = One;
    Result /= Other;
    return Result;
}
