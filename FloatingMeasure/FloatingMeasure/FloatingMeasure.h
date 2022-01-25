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

#ifndef CFLOATINGMEASURE_H
#define CFLOATINGMEASURE_H

#include<Measure/ComplexMeasure.h>

// DEBUG
#include <iostream>

/**
 * \mainpage [FloatingMeasure Library]
 * FloatingMeasure is a class API for physical calculations. 
 * It offers:
 * - definition of a set of  phyisical  measures 
 *   - simple handling by separating the definition of a measure into its base-measure (::eBaseMeasure) and its pre-measure (::ePreMeasure):<br>
 *   new base / pre- measures can easily be added and all the modifications defined by the pre- / base- measures come for free
 * - support of complex measures (see ::CComplexMeasure):<br>
 *   - construction by concatenation of any defined measures by means of multiplication (operator "*") and division (operator "/").
 *   - simplification 
 *   - scaling to any compatible complex measure
 * - handling of numerical errors due to the incomplete digital representation of floating numbers (::CDigFloat):
 *   - comparison operators considering the numerical error
 *   - all kinds of mathematical operations
 *   - mathematical functions pow / log 
 *   - calculating the numerical error propagation for mathematical operations / functions
 *   - handling of user given resolution
 * - support  for physical calculations by utilizing ::CDigFloat and ::CComplexMeasure in a class ::CFloatingMeasure
 *   - all kinds of mathematical operations
 *   - handling of user given resolution
 *   - simplification of complex measures
 *   - scaling to compatible (complex) measures
 *   - printing
 */

/**
 * @brief FloatingMeasure: represents a floating number with a complex measure (e.g. 10*m/s).
 * This class offers:
 * - operators (+,-,*,/,<=, >=, ==, !=, <, >)
 * - simplification (e.g. 1*ms*10*m/s --> 0.01m
 * - normalization (i.e. SI units. e.g. 36*km/h --> 10*m/s)
 * - handling of the precision of the floating part for output and calculations
 * 
 */
