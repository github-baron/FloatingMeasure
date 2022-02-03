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

#ifndef CSIMPLEUNIT_H
#define CSIMPLEUNIT_H

// #include<Measure/PreMeasure.h>
// #include<Measure/BaseMeasure.h>

#include "PreMeasure.h"
#include "BaseMeasure.h"
/**
 * @brief CSimpleMeasure: represents a pre measure combined with a base measure like "mV".<br>
 * This class offers:
 * - handling of combined short / long labels of CPreMeasure and CBaseMeasure
 * - construction by short / long labels of CPreMeasure and CBaseMeasure
 * - recalculation offset and factor to SI measure of the CPreMeasure and CBaseMeasure
 * 
 */
class 
#ifdef _WIN32
_WIN_DLL_API
#endif
 CSimpleMeasure
{
friend class CPreMeasure;
friend class CBaseMeasure;
friend class CSingleton<CPreMeasure>;
friend class CSingleton<CBaseMeasure>;
public:
    /**
     * @brief Default constructor: calls CSimpleMeasure::_Init()
     */
    CSimpleMeasure();

    /**
     * @brief Copy constructor: calls CSimpleMeasure::_Init() and CSimpleMeasure::SetByID
     *
     * @param other instance to copy from
     */
    CSimpleMeasure(const CSimpleMeasure& other);

    /**
     * @brief Copy constructor: calls CSimpleMeasure::_Init() and CSimpleMeasure::SetByID
     *
     * @param other instance to copy from
     */
    CSimpleMeasure(const CSimpleMeasure* other);

    /**
     * @brief constructor by string: calls CSimpleMeasure::_Init() and CSimpleMeasure::SetByID
     *
     * @param other instance to copy from
     */
    CSimpleMeasure(const string& SimpleMeasureString);

    /**
     * @brief Destructor
     */
    ~CSimpleMeasure();

    /**
     * @brief Assignment operator: calls CSimpleMeasure::_Init() and CSimpleMeasure::SetByID
     *
     * @param other instance to assign from
     * @return reference to this
     */
    CSimpleMeasure& operator=(const CSimpleMeasure& other);
    
    /**
     * @brief operator ==:<br>
     * compares
     * - CSimpleMeasure::PreIndex
     * - CSimpleMeasure::BaseIndex
     * 
     * @param other: CSimpleMeasure to compare
     * @return const bool
     */
    bool const operator==(const CSimpleMeasure& other) const;

    /**
     * @brief operator !=: <br>
     * calls inverted CSimpleMeasure::operator==
     * 
     * @param other: CSimpleMeasure to compare
     * @return const bool
     */
    bool operator!=(const CSimpleMeasure& other) const;
    
    /**
     * @brief Sets pre- and base Measure parsing compound string like "mV"
     * 
     * @param strPreLabelBaseLabel: single string consisting of pre and base level (e.g. "mV" or long: "milliVolt")
     * @param bShort: flag indicating that the string is to be parsed in short version ("mV": flag true) or long version ("milliVolt": flag false)
     */
    bool Parse(const string& strPreLabelBaseLabel, bool bShort = true);
    
    
    /**
     * @brief sets the CSimpleMeasure::PreIndex and CSimpleMeasure::BaseIndex <br>
     * and adapts the depending members 
     * - CSimpleMeasure::dSIFactor
     * - CSimpleMeasure::dSIOffset
     * - CSimpleMeasure::strShort
     * - CSimpleMeasure::strLong
     *
     * @param PreMeasureEnum: index of #ePreMeasure
     * @param BaseMeasureEnum: index of #eBaseMeasure
     */
    void SetByID(const ePreMeasure PreMeasureEnum, const eBaseMeasure BaseMeasureEnum);
    
    /**
     * @brief calls CSimpleMeasure::SetByID with the indices defined by the corresponding short labels
     * 
     * @param strPreLabelShort: short label searched in CPreMeasure::vstrShort in #PRE
     * @param strBaseLabelShort: short label searchedin CBaseMeasure::vstrShort in #BASE
     */
    void SetByShort(const string& strPreLabelShort, const string& strBaseLabelShort);
    /**
     * @brief calls CSimpleMeasure::SetByID with the indices defined by the corresponding long labels
     * 
     * @param strPreLabelLong: long label searched in CPreMeasure::vstrLong in #PRE
     * @param strBaseLabelLong: long label searched in CPreMeasure::vstrLong in #BASE
     */
    void SetByLong(const string& strPreLabelLong, const string& strBaseLabelLong);
    /**
     * @brief checks if CSimpleMeasure::PreIndex and CSimpleMeasure::BaseIndex are valid indices <br>
     * defined in #ePreMeasure and #eBaseMeasure
     * 
     * @return bool, true in case the indices are valid
     */
    bool Valid() {return PreIndex < pmUnknown && PreIndex >= pmFirst && BaseIndex < bmUnknown && BaseIndex >= bmFirst;}
    /**
     * @brief prints all members as string for debugging.
     * 
     * @return const string
     */
    const string DebugOut();
    
    /**
     * @brief check compatiblity with other CSimpleMeasure:<br>
     * compatibility is given if the CSimpleMeasure::eBaseMeasure have the same SI measure.
     * 
     * @param other: CSimpleMeasure to check for compatibility
     * @return bool
     */
    bool Compatible( const CSimpleMeasure& other ) { return BASE->SIID( BaseID() ) == BASE->SIID(other.BaseID());}

    ////////////////////////////////////
    // public getter 
    ////////////////////////////////////
    /**
     * @brief getter of CSimpleMeasure::dSIFactor
     * 
     * @return const double
     */
    const double SIFactor(void) {return dSIFactor;}
    /**
     * @brief getter of CSimpleMeasure::dSIOffset
     * 
     * @return const double
     */
    const double SIOffset(void) {return dSIOffset;}
    /**
     * @brief getter of CSimpleMeasure::strShort
     * 
     * @return const string&
     */
    const string& Short(void) {return *strShort;}
    /**
     * @brief getter of CSimpleMeasure::strLong
     * 
     * @return const string&
     */
    const string& Long(void) {return *strLong;}
    /**
     * @brief getter of CSimpleMeasure::BaseIndex
     * 
     * @return eBaseMeasure&
     */
    const eBaseMeasure BaseID() const { return BaseIndex;}
    /**
     * @brief getter of CSimpleMeasure::PreIndex
     * 
     * @return ePreMeasure&
     */
    const ePreMeasure PreID() const { return PreIndex;}
    
    
protected:

    ////////////////////////////////////
    // protected functions
    ////////////////////////////////////     
    /**
     * @brief sets CSimpleMeasure::BaseIndex to eBaseMeasure::bmUnknown and CSimpleMeasure::PreIndex to CPreMeasure::pmUnknown
     * 
     */
    void _Init();
    
    ////////////////////////////////////
    // protected variables
    ////////////////////////////////////     
    /**
     * @brief index of type #eBaseMeasure:<br>
     * used to get elements from the vectors of #BASE:
     * - CBaseMeasure::vdOffset
     * - CBaseMeasure::vdFactor
     * - CBaseMeasure::vstrShort
     * - CBaseMeasure::vstrLong
     * 
     */
    eBaseMeasure BaseIndex;
 
    /**
     * @brief index of type #ePreMeasure:<br>
     * used to get elements from the vectors of #PRE:
     * - CPreMeasure::vdOffset
     * - CPreMeasure::vdFactor
     * - CPreMeasure::vstrShort
     * - CPreMeasure::vstrLong
     * 
     */
    ePreMeasure PreIndex;
    
    /**
     * @brief factor which must be applied this CSimpleMeasure to achieve SI measure (e.g. mV : SIFactor = 1000).<br>
     * This factor must be applied in combination with CSimpleMeasure::dSIOffset:<br>
     * SIMeasure = SIFactor * Measure + SIOffset
     * 
     */
    double dSIFactor;
    
    /**
     * @brief offset (SI measure) which must added to this CSimpleMeasure to achieve the corresponding SI measure<br>
     * E.g. °C: SIOffset = +273.15°K<br>
     * This offset must be applied in combination with CSimpleMeasure::dSIFactor:<br>
     * SIMeasure = SIFactor * Measure + SIOffset
     * 
     */
    double dSIOffset;
    
    /**
     * @brief short label  of this CSimpleMeasure: <br>
     * combination of the pre-measure short label (see PRE::Short)<br>
     * and the base-measure short label (see BASE::Short)
     * 
     */
    string* strShort;
    
    /**
     * @brief long label of this CSimpleMeasure: <br>
     * combination of the pre-measure long label (see PRE::Long)<br>
     * and the base-measure long label (see BASE::Long)
     * 
     */
    string* strLong;
    
    
};

#endif // CSIMPLEUNIT_H
