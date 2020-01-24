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

/**
 * @brief FloatingMeasure: represents a floating number with a complex measure (e.g. 10*m/s).
 * This class offers:
 * - operators (+,-,*,/,<=, >=, ==, !=, <, >)
 * - simplification (e.g. 1*ms*10*m/s --> 0.01m
 * - normalization (i.e. SI units. e.g. 36*km/h --> 10*m/s)
 * - handling of the precision of the floating part for output and calculations
 * 
 */
class DLLEXPORT_CMD CFloatingMeasure
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
     * @param other p_other:CFloatingMeasure
     * @return bool
     */
    bool operator==(const CFloatingMeasure& other) const;

    /**
     * @brief operator!=
     * 
     * @param other p_other:CFloatingMeasure
     * @return bool
     */
    bool operator!=(const CFloatingMeasure& other) const;
    
    /**
     * @brief operator<
     * 
     * @param other p_other:CFloatingMeasure
     * @return bool
     */
    bool operator<(const CFloatingMeasure& other) const;
    /**
     * @brief operator<=
     * 
     * @param other p_other:CFloatingMeasure
     * @return bool
     */
    bool operator<=(const CFloatingMeasure& other) const;
    /**
     * @brief operator>=
     * 
     * @param other p_other:CFloatingMeasure
     * @return bool
     */
    bool operator>=(const CFloatingMeasure& other) const;
    /**
     * @brief operator>
     * 
     * @param other p_other:CFloatingMeasure
     * @return bool
     */
    bool operator>(const CFloatingMeasure& other) const;
    /**
     * @brief operator +=
     * 
     * @param other p_other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator+=(const CFloatingMeasure& other);
    
    /**
     * @brief operator-=
     * 
     * @param other p_other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator-=(const CFloatingMeasure& other);
    
    /**
     * @brief operator*=
     * 
     * @param other p_other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator*=(const CFloatingMeasure& other);
    
    /**
     * @brief operator/=
     * 
     * @param other p_other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator/=(const CFloatingMeasure& other);
    
    /**
     * @brief operator +
     * 
     * @param other p_other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator+(const CFloatingMeasure& other);
    
    /**
     * @brief operator-
     * 
     * @param other p_other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator-(const CFloatingMeasure& other);
    
    /**
     * @brief operator*
     * 
     * @param other p_other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator*(const CFloatingMeasure& other);
    
    /**
     * @brief operator/
     * 
     * @param other p_other:CFloatingMeasure
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator/(const CFloatingMeasure& other);
    
    /**
     * @brief operator*=
     * 
     * @param other p_other:double
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator*=(const double& other);
    
    /**
     * @brief operator/=
     * 
     * @param other p_other:double
     * @return CFloatingMeasure&
     */
    CFloatingMeasure& operator/=(const double& other);
    
    /**
     * @brief operator*
     * 
     * @param other p_other:double
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator*(const double& other);
    
    /**
     * @brief operator/
     * 
     * @param other p_other:double
     * @return CFloatingMeasure&
     */
    CFloatingMeasure operator/(const double& other);
    
    
    /////////////////////////////////////////////////////
    // pipe functions from CComplexMeasure
    /////////////////////////////////////////////////////
    /**
     * @brief convert to SI unit and remove premeasures != pmIdent
     * 
     */
    void Normalize();
    
    /**
     * @brief check measures for compatibility
     * 
     * @param other p_other:CFloatingMeasure
     * 
     * @return bool
     */
    bool Compatible(const CFloatingMeasure& other) { return cmMeasure.Compatible(other.Measure());}
    
    /**
     * @brief check measures for compatibility
     * 
     * @param other p_other:CComplexMeasure&
     * 
     * @return bool
     */
    bool Compatible(const CComplexMeasure& other) { return cmMeasure.Compatible(other);}
    
    /**
     * @brief scales to CComplexMeasure of other
     * 
     * @param other p_other:CFloatingMeasure
     */
    void ScaleTo(const CFloatingMeasure& other); 
    
    /**
     * @brief scales to CComplexMeasure other
     * 
     * @param other p_other:CComplexMeasure&
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
    void _Precision(const CFloatingMeasure* pOtherPrecision );
    /////////////////////////////////////////////////////
    // protected getter / setter
    /////////////////////////////////////////////////////
    
    /**
     * @brief setter for cmMeasure
     * 
     * @param other p_other:CComplexMeasure
     */
    void Measure(const CComplexMeasure& other);
    /**
     * @brief setter for dfFloating
     * 
     * @param other p_other:CDigFloat
     */
    void Floating(const CDigFloat& other ) {dfFloating = other;}
    
    /////////////////////////////////////////////////////
    // protected variables
    /////////////////////////////////////////////////////
 
    CComplexMeasure cmMeasure;
    CDigFloat dfFloating;
    CFloatingMeasure* pfmPrecision;
};

