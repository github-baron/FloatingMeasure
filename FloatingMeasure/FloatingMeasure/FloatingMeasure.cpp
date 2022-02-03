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
    dfFloating *= other;
    return *this;
}

CFloatingMeasure& CFloatingMeasure::operator*=(const CComplexMeasure& other)
{
    cmMeasure*= other;
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

bool CFloatingMeasure::Parse(const string& str2Parse, bool bShort)
{
    // init result ... be positive
    bool bSuccess = true;
    
    // now prepare for parsing  1*meas/2/meas*3...
    vector<DF_VALUE_TYPE> vDouble;
    vector<string> vMeasString;
    vector<eOperation> vOperation;
//     char* str=new char[str2Parse.length()];
    string str; str.resize(str2Parse.length());
    memset((void*)str.data(),0,sizeof(char)*str2Parse.length());
    
    // parse all values and the corresponding operators in front of it
    // to generate the double value and remove the corresponding string
    // parts from str2Parse receiving str4Meas which can be parsed by a
    // complex measure class
    size_t tPos = 0;
    unsigned int uiPos = 0;
    string str4Val = str2Parse;
    string str4Meas = "";
    DF_VALUE_TYPE val;
    CComplexMeasure meas;
    eOperation op = eOperation::opUnknown;    
    while(str4Val.length() > 0)
    {    
        
        cout << "parsing " << str4Val << endl << "str4Meas = " << str4Meas << endl << "value(before) = " << to_string(val) << endl;
        
        // for building complex measure string:
        // for the first time add bmNumber if operator exists
        // (when a number preceeds the whole str2Parse) 
        bool bPrependOpMult = false;
        bool bPrependNumber4FirstTime = (str4Meas.length()==0);
        
        try
        {
            // get new value and apply to former value
            switch(op)
            {
                case eOperation::opUnknown:
                    val = STR2DBL(str4Val, &tPos);
                    break;
                case eOperation::opMult:
                    val *= STR2DBL(str4Val, &tPos);
                    break;
                case eOperation::opDivide:
                    val /= STR2DBL(str4Val, &tPos);
                    break;
                
            }
            
            cout << "value (after) = " << to_string(val) << endl;
        }
        catch(exception &e)
        {
            
            cout << "exception part:" << endl;
            // in case the string is already parsed 
            if(str4Val.length() < str2Parse.length())
            {
                cout << "leaving ..." << endl;
                // leave : expected a number
                bSuccess = false;
                break;
            }
            else
            {
                
                cout << "first time: setting to one " << to_string(val) << endl;
                
                // the first number if non is found
                val = 1;
            }
        }        
        
        // remove number part
        str4Val = str4Val.substr(tPos, str4Val.length()-tPos);        
        cout << "removing number part: str4Val = " << str4Val << endl;
        
        // check: do we have to add multiplication operator for the first time:
        uiPos = 0;
        if(bPrependNumber4FirstTime)
            bPrependOpMult = ((eOperation)(OP->Parse(str4Val,uiPos,bShort, eOperation::opUnknown) == eOperation::opUnknown));
        cout << "bPrependOpMult is set to " << Bool2String(bPrependOpMult) << endl;
         
        // search for next number part for next run
        tPos = 0; 
        while(tPos < str4Val.length())
        {
            if(!IsNumeric(str4Val.at(tPos)))
                tPos++;
            else
                break;
        }
        
        cout << "next pos of number is " << to_string(tPos) << endl;
            
        // remember the first numeric position: start of operator
        uiPos = tPos;
        
        // reverse parse for operator at the end: e.g. 10*m/s/10/s
        if(tPos < str4Val.length())
        {
            op = (eOperation)OP->ParseReverse(str4Val,uiPos,bShort, eOperation::opUnknown);
        
            cout << "Operator is " << BASE->Short(op) << endl;
            if(op == eOperation::opUnknown)
            {
                cout << "no operator found .... leaving " << endl;
                // leave : expected an operator
                bSuccess = false;
                break;
            }
        }
        
        // now add the the str4Meas part : might be with number for the first if left out (e.g. m/s*10)
        str4Meas += ((str4Meas.length()==0) ? BASE->Short(bmNumber) : "") + 
         (bPrependOpMult ? (bShort ? OP->Short(eOperation::opMult) :  OP->Long(eOperation::opMult)) : "") +
         str4Val.substr(0, uiPos);
        cout << "adding str4Meas part: str4Meas = " << str4Meas << endl;
        
        // remove complex measure string + operator in str4Val: str4Val starts now with a number
        // the game starts over again within this while loop
        str4Val = str4Val.substr(tPos, str4Val.length()-tPos);
        
        cout << "removing CM and  operator part: str4Val = " << str4Val << endl;
        
    }
    
    // now val keeps the value part: start to parse the complex measure part :
    
    bSuccess = meas.Parse(str4Meas, bShort);
    
    //concatenate values operators and parsed measures to one floating measure
    if(bSuccess)
    {
        // hand over results only in case of success
        dfFloating = val;
        cmMeasure = meas;
    }
    
    return bSuccess;
    
}

void CFloatingMeasure::Normalize()
{   
    // first handle simple case: only one CSimpleMeasure. I.e. when
    // 1. pMeasureRight == nullptr 
    if(  Measure().pMeasureRight == nullptr )
    {
        // multiply by "own premeasure" * "SIFactor"
        dfFloating *= Measure().pMeasureLeft->SIFactor();
        // add SI offset
        dfFloating += Measure().pMeasureLeft->SIOffset();
        
        // set measure to SI
        cmMeasure.pMeasureLeft->SetByID(pmIdent,BASE->SIID(cmMeasure.pMeasureLeft->BaseID()));
        
        // leave now ... we will not do any complex stuff
        return; 
    }

    cmMeasure.Normalize();
    dfFloating *= cmMeasure.ReleaseExp10AndFactor();
}

void CFloatingMeasure::Simplify()
{
    cmMeasure.Simplify();
    dfFloating *= cmMeasure.ReleaseExp10AndFactor();
}

void CFloatingMeasure::ScaleTo(const CComplexMeasure& other)
{
    // first handle simple case: only one CSimpleMeasure. I.e. when
    // 1. pMeasureRight == nullptr for other and this 
    // 2. pMeasureLeft is compatible with other.pMeasureLeft
    if(  Measure().pMeasureRight == nullptr && 
         other.pMeasureRight == nullptr &&
         Measure().pMeasureLeft->Compatible(other.pMeasureLeft) 
    )
    {
        // receipe: example m°C --> k°F
        // 1. Normalization: e.g. m°C --> 0.001°K
        // 2. to target base measure (no pre measure): 0.001°K --> XXX °F
        // 3. to target base measure with pre measure; XXX °F / 1000 --> XXX / 1000 * k°F

        // 1, Normalization:
        // this to SI : resolves own pre measure factor
        Normalize();
        
        // 2. to target base measure (no pre measure)
        // invert SI conversion of other: / other.SIFactor and - other.SIOffset
        dfFloating -= other.pMeasureLeft->SIOffset();
        dfFloating /=  BASE->Factor(other.pMeasureLeft->BaseID()); 

        // 3. to target base measure with pre measure
        // now divide by premeasure of other (e.g. m°C --> k°F:
         dfFloating /= PRE->Factor(other.pMeasureLeft->PreID());
        
        // hand over the new measure
        cmMeasure = other;
    } 
    else
    {
        // handle complex case:
        // check compatibility
        if (!Compatible(other))
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
    // scale precision .. if necessary: 
    // REM: this is a recursive call
    if (pfmPrecision != nullptr)
        _ScalePrecision(other);
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
        // call other ScaleTo with CComplexMeasure& argument
        ScaleTo(other.Measure());
        
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
    if (pfmPrecision == nullptr)
        pfmPrecision = new CFloatingMeasure();

    // set to precision
    pfmPrecision->operator=(UserPrecision);

    // ScaleTo actual measure
    _ScalePrecision(Measure());

}

void CFloatingMeasure::_ScalePrecision(const CComplexMeasure& other)
{
    pfmPrecision->ScaleTo(other);
    
    // do the following only if the precision has a compatible measure
    // otherwise CFloatingMeasure::ScaleTo will reset *pfmPrecision to invalid values
    // see CFloatingMeasure::_Init()
    if( pfmPrecision->Valid())
    {
        // calculate the resolution in digits
        // provide next higher number of digits for the given resolution (dValueToDeriveDigitsFrom)
        // nDigit = 1 for resolution in [0.1, 1[
        // nDigit = 0 for resolution in [1, 10[
        // nDigit = -1 for resolution in [10, 100[
        CDigFloat dfDigits = log(pfmPrecision->Floating(), 10)*(-1.);
        
        // for positive number or zero digits (i.e. precision < 10) add a digit
        // for negative number of digits subtracting twice the error should be sufficient
        // to achieve the desired number of digits
        if (pfmPrecision->Floating() < 10)
            dfDigits += 1.;

        // subtract 2* the error to be sure to fall below the next integer before casting to integer
        // REM: if you subtract only once it might happen that the subtracted result will not be different from the original double.
        //      This is due to numerical errors when using floating numbers. Subtracting twice the error will make
        //      sure to hop over the gap.
        int nDigits = (int)(dfDigits.RawValue()-2*dfDigits.RawError());
        
        // set to new precision
        dfFloating.Precision(nDigits);
        
        // activate precision
        PrecisionActive(true);
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
    oss << dfFloating.Print(false) << "*" << cmMeasure.Short();
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


    /////////////////////////////////////////////////////
    // external operators and functions for comfortable 
    // use 
    /////////////////////////////////////////////////////
CFloatingMeasure abs(const CFloatingMeasure& FM)
{ 
    return CFloatingMeasure (abs(FM.Floating()),FM.Measure());
    
}
