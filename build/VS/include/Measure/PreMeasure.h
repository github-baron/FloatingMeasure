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

#ifndef CPREUNIT_H
#define CPREUNIT_H

#include "VectorHandle.h"

/**
 * \brief enum for indexing the vectors of CPreMeasure
 * 
 */
enum ePreMeasure 
{
    pmFemto = 0,        /*!<0 factor = 10 <SUP> ⁻15 </SUP>, exp10: -15, short: "f", long: "femto"   */  
    pmFirst = pmFemto,  /*!<0 starting index "femto"*/
    pmPiko,             /*!<1  :  factor = 10 <SUP>⁻12</SUP>,  exp10: -12, short: "p",   long: "piko" */   
    pmNano,             /*!<2  :  factor = 10 <SUP>⁻9 </SUP>,  exp10: -9,  short: "n",   long: "nano" */   
    pmMicro,            /*!<3  :  factor = 10 <SUP>⁻6 </SUP>,  exp10: ⁻6,  short: \"&mu;\", long: "micro"*/    
    pmMilli,            /*!<4  :  factor = 10 <SUP>⁻3 </SUP>,  exp10: ⁻3,  short: "m",   long: "milli"*/    
    pmCenti,            /*!<5  :  factor = 10 <SUP>⁻2 </SUP>,  exp10: ⁻2,  short: "c",   long: "centi"*/    
    pmDeci,             /*!<6  :  factor = 10 <SUP>⁻1 </SUP>,  exp10: ⁻1,  short: "d",   long: "deci" */   
    pmIdent,            /*!<7  :  factor = 10 <SUP> 0 </SUP>,  exp10:  0,  short: "",    long: ""     */
    pmDeca,             /*!<8  :  factor = 10 <SUP>+1 </SUP>,  exp10: +1,  short: "da",  long: "deca" */   
    pmHecto,            /*!<9  :  factor = 10 <SUP>+2 </SUP>,  exp10: +2,  short: "h",   long: "hecto"*/    
    pmKilo,             /*!<10 :  factor = 10 <SUP>+3 </SUP>,  exp10: +3,  short: "k",   long: "kilo" */   
    pmMega,             /*!<11 :  factor = 10 <SUP>+6 </SUP>,  exp10: +6,  short: "M",   long: "mega" */   
    pmGiga,             /*!<12 :  factor = 10 <SUP>+9 </SUP>,  exp10: +9,  short: "G",   long: "giga" */   
    pmTera,             /*!<13 :  factor = 10 <SUP>+12</SUP>,  exp10: +12, short: "T",   long: "tera" */   
    pmPeta,             /*!<14 :  factor = 10 <SUP>+15</SUP>,  exp10: +15, short: "P",   long: "peta" */   
    pmExa,              /*!<15 :  factor = 10 <SUP>+18</SUP>,  exp10: +18, short: "E",   long: "exa"  */  
    pmZetta,            /*!<16 :  factor = 10 <SUP>+21</SUP>,  exp10: +21, short: "Z",   long: "zetta"*/    
    pmYotta,            /*!<17 :  factor = 10 <SUP>+24</SUP>,  exp10: +24, short: "Y",   long: "yotta"*/    
    pmLast,             /*!<18 :  invalid last index */ 
    pmUnknown = pmLast  /*!<18 :  identical with last index */
}; 

/**
 * @brief CPreMeasure represents the pre-measure part of a measure. <br>
 * For example milli volt consists of the base-measure part "Volt" (see CBaseMeasure) and the 
 * pre-measure part "milli". <br>
 * This class handles vectors of:
 * - pre-measure factor (e.g. for "milli" with index #pmMilli the factor is 0.001)
 * - the exponent to the base of 10 of the pre-measure factor (e.g. for "milli" the exp10 is -3)
 * - the short label (e.g. for "milli" the short label is "m")
 * - the long label (e.g. for "milli" the long label is "milli")<br>
 * These vectors are accessed by the indices defined by the enum #ePreMeasure.<br>
 * The indices can be vice versa accessed by 
 * - pre-measure factor
 * - exp10
 * - short label
 * - long label
 */
