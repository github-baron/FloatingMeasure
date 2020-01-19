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

#ifndef CVECTORHANDLE_H
#define CVECTORHANDLE_H

#include<Utils/Utils.h>

/**
 * @brief This class keeps three vectors (two string : Short and Long and
 *        one double : Factor). These vectors are common to classes CPreMeasure
 *        and CBaseMeasure and are therefore packed into this class for vector
 *        handling.
 * 
 */
class DLLEXPORT_CMD CVectorHandle
{
    
public:    
    ///////////////////////////////////////////////////
    // constructor / destructor
    ///////////////////////////////////////////////////    
    /**
     * @brief does nothing
     * 
     */
    CVectorHandle();
    
    /**
     * @brief destructor: calls CVectorHandle::_DeInit()
     * 
     */
    ~CVectorHandle(){ _DeInit();}

    ///////////////////////////////////////////////////
    // index getter
    ///////////////////////////////////////////////////
    /**
     * @brief returns the index of the pre-unit if the user given string matches one of the elemens in CPreUnit::m_vstrPreUnitShort
     * 
     * @param strShortLabel p_strPreUnitShortLabel:user given short label of the demanded unit
     * @return const unsigned int&
     */    
    int GetIndexByShortLabel(const string& strShortLabel)
    {
        return FindElementInVectorGetIndex(strShortLabel, vstrShort, (int)(vstrShort.size()-1));
    }

    /**
     * @brief returns the index of the pre-unit if the user given string matches one of the elemens in CPreUnit::m_vstrPreUnitLong
     * 
     * @param strLongLabel p_strPreUnitLongLabel: user given long label of the demanded unit
     * @return const unsigned int&
     */
    int GetIndexByLongLabel(const string& strLongLabel)
    {
        return FindElementInVectorGetIndex(strLongLabel, vstrLong, (int)(vstrLong.size()-1));
    }

    ///////////////////////////////////////////////////
    // element getter
    ///////////////////////////////////////////////////
    /**
     * @brief gets element from CVectorHandle::vstrShort by index
     * 
     * @param uiIndex: index
     * @return string: long label
     */
    const string& Long(const unsigned int uiIndex) 
    {
        return GetElementFromVectorByIndex(vstrLong, uiIndex);
    }
    
    /**
     * @brief gets element from CVectorHandle::vstrLong by index
     * 
     * @param uiIndex: index
     * @return string: short label
     */
    const string& Short(const unsigned int uiIndex) 
    {
        return GetElementFromVectorByIndex(vstrShort, uiIndex);
    }
    
    /**
     * @brief gets element from CVectorHandle::vdFactor by index 
     * 
     * @param uiIndex: index 
     * @return double: factor
     */
    const double Factor(const unsigned int uiIndex) 
    {
        return GetElementFromVectorByIndex(vdFactor, uiIndex);
    }
 
protected:
    ///////////////////////////////////////////////////
    // protected functions
    ///////////////////////////////////////////////////
    /**
     * @brief software interface for intializing all member vectors 
     * these are the vectors:
     * - CVectorHandle::vdFactor
     * - CVectorHandle::vstrShort
     * - CVectorHandle::vstrLong
     * 
     */
    virtual void _Init() = 0;
    
    /**
     * @brief clear all member vectors
     * 
     */
    virtual void _DeInit();
    
    ///////////////////////////////////////////////////
    // protected variables
    ///////////////////////////////////////////////////
    /**
     * @brief vector keeping all the factors:<br>
     * e.g. 
     * - CPreMeasure:  milli --> 0.001
     * - CBaseMeasure: °F --> 5/9 (SI recalculation factor for °K)
     * 
     */
    vector<double> vdFactor;
    
    /**
     * @brief vector keeping the long label<br>
     * e.g. 
     * - CPreMeasure:  milli --> "milli"
     * - CBaseMeasure: volt --> "volt"
     * 
     */
    vector<string> vstrLong;
 
    /**
     * @brief vector keeping the short label:<br>
     * e.g. 
     * - CPreMeasure:  milli --> "m"
     * - CBaseMeasure: volt --> "V"
     * 
     */
    vector<string> vstrShort;    
  
};

#endif // CVECTORHANDLE_H
