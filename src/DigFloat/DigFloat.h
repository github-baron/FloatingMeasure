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

#ifndef CDIGFLOAT_H
#define CDIGFLOAT_H


///////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////
#include<Utils/Utils.h>

///////////////////////////////////////////////////
// forward declarations
///////////////////////////////////////////////////
class CFloatingMeasure;


/**
 * @brief CDigFloat: a class for floating point numbers which handels numerical errors of the 64 bit floating point representation.<br>
 * This class offers:
 * - operations of floating points (+,-,/,*)
 * - propagation of numerical errors for all operations performed on an instance
 * - setting of user defined precision for comparing and printing.
 * 
 */
class DLLEXPORT_CMD CDigFloat
{
    friend class CFloatingMeasure;
public:
    
    ///////////////////////////////////////////////////
    // constructors / destructor
    ///////////////////////////////////////////////////
    /**
     * @brief Default constructor: calls  CDigFloat::_Init
     */
    CDigFloat();

    /**
     * @brief Copy constructor: calls CDigFloat::operator=
     *
     * @param other: CDigFloat instance to copy from
     */
    CDigFloat(const CDigFloat& other);
    
    /**
     * @brief Copy constructor from double: calls DigFloat::Value
     * 
     * @param Val: double value
     */
    CDigFloat(const double Val);

    /**
     * Destructor
     */
    ~CDigFloat();

    ///////////////////////////////////////////////////
    // public assignment operators
    ///////////////////////////////////////////////////
    /**
     * @brief Assignment operator:<br>
     * sets from other:
     * - CDigFloat::dValue
     * - CDigFloat::dError
     * calling instance keeps :
     * - CDigFloat::nPrecision 
     * - CDigFloat::bPrecisionActive
     * 
     * @param other: CDigFloat to assign from
     * @return CDigFloat& 
     */
     CDigFloat& operator=(const CDigFloat& other);
    /**
     * @brief Assignment operator with double:<br>
     * calls CDigFloat::operator= with "other" CDigFloat constructed from double.
     * 
     * @param other: double from which "other" CDigFloat is constructed
     * @return CDigFloat&
     */
    CDigFloat& operator=(const double other);

    ///////////////////////////////////////////////////
    // public comparing operators
    ///////////////////////////////////////////////////
    /**
     * @brief operator ==:  <br>
     * the absolute deviation of the comparison partners (deviation of CDigFloat::Value()) is compared to an allowed deviation range.<br>
     * This deviation range depends on CDigFloat::bPrecisionActive of calling instance:
     * - true:  the allowed deviation range is CDigFloat::dPrecisionResolution/2 of calling instance
     * - false: allowed deviation range is the sum of CDigFloat::Error of the comparison partners
     * 
     * @param other CDigFloat to compare
     * @return bool, true if absolute deviation is within the allowed deviation range
     */
    bool operator==(const CDigFloat& other) const;
    /**
     * @brief operator == with double: <br>
     * calls CDigFloat::operator== with "other" CDigFloat constructed from double.
     * 
     * @param other : double from which "other" CDigFloat is constructed 
     * @return bool, true if absolute deviation is within the allowed deviation range
     */
    bool operator==(const double other) const;

    /**
     * @brief operator !=: <br> 
     * inversion of CDigFloat::operator==
     * 
     * @param other: CDigFloat to compare with
     * @return bool, true if CDigFloat::operator== is false
     */
    bool operator!=(const CDigFloat& other) const;
    
    /**
     * @brief operator< : 
     * 
     * @param other: other CDigFloat to compare with
     * @return bool, true if CDigFloat::operator!= is true AND CDigFloat::RawValue() is less than CDigFloat::RawValue() of compared instance
     */
    bool operator<(const CDigFloat& other) const;
    /**
     * @brief operator<=
     * 
     * @param other: other CDigFloat to compare with
     * @return bool, true if CDigFloat::operator== is true OR CDigFloat::RawValue() is less than CDigFloat::RawValue() of compared instance
     */
    bool operator<=(const CDigFloat& other) const;
    /**
     * @brief operator>=
     * 
     * @param other: other CDigFloat to compare with
     * @return bool, true if CDigFloat::operator== is true AND CDigFloat::RawValue() is larger than CDigFloat::RawValue() of compared instance
     */
    bool operator>=(const CDigFloat& other) const;
    /**
     * @brief operator>
     * 
     * @param other: other CDigFloat to compare with
     * @return bool, true if CDigFloat::operator!= is true AND CDigFloat::RawValue() is larger than CDigFloat::RawValue() of compared instance
     */
    bool operator>(const CDigFloat& other) const;

    ///////////////////////////////////////////////////
    // public unary operators for operations 
    // (+,-,*,/ & Co)
    ///////////////////////////////////////////////////
    /**
     * @brief operator+=: adding CDigFloat::dValue and CDigFloat::dError (no rounding)
     * 
     * @param other: CDigFloat added
     * @return CDigFloat&
     */
    CDigFloat& operator+=(const CDigFloat& other);