class 
#ifdef _WIN32
FloatingMeasureDLL_API
#endif
 CPreMeasure : public CVectorHandle
{
    
public:
 
    ///////////////////////////////////////////////////
    // constructors / destructor
    ///////////////////////////////////////////////////
    /**
     * @brief default constructor:
     * initialize all member vectors of CPreMeasure:
     * - CPreMeasure::vdFactor
     * - CPreMeasure::vnExp10
     * - CPreMeasure::vstrShort
     * - CPreMeasure::vstrLong
     *
     */
    CPreMeasure();

    /**
     * @brief Destructor
     */
    ~CPreMeasure();
    
    ///////////////////////////////////////////////////
    // public printing functions
    ///////////////////////////////////////////////////
    /**
     * @brief returns all representations in a string
     * 
     * @return string: output string
     */
    string DebugOut(const int nIndex);
    /**
     * @brief returns all representations in a string
     * 
     * @param PreMeasureEnum p_PreMeasureEnum:...
     * @return string
     */
    string DebugOut(const ePreMeasure PreMeasureEnum);

    ///////////////////////////////////////////////////
    // element getter (by ID)
    ///////////////////////////////////////////////////
    /**
     * @brief returns the exp10 (see CPreMeasure::vnExp10) for a given pre-measure
     * 
     * @param nExp10Idx p_nExp10Idx: is e.g. ePreMeasure::pmMilli (returns -3 in this case)
     * @return int
     */
    int Exp10(const int nExp10Idx)
    {       
        return GetElementFromVectorByIndex(vnExp10, nExp10Idx);
    }
        
    ///////////////////////////////////////////////////
    // ID getter (by elements)
    ///////////////////////////////////////////////////
    /**
     * @brief returns the enum (index) of the pre-measure by searching the vstrShort
     * 
     * @param strShortLabel: short label of the enum (e.g. "m" returns ePreMeasure::pmMilli)
     * @return ePreMeasure
     */
    ePreMeasure GetIDByShortLabel( const string& strShortLabel)
    {
        return (ePreMeasure) CVectorHandle::GetIndexByShortLabel(strShortLabel);
    }
        
    /**
     * @brief returns the enum (index) of the pre-measure by searching the vstrLong
     * 
     * @param strLongLabel: long label of the enum (e.g. "milli" 
     * @return ePreMeasure: the pre-measure index (e.g. ePreMeasure::pmMilli)
     */
    ePreMeasure GetIDByLongLabel( const string& strLongLabel)
    {
        return (ePreMeasure) CVectorHandle::GetIndexByLongLabel(strLongLabel);
    }
        
    /**
     * @brief returns the enum (index) of the pre-measure by searching the vdFactor
     * 
     * @param dPreMeasureFactor p_dPreMeasureFactor: user given factor (e.g. 0.001 returns ePreMeasure::pmMilli)
     * @return ePreMeasure
     */
    ePreMeasure GetIDByFactor( const double dPreMeasureFactor);
        
    /**
     * @brief returns the enum (index) of the pre-measure by searching the vnExp10
     * 
     * @param nExp10 ${p_nExp10:...}
     * @return ePreMeasure
     */
    ePreMeasure GetIDByExp10( const int nExp10);
    
protected:
    
    /**
     * @brief the exponents to the base of 10 (exp10 from now on) of the corresponding
     *        factors stored in CVectorHandle::vdFactor
     * 
     */
    vector<int>* vnExp10;
    
};

/**
 * @brief a singleton instance of the class CPreMeasure: use this for 
 *        efficient memory handling
 * 
 */
typedef CSingleton<CPreMeasure> CPreMeasureSingleton;


/**
 * @brief Short cut to the singleton instance of CPreMeasure
 * 
 */
#define PRE CPreMeasureSingleton::instance()
 

#endif // CPREUNIT_H