/**
 * @brief operator* : enables CFloatingMeasure = 10*mV;
 * 
 * @param Floating: CDigFloat 
 * @param Measure: CComplexMeasure
 * @return CFloatingMeasure
 */
CFloatingMeasure operator*(const CDigFloat& Floating ,const CComplexMeasure& Measure) { return CFloatingMeasure(Floating, Measure);}

/**
 * @brief operator* : enables CFloatingMeasure = mV*10;
 * 
 * @param Measure: CComplexMeasure
 * @param Floating: CDigFloat 
 * @return CFloatingMeasure
 */
CFloatingMeasure operator*(const CComplexMeasure& Measure,const CDigFloat& Floating) { return CFloatingMeasure(Floating, Measure);}

/**
 * @brief operator* : enables CFloatingMeasure = 10*mV*uA;
 * 
 * @param FloatingMeasure: CFloatingMeasure (e.g. 10*mV)
 * @param Measure: CComplexMeasure (e.g. uA)
 * @return CFloatingMeasure
 */
CFloatingMeasure operator*(const CFloatingMeasure& FloatingMeasure ,const CComplexMeasure& Measure) { return CFloatingMeasure(FloatingMeasure.Floating(), FloatingMeasure.Measure()*Measure);}

/**
 * @brief operator* : enables CFloatingMeasure = mV*uA*10;
 * 
 * @param Measure: CComplexMeasure (e.g. mV*uA)
 * @param FloatingMeasure: CFloatingMeasure (e.g. 10)
 * @return CFloatingMeasure
 */
CFloatingMeasure operator*(const CComplexMeasure& Measure, const CFloatingMeasure& FloatingMeasure ) { return CFloatingMeasure(FloatingMeasure.Floating(), FloatingMeasure.Measure()*Measure);}

/**
 * @brief operator/ : enables CFloatingMeasure = 10/mV;
 * 
 * @param Floating: CDigFloat 
 * @param Measure: CComplexMeasure
 * @return CFloatingMeasure
 */
CFloatingMeasure operator/(const CDigFloat& Floating ,const CComplexMeasure& Measure) { return CFloatingMeasure(Floating, CComplexMeasure(pmIdent, bmNumber) / Measure);}

/**
 * @brief operator/ : enables CFloatingMeasure = mV/10;
 * 
 * @param Measure: CComplexMeasure
 * @param Floating: CDigFloat 
 * @return CFloatingMeasure
 */
CFloatingMeasure operator/(const CComplexMeasure& Measure,const CDigFloat& Floating ) { return CFloatingMeasure(Floating, CComplexMeasure(pmIdent, bmNumber) / Measure);}

/**
 * @brief operator/ : enables CFloatingMeasure = 10*mV/uA;
 * 
 * @param FloatingMeasure: CFloatingMeasure (e.g. 10*mV)
 * @param Measure: CComplexMeasure (e.g. uA)
 * @return CFloatingMeasure
 */
CFloatingMeasure operator/(const CFloatingMeasure& FloatingMeasure ,const CComplexMeasure& Measure) { return CFloatingMeasure(FloatingMeasure.Floating(), FloatingMeasure.Measure()/Measure);}

#endif // CFLOATINGMEASURE_H