    /**
     * @brief operator-=: subtracting CDigFloat::dValue, summing CDigFloat::dError (no rounding)
     * 
     * @param other:  CDigFloat subtracted
     * @return CDigFloat&
     */
    CDigFloat& operator-=(const CDigFloat& other);

    /**
     * @brief operator*=: multiplies CDigFloat::dValue, estimates max. from CDigFloat::dError propagated by the multiplication  (no rounding)
     * 
     * @param other: CDigFloat multiplied
     * @return CDigFloat&
     */
    CDigFloat& operator*=(const CDigFloat& other);

    /**
     * @brief operator/=: multiplies CDigFloat::dValue, estimates max. from CDigFloat::dError propagated by the division  (no rounding)
     * 
     * @param other: CDigFloat divided
     * @return CDigFloat&
     */
    CDigFloat& operator/=(const CDigFloat& other);
    
    /**
     * @brief operator+: calls CDigFloat::operator+=
     * 
     * @param other: CDigFloat added
     * @return CDigFloat
    */
    CDigFloat operator+(const CDigFloat& other);

    /**
     * @brief operator-: calls CDigFloat::operator=
     * 
     * @param other: CDigFloat subtracted
     * @return CDigFloat
     */
    CDigFloat operator-(const CDigFloat& other);

    /**
     * @brief operator*: calls CDigFloat::operator*=
     * 
     * @param other: CDigFloat multiplied
     * @return CDigFloat
     */
    CDigFloat operator*(const CDigFloat& other);

    /**
     * @brief operator/: calls CDigFloat::operator/=
     * 
     * @param other: CDigFloat divided
     * @return CDigFloat
     */
    CDigFloat operator/(const CDigFloat& other);    

    /**
     * @brief operator+= with double: calls CDigFloat::operator+= with CDigFloat(double)
     * 
     * @param other: double added
     * @return CDigFloat
     */
    CDigFloat& operator+=(const double other);

    /**
     * @brief operator-= with double: calls CDigFloat::operator-= with "other" CDigFloat constructed from double.
     * 
     * @param other: double from which "other" CDigFloat is constructed
     * @return CDigFloat&
     */
    CDigFloat& operator-=(const double other);

    /**
     * @brief operator*= with double: calls CDigFloat::operator*= with "other" CDigFloat constructed from double.
     * 
     * @param other: double from which "other" CDigFloat is constructed
     * @return CDigFloat&
     */
    CDigFloat& operator*=(const double other);

    /**
     * @brief operator/= with double: calls CDigFloat::operator/= with "other" CDigFloat constructed from double.
     * 
     * @param other: double from which "other" CDigFloat is constructed
     * @return CDigFloat&
     */
    CDigFloat& operator/=(const double other);
    
    /**
     * @brief operator+ with double: calls CDigFloat::operator+= with "other" CDigFloat constructed from double.
     * 
     * @param other: double from which "other" CDigFloat is constructed
     * @return CDigFloat
     */
    CDigFloat operator+(const double other);

    /**
     * @brief operator- with double: calls CDigFloat::operator-= with "other" CDigFloat constructed from double.
     * 
     * @param other: double from which "other" CDigFloat is constructed
     * @return CDigFloat
     */
    CDigFloat operator-(const double other);

    /**
     * @brief operator* with double: calls CDigFloat::operator*= with "other" CDigFloat constructed from double.
     * 
     * @param other: double from which "other" CDigFloat is constructed
     * @return CDigFloat
     */
    CDigFloat operator*(const double other);

    /**
     * @brief operator/ with double: calls CDigFloat::operator/= with "other" CDigFloat constructed from double.
     * 
     * @param other: double from which "other" CDigFloat is constructed
     * @return CDigFloat
     */
    CDigFloat operator/(const double other);
    
    ///////////////////////////////////////////////////
    // public getter / setter
    ///////////////////////////////////////////////////
    /**
     * @brief sets  CDigFloat::dValue and CDigFloat::dError corresponding to #DoubleMachineEpsilon
     * 
     * @param Val Value to be set to
     */
    void Value(const double Val);   
    
    /**
     * @brief resets CDigFloat::dError to #DoubleMachineEpsilon ( CDigFloat::dValue)
     * 
     */
    void ResetError() { Value(dValue);}
    
    /**
     * @brief getter of CDigFloat::dValue conditionally considering  CDigFloat::nPrecision:<br>
     * see CDigFloat::PrecisionActive() and CDigFloat::Precision()
     * 
     * @return const double 
     */
    const double Value() const {return PrecisionActive() ? Round2Precision( dValue, Precision()) : dValue;}
    