class 
#ifdef _WIN32
_WIN_DLL_API
#endif
 CFloatingMeasure
{
    friend class CComplexMeasure;
public:
    /**
     * Default constructor
     */
    CFloatingMeasure();

    /**
     * Copy constructor
     *
     * @param other CFloatingMeasure
     */
    CFloatingMeasure(const CFloatingMeasure& other);

    /**
     * @brief Constructor from CDigFloat and CComplexMeasure
     * 
     * @param OtherFloating :CDigFloat
     * @param OtherMeasure :CComplexMeasure
     */
    CFloatingMeasure(const CDigFloat& OtherFloating, const CComplexMeasure& OtherMeasure);
    
    /**
     * Destructor
     */
    ~CFloatingMeasure();
    
    /////////////////////////////////////////////////////
    // operators
    /////////////////////////////////////////////////////
    /**
     * Assignment operator
     *
     * @param other CFloatingMeasure
     * @return CFloatingMeasure
     */
    CFloatingMeasure& operator=(const CFloatingMeasure& other);

    /**
     * @brief comparison operator
     * 
     * @param other:CFloatingMeasure
     * @return bool
     */
    bool operator==(const CFloatingMeasure& other) const;

    /**
     * @brief operator!=
     * 
     * @param other:CFloatingMeasure
     * @return bool
     */
    bool operator!=(const CFloatingMeasure& other) const;
    
    /**
     * @brief operator<
     * 
     * @param other:CFloatingMeasure
     * @return bool
     */
    bool operator<(const CFloatingMeasure& other) const;
    /**
     * @brief operator<=
     * 
     * @param other:CFloatingMeasure
     * @return bool
     */
    bool operator<=(const CFloatingMeasure& other) const;
    /**
     * @brief operator>=
     * 
     * @param other:CFloatingMeasure
     * @return bool
     */
    bool operator>=(const CFloatingMeasure& other) const;
    /**
     * @brief operator>
     * 
     * @param other:CFloatingMeasure
     * @return bool
     */
    bool operator>(const CFloatingMeasure& other) const;
    /**
     * @brief operator +=
     * 
     * @param other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator+=(const CFloatingMeasure& other);
    
    /**
     * @brief operator-=
     * 
     * @param other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator-=(const CFloatingMeasure& other);
    
    /**
     * @brief operator*=
     * 
     * @param other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator*=(const CFloatingMeasure& other);
    
    /**
     * @brief operator/=
     * 
     * @param other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator/=(const CFloatingMeasure& other);
    
    /**
     * @brief operator +
     * 
     * @param other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator+(const CFloatingMeasure& other);
    
    /**
     * @brief operator-
     * 
     * @param other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator-(const CFloatingMeasure& other);
    
    /**
     * @brief operator*
     * 
     * @param other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator*(const CFloatingMeasure& other);
    
    /**
     * @brief operator/
     * 
     * @param other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator/(const CFloatingMeasure& other);

    /**
     * @brief operator*=
     *
     * @param other:double
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator*=(const double& other);

    /**
     * @brief operator*=
     *
     * @param other: type CComplexMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator*=(const CComplexMeasure& other);
    
    /**
     * @brief operator/=
     * 
     * @param other: double
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator/=(const double& other);
    
    /**
     * @brief operator*
     * 
     * @param other:double
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator*(const double& other);
    
    /**
     * @brief operator/
     * 
     * @param other:double
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator/(const double& other);
    
    
    /////////////////////////////////////////////////////
    // pipe functions from CComplexMeasure
    /////////////////////////////////////////////////////
    /**
     * @brief parses a string setting ::dfFloating and ::cmMeasure if parsing is successful
     * 
     */
    bool Parse(const string& str2Parse, bool bShort = true);
    
    /**
     * @brief convert to SI unit and remove premeasures != pmIdent
     * 
     */
    void Normalize();
    
    /**
     * @brief convert to SI unit and remove premeasures != pmIdent
     * 
     */
    void Simplify();
    
    /**
     * @brief check measures for compatibility
     * 
     * @param other:CFloatingMeasure
     * 
     * @return bool
     */
    bool Compatible(const CFloatingMeasure& other) { return cmMeasure.Compatible(other.Measure());}
    
    /**
     * @brief check measures for compatibility
     * 
     * @param other:CComplexMeasure&
     * 
     * @return bool
     */
    bool Compatible(const CComplexMeasure& other) { return cmMeasure.Compatible(other);}
    
    /**
     * @brief scales to CComplexMeasure of other
     * 
     * @param other:CFloatingMeasure
     */
    void ScaleTo(const CFloatingMeasure& other); 
    
    /**
     * @brief scales to CComplexMeasure other
     * 
     * @param other:CComplexMeasure&
     */
    void ScaleTo(const CComplexMeasure& other); 
    
    /////////////////////////////////////////////////////
    // pipe functions from CDigFloat
    /////////////////////////////////////////////////////
    /**
     * @brief setting precision of floating number by floating number:
     * calls CDigFloat::Precision(nDigits) from CFloatingMeasure::dfFloating. 
     * 
     * @param UserPrecision: CFloatingMeasure which determines no. of digits=(-log(UserPrecision) +1)
     */
    void Precision(const CFloatingMeasure& UserPrecision );
    
    /**
     * @brief switch precision defined by dfFloating::nPrecision on / off
     * 
     * @param bPrecisionActive p_bPrecisionActive:bool
     */
    void PrecisionActive( const bool bPrecisionActive) {dfFloating.PrecisionActive(bPrecisionActive);}
    /**
     * @brief get PrecisionActive from dfFloating
     * 
     * @return const bool
     */
    const bool PrecisonActive() const {return dfFloating.PrecisionActive();}
    /**
     * @brief checks if the cmMeasure and dfFloating are valid values 
     * 
     * @return bool
     */
    bool Valid() {return Measure().Valid() && Floating().Valid();}
    
    /////////////////////////////////////////////////////
    // public output functions 
    /////////////////////////////////////////////////////
    /**
     * @brief debugging output for every member
     * 
     * @return string
     */
    string DebugOut();
    /**
     * @brief printing short output: e.g. "10*mv/V"
     * 
     * @return string
     */
    string PrintShort();

    /////////////////////////////////////////////////////
    // public getter 
    /////////////////////////////////////////////////////
    /**
     * @brief gettter for dfFloating
     * 
     * @return CDigFloat
     */
    CDigFloat Floating() const {return dfFloating;}
    /**
     * @brief getter for cmMeasure
     * 
     * @return CComplexMeasure
     */
    CComplexMeasure Measure() const { return cmMeasure;}
    
    /**
     * @brief get the precision as CFloatingMeasure
     * 
     * @return CFloatingMeasure
     */
    CFloatingMeasure Precision() const;
    
protected:

    /////////////////////////////////////////////////////
    // protected functions
    /////////////////////////////////////////////////////
    /**
     * @brief initialization with invalid values: floating = myNaN, cmMeasure = unknownn
     * 
     */
    void _Init();
    void _Precision(const CFloatingMeasure* pOtherPrecision);
    void _ScalePrecision(const CComplexMeasure& other);
    /////////////////////////////////////////////////////
    // protected getter / setter
    /////////////////////////////////////////////////////
    
    /**
     * @brief setter for cmMeasure
     * 
     * @param other:CComplexMeasure
     */
    void Measure(const CComplexMeasure& other);
    /**
     * @brief setter for dfFloating
     * 
     * @param other:CDigFloat
     */
    void Floating(const CDigFloat& other ) {dfFloating = other;}
    
    /////////////////////////////////////////////////////
    // protected variables
    /////////////////////////////////////////////////////
 
    CComplexMeasure cmMeasure;
    CDigFloat dfFloating;
    CFloatingMeasure* pfmPrecision;
};
    /////////////////////////////////////////////////////
    // external operators and functions for comfortable 
    // use 
    /////////////////////////////////////////////////////
