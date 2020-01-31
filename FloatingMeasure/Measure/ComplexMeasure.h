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

#ifndef CCOMPLEXMEASURE_H
#define CCOMPLEXMEASURE_H

#include "SimpleMeasure.h"
#include "MeasureOperator.h"
#include <DigFloat/DigFloat.h>

// forward declaration
class CFloatingMeasure;

/**
 * @brief CComplexMeasure: represents a list of measures (i.e. CSimpleMeasure) chained by operators * and / <br>
 * This class handles:
 *    - operators and constructors for construction of complex measures (e.g. mV / kA )
 *    - simplification (e.g. V * A / V --> A)
 *    - normalization  (e.g. mV \f$\rightarrow\f$ V)
 *    - comparison (e.g. mV / mA is equal to kV / kA)
 *    - compatibility check ( e.g. mV /kA is compatible with kA / mV)<br>
 * 
 * REMARK:
 * physical laws like the Ohm law is NOT (yet) meant to (and may be never will) <br> 
 * be considered within this class (i.e. ohm = volt / ampere )
 * 
 */
class 
#ifdef _WIN32
FloatingMeasureDLL_API
#endif
CComplexMeasure
{
    // friends
    friend class CFloatingMeasure;
    friend class CSimpleMeasure;
    
public:
    /**
     * Default constructor: calls CComplexMeasure::_Init()
     */
    CComplexMeasure();

    /**
     * Copy constructor: <br>
     * calls CComplexMeasure::_Init, newly allocates CComplexMeasure::pMeasureLeft and CComplexMeasure::pMeasureRight from "other" CComplexMeasure
     *
     * @param other CComplexMeasure to 
     */
    /**
     * @brief Copy constructor: calls CComplexMeasure::<br>
     * calls CComplexMeasure::_Init, newly allocates CComplexMeasure::pMeasureLeft and CComplexMeasure::pMeasureRight from "other" CComplexMeasure
     * 
     * @param other: CComplexMeasure& to copy from
     */
    CComplexMeasure(const CComplexMeasure& other);

    /**
     * @brief Constructor by #ePreMeasure index and #eBaseMeasure index:<br>
     * only sets ::pMeasureLeft and deletes ::pMeasureRight
     * 
     * @param PreMeasureEnum: pre-measure index
     * @param BaseMeasureEnum: base-measure index
     */
    CComplexMeasure(const ePreMeasure PreMeasureEnum, const eBaseMeasure BaseMeasureEnum);

    /**
     * @brief Copy constructor with  pointer arg. :  <br>
     * calls CComplexMeasure::_Init, newly allocates CComplexMeasure::pMeasureLeft and CComplexMeasure::pMeasureRight from "other" CComplexMeasure
     *
     * @param other p_other:...
     */
    CComplexMeasure(const CComplexMeasure* other);

    /**
     * Destructor
     */
    ~CComplexMeasure();
    
    /**
     * @brief assignment operator: 
     * 
     * @param other: CComplexMeasure to copy from
     * @return CComplexMeasure&
     */
    CComplexMeasure& operator=(const CComplexMeasure& other);
  
    /**
     * @brief operator *=: calls CComplexMeasure::_AllocateLastUnsetMeasureRight
     * 
     * 
     * @param other: CComplexMeasure to copy into CComplexMeasure::pMeasureRight connecting with #opMult
     * @return CComplexMeasure&
     */
    CComplexMeasure& operator*=(const CComplexMeasure& other);

    /**
     * @brief operator /=: calls CComplexMeasure::_AllocateLastUnsetMeasureRight
     * 
     * 
     * @param other: CComplexMeasure to copy into CComplexMeasure::pMeasureRight connecting with #opDivide
     * @return CComplexMeasure&
     */
    CComplexMeasure& operator/=(const CComplexMeasure& other);
    
    /**
     * @brief operator *: calls CComplexMeasure::operator*= with a copy of calling instance
     * 
     * @param other: CComplexMeasure to copy into CComplexMeasure::pMeasureRight connecting with #opMult
     * @return CComplexMeasure
     */
    CComplexMeasure operator*(const CComplexMeasure& other);
    
    /**
     * @brief operator /: calls CComplexMeasure::operator/= with a copy of calling instance
     * 
     * @param other: CComplexMeasure to copy into CComplexMeasure::pMeasureRight connecting with #opDivide
     * @return CComplexMeasure
     */
    CComplexMeasure operator/(const CComplexMeasure& other);

    bool operator==(const CComplexMeasure& other) const;
    bool operator!=(const CComplexMeasure& other) const;
    /**
     * @brief checks for a CComplexMeasure being scaled (i.e. f* this) to this
     * 
     * @param other p_other:CComplexMeasure
     * @return bool
     */
    bool Compatible(const CComplexMeasure& other) const;
    /**
     * @brief scale to other compatible CComplexMeasure
     * 
     * @param other p_other:CComplexMeasure
     */
    void ScaleTo(const CComplexMeasure& other);
    
    /**
     * @brief sets the pMeasureLeft calling CSimpleMeasure::SetByID
     * 
     * @param PreMeasureEnum p_PreMeasureEnum: index of premeasure...
     * @param BaseMeasureEnum p_BaseMeasureEnum: index of base measure
     */
    void SetByID(const ePreMeasure PreMeasureEnum, const eBaseMeasure BaseMeasureEnum);
    
    /**
     * @brief sets all measures to SI and calculates SIpremeasure and dSIFactor: calls internal 
     *        function CComplexMeasure::_Normalize(nullptr,nullptr)
     * 
     */
    void Normalize();
    
    /**
     * @brief getter for dfCMFactor
     * 
     * @return double&
     */
    const CDigFloat& CMFactor() {return dfCMFactor;};
    /**
     * @brief getter for nCMExp10
     * 
     * @return ePreMeasure&
     */
    const int CMExp10() {return nCMExp10;};
    
    /**
     * @brief simplifies complex measure (e.g. uV / mV * A = A (exp10 += -3))
     * the factors of the premeasures are collected in the CComplexMeasure::nExp10 member of this class
     * 
     */
    void Simplify();
    
    /**
     * @brief check for valid measures: if one invalid measure is found --> everything is invalid
     * 
     * @return bool
     */
    bool Valid();
    
    /**
     * @brief prints the short label of the CComplexMeasure::opEnum
     * 
     * @return string
     */
    string OPShort() {return CMeasureOperatorSingleton::instance()->Short(opEnum);}
    /**
     * @brief prints the premeasure and the base measure short labels
     * 
     * @return string
     */
    string Short();
    
    /**
     * @brief prints all members: can be applied for debugging purpose
     * 
     * @return string
     */
    string DebugOut();

protected:
    /////////////////////////////////////////////////////
    // protected functions
    /////////////////////////////////////////////////////
    
    void _Init(bool bAllocateMeasureLeft = true);
    void _InvertOP();    
   /**
     * @brief helping function allocating the last pMeasureRight, joining with given operation
     * 
     *  
    * @param cmOperandLeft: CComplexMeasure left operand
    * @param cmOperandRight: CComplexMeasure right operand
    * @param OperationEnum: eOperation operation
     */
   void _AllocateLastUnsetMeasureRight(CComplexMeasure& cmOperandLeft,const CComplexMeasure& cmOperandRight, const eOperation OperationEnum);
    
    /**
     * @brief internally called function: called by CComplexMeasure::Normalize which
     *        sets all measures to SI and calculates SIpremeasure and dSIFactor
     * 
     * @details setting to SI measure can only be done for factors only. Any measure which
     *          must be calculated with a non-zero offset to its SI measure is left as is.
     *          But all premeasures will be collected in eSIPreMeasure and set to identity.
     * 
     * @param pPreviousOP: eOperation operation of previous CComplexMeasure
     * @param pdTempPreMeasureExp10Collector: int pointer collecting all exp10
     * @param pdTempCMFactorCollector: CDigFloat pointer collecting all  CComplexMeasure::CMFactor
     * @param pFirstComplexMeasure: CComplexMeasure first complex measure where collected exp10 and CMFactor are stored
     */
    void _Normalize(eOperation* &pPreviousOP, int* &pdTempPreMeasureExp10Collector, CDigFloat* &pdTempCMFactorCollector, CComplexMeasure* &pFirstComplexMeasure);
    
    
    /**
     * @brief this function must always called when two CComplexMeasures are joined (e.g. from function _AllocateLastUnsetMeasureRight)
     * 
     */
    void _COllectCMExp10CMFactorWrapper();
    
    
    /**
     * @brief internal function called by every function which extents CComplexMeasure with "other" CComplexMeasure
     *        collects the CMExp10 and CMFactor from "other" and unites it into the primary CMFactor and CMExp10
     * 
     * @param pPreviousOP: eOperation operation of previous CComplexMeasure
     * @param pdTempPreMeasureExp10Collector: int pointer collecting all exp10
     * @param pdTempCMFactorCollector: CDigFloat pointer collecting all  CComplexMeasure::CMFactor
     * @param pFirstComplexMeasure: CComplexMeasure first complex measure where collected exp10 and CMFactor are stored
     */
    void _COllectCMExp10CMFactor(eOperation* &pPreviousOP, int* &pdTempPreMeasureExp10Collector, CDigFloat* &pdTempCMFactorCollector, CComplexMeasure* &pFirstComplexMeasure);
    
    /**
     * @brief collects pMeasureLeft with operands into mOpMeas --> used for CComplexMeasure::Simplify
     * 
     * @param mOpMeas p_mOpMeas:...
     */
    void _CollectLeftSortByOp(map<eOperation,CComplexMeasure*> &mOpMeas);
    
    /**
     * @brief searches CSimpleMeasure of consecutive pMeasureRight, which pMeasureLeft have thesame SI index as 
     *        pMeasureLeft of pShortenPartner: stops if the first item is found, CComplexMeasure::_ResolveMeasureLeft for pShortenPartner
     * and the found item is called.
     * This function is called as one step CComplexMeasure::Simplify
     * 
     * @param pShortenPartner: the shorten partner which lets its pMeasureRight call this function
     * @param eOPofShortenPartner: the operator which preceedes the pMeasureRight of the shorten partner
     * @param eOPofConsecutiveShortenPartner: 
     */
    void _SearchAndShortenSameSIIndex(CComplexMeasure* pShortenPartner,eOperation &eOPofShortenPartner, eOperation &eOPofConsecutiveShortenPartner);
    /**
     * @brief collects premeasure factor in nExp10 and sets pMeasureLeft to (pmIdent, bmNumber)
     * 
     */
    void _ResolveMeasureLeft();
    void _RemoveNeutralNumbers(CComplexMeasure &PreviousComplexMeasure);
    void _Simplify(eOperation& PreviousOP);
    
    /**
     * @brief recursive call of checking the pMeasureLeft measures being valid
     * 
     * @param bValid: bool which will be set to pMeasureLeft::Valid
     */
    void _Valid(bool& bValid);
    
    /**
     * @brief returns the product of dfCMFactor and pow(10,Exp10()) and resets factor to 1 and nExp10 to 0
     * 
     * @return const double
     */
    const double ReleaseExp10AndFactor();
    
    /**
     * @brief protected setter of nCMExp10 ... for internal use only
     * 
     * @param OtherExp10 :ePreMeasure
     */
    void CMExp10(const int OtherExp10) {nCMExp10 = OtherExp10;}

    /**
     * @brief protected setter of dfCMFactor ... for internal use only
     * 
     * @param Factor p_Factor:double
     */
    void CMFactor(const double Factor) {dfCMFactor = Factor;}
    
//     void _MergnCMExp10CMFactors();

    /////////////////////////////////////////////////////
    // protected members
    /////////////////////////////////////////////////////

    /**
     * @brief index of the corresponding operator of pMeasureLeft and pMeasureRight
     * 
     */
    eOperation        opEnum;
    /**
     * @brief right operand as complex measure (pointing to next pMeasureLeft, operator, and pMeasureRight
     *        for a daisy chained list of complex measures
     * 
     */
    CComplexMeasure*  pMeasureRight;
    /**
     * @brief left operand is a SimpleMeasure representant
     * 
     */
    CSimpleMeasure*  pMeasureLeft;
    /**
     * @brief the epx10 which will be set e.g. for normalization or simplification collecting all Exp10 of PreMeasureEnum(see CComplexMeasure::Simplify()
     *        and CComplexMeasure::Normalize().)
     * 
     */
    int     nCMExp10;
    /**
     * @brief the factor value which will be set e.g. for normalization or simplification collecting all SI factors(see CComplexMeasure::Simplify()
     *        and CComplexMeasure::Normalize().)
     * 
     */
    CDigFloat        dfCMFactor;
};

#endif // CCOMPLEXMEASURE_H