    /**
     * @brief getter of CDigFloat::dValue (no rounding)
     * 
     * @return const double
     */
    const double RawValue() const { return dValue;}
    
    /**
     * @brief getter of CDigFloat::dError conditionally considering CDigFloat::nPrecision: <br>
     * see CDigFloat::PrecisionActive() and CDigFloat::Precision()
     * 
     * @return const double
     */
    const double Error() const {return PrecisionActive() ? Round2Precision( dError, Precision()) : dError;}
    
    /**
     * @brief getter of CDigFloat::dError (no rounding)
     * 
     * @return const double
     */
    const double RawError() const { return dError;}
    
    /**
     * @brief getter of CDigFloat::nPrecision
     * 
     */
    const int Precision() const {return nPrecision;}
    
    /**
     * @brief sets CDigFloat::nPrecision and CDigFloat::dPrecisionResolution =10<SUP>-nPrecision</SUP> :
     * 
     * @param UserPrecision: int, defining the resolution of CDigFloat::dValue
     */
    void Precision(const int UserPrecision) { nPrecision = UserPrecision; dPrecisionResolution = pow(10,-UserPrecision);}
    
    /**
     * @brief getter for bPrecisionActive
     * 
     * @return const bool
     */
    const bool PrecisionActive() const { return bPrecisionActive;}

    /**
     * @brief setter for bPrecisionActive: constrols rounding to digits given by nPrecision
     * affected functions
     * - CDigFloat::Value()
     * - CDigFloat::Print
     * - CDigFloat::operator== 

     * 
     * @param UserPrecisionActive: bool,
     */
    void PrecisionActive( const bool UserPrecisionActive) {bPrecisionActive = UserPrecisionActive;}
    
    /**
     * @brief getter for the resolution defined by the given precision (see CDigFloat::Precision)
     * 
     * @return double
     */
    const double PrecisionResolution() const {return dPrecisionResolution;}

    /**
     * @brief check if value is valid: non-NaN
     * 
     * @return bool
     */
    bool Valid() {return !isnan( RawValue() );}

    ///////////////////////////////////////////////////
    // public printing functions
    ///////////////////////////////////////////////////
    /**
     * @brief prints CDigFloat::dValue and conditionally CDigFloat::dError formatted according to CDigFloat::nPrecision.
     * 
     * @param bWithError: if true, CDigFloat::dError is printed, too
     * @return wstring, formatted CDigFloat::dValue [\f$\pm\f$ CDigFloat::dError] according to CDigFloat::nPrecision
     */
    wstring Print(bool bWithError = true) const;
    
    /**
     * @brief prints CDigFloat::dValue and conditionally CDigFloat::dError formatted according to UserPrecision.
     * 
     * @param UserPrecision: int defining the precision
     * @param bWithError: bool, switching printing of CDigFloat::dError
     * @return wstring, formatted CDigFloat::dValue [\f$\pm\f$ CDigFloat::dError] according to UserPrecision 
     */
    wstring RawPrint(const int UserPrecision, bool bWithError = true) const;
    
    /**
     * @brief prints all members into a wstring for debugging purpose
     * 
     * @return wstring
     */
    wstring DebugOut();

    
protected:
    
    ///////////////////////////////////////////////////
    // protected functions
    ///////////////////////////////////////////////////
    /**
     * @brief initializes all members with invalid values
     * 
     */
    void _Init();
    
    /**
     * @brief setter for CDigFloat::dError (protected: for internal use only)
     * 
     * @param other: double
     */
    void Error(const double other) {dError = other;}
    
    
    ///////////////////////////////////////////////////
    // protected variables
    ///////////////////////////////////////////////////
    
    /**
     * @brief keeps the numerical error of CDigFloat::dValue including the propagation due to multiple operations
     * 
     */
    double dError;
    /**
     * @brief the raw value 
     * 
     */
    double dValue;
    /**
     * @brief number which controls the output precision of CDigFloat::dValue:
     * affected functions
     * - CDigFloat::Value() (if CDigFloat::bPrecisionActive == true)
     * - CDigFloat::Print
     * - CDigFloat::operator== (if CDigFloat::bPrecisionActive == true)
     * 
     * 
     */
    int nPrecision;
    /**
     * @brief the resolution which controls the output precision of CDigFloat::dValue:
     * It is calculated by 10<SUP>-nPrecision</SUP>
     * affected functions
     * - CDigFloat::Value() (if CDigFloat::bPrecisionActive == true)
     * - CDigFloat::Print
     * - CDigFloat::operator== (if CDigFloat::bPrecisionActive == true)
     * 
     */
    double dPrecisionResolution;
    /**
     * @brief switches on (=true) / off (=false) the given precision:<br>
     * affected functions
     * - CDigFloat::Value() 
     * - CDigFloat::operator== 
     * 
     */
    bool bPrecisionActive;
};


#endif // CDIGFLOAT_H