/**
 * @brief abs: returns CFloatingMeasure with absolute value;
 *
 * @param FM: CFloatingMeasure
 * @return CFloatingMeasure
 */
CFloatingMeasure
#ifdef _WIN32
_WIN_DLL_API
#endif
abs(const CFloatingMeasure& FM);

/**
 * @brief operator* : enables CFloatingMeasure = 10*mV;
 * 
 * @param Floating: CDigFloat 
 * @param Measure: CComplexMeasure
 * @return CFloatingMeasure
 */
CFloatingMeasure
#ifdef _WIN32
_WIN_DLL_API
#endif
inline operator*(const CDigFloat& Floating ,const CComplexMeasure& Measure) { return CFloatingMeasure(Floating, Measure);}

/**
 * @brief operator* : enables CFloatingMeasure = mV*10;
 * 
 * @param Measure: CComplexMeasure
 * @param Floating: CDigFloat 
 * @return CFloatingMeasure
 */
CFloatingMeasure
#ifdef _WIN32
_WIN_DLL_API
#endif
inline operator*(const CComplexMeasure& Measure,const CDigFloat& Floating) { return CFloatingMeasure(Floating, Measure);}

/**
 * @brief operator* : enables CFloatingMeasure = 10*mV*uA;
 * 
 * @param FloatingMeasure: CFloatingMeasure (e.g. 10*mV)
 * @param Measure: CComplexMeasure (e.g. uA)
 * @return CFloatingMeasure
 */
CFloatingMeasure
#ifdef _WIN32
_WIN_DLL_API
#endif
inline operator*(const CFloatingMeasure& FloatingMeasure ,const CComplexMeasure& Measure) { return CFloatingMeasure(FloatingMeasure.Floating(), FloatingMeasure.Measure()*Measure);}

/**
 * @brief operator* : enables CFloatingMeasure = mV*uA*10;
 * 
 * @param Measure: CComplexMeasure (e.g. mV*uA)
 * @param FloatingMeasure: CFloatingMeasure (e.g. 10)
 * @return CFloatingMeasure
 */
CFloatingMeasure
#ifdef _WIN32
_WIN_DLL_API
#endif
inline operator*(const CComplexMeasure& Measure, const CFloatingMeasure& FloatingMeasure ) { return CFloatingMeasure(FloatingMeasure.Floating(), FloatingMeasure.Measure()*Measure);}

/**
 * @brief operator/ : enables CFloatingMeasure = 10/mV;
 * 
 * @param Floating: CDigFloat 
 * @param Measure: CComplexMeasure
 * @return CFloatingMeasure
 */
CFloatingMeasure
#ifdef _WIN32
_WIN_DLL_API
#endif
inline operator/(const CDigFloat& Floating ,const CComplexMeasure& Measure) { return CFloatingMeasure(Floating, CComplexMeasure(pmIdent, bmNumber) / Measure);}

/**
 * @brief operator/ : enables CFloatingMeasure = mV/10;
 * 
 * @param Measure: CComplexMeasure
 * @param Floating: CDigFloat 
 * @return CFloatingMeasure
 */
CFloatingMeasure
#ifdef _WIN32
_WIN_DLL_API
#endif
inline operator/(const CComplexMeasure& Measure,const CDigFloat& Floating ) { return CFloatingMeasure(Floating, CComplexMeasure(pmIdent, bmNumber) / Measure);}

/**
 * @brief operator/ : enables CFloatingMeasure = 10*mV/uA;
 * 
 * @param FloatingMeasure: CFloatingMeasure (e.g. 10*mV)
 * @param Measure: CComplexMeasure (e.g. uA)
 * @return CFloatingMeasure
 */
CFloatingMeasure
#ifdef _WIN32
_WIN_DLL_API
#endif
inline operator/(const CFloatingMeasure& FloatingMeasure ,const CComplexMeasure& Measure) { return CFloatingMeasure(FloatingMeasure.Floating(), FloatingMeasure.Measure()/Measure);}

#endif // CFLOATINGMEASURE_H
