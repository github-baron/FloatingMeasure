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

#ifndef CBASEMEASURE_H
#define CBASEMEASURE_H


#include"VectorHandle.h"

/**
 * 
 * @brief enum for indexing the vectors of CBaseMeasure
 * 
 */      
enum eBaseMeasure 
{
    bmNumber = 0,       /*!<0  : simple measure-less number 1, short: "1"*/
    bmFirst = bmNumber, /*!<0  : simple measure-less number is the starting element*/
    bmVolt,             /*!<1  : factor: 1, offset: 0, SIindex:1, short: "V", long: "volt"*/
    bmAmpere,           /*!<2  : factor: 1, offset: 0, SIindex:2, short: "A", long: "ampere"*/
    bmDegKelvin,        /*!<3  : factor: 1, offset: 0, SIindex:3, short: "°K", long: "degree kelvin"*/
    bmDegCelsius,       /*!<4  : factor: 1, offset: -273,15, SIindex:3, short: "°C", long: "degree celsius"*/
    bmDegFahrenheit,    /*!<5  : factor: 5/9, offset: 32-5./9.*273.15, SIindex:3, short: "°F", long: "degree fahrenheit"*/
    bmOhm,              /*!<6  : factor: 1, offset: 0, SIindex:6, short: \"&Omega;\", long: "ohm"*/
    bmFarad,            /*!<7  : factor: 1, offset: 0, SIindex:7, short: "F", long: "farad"*/
    bmHertz,            /*!<8  : factor: 1, offset: 0, SIindex:8, short: "Hz", long: "hertz"*/
    bmSecond,           /*!<9  : factor: 1, offset: 0, SIindex:9, short: "s", long: "second"*/
    bmMinute,           /*!<10 : factor: 60,offset: 0, SIindex:9, short: "min", long: "minute"*/
    bmHour,             /*!<11 : factor: 3600,offset: 0, SIindex:9, short: "h", long: "hour"*/
    bmDay,              /*!<12  : factor: 3600*24,offset: 0, SIindex:9, short: "d", long: "day"*/
    bmMeter,	        /*!<12  : factor: 1, offset: 0, SIindex:13, short: "m", long: "meter"*/
    bmInch, 	        /*!<13  : factor: 0.0254, offset: 0, SIindex:13, short: "in", long: "inch"*/
    bmFoot, 	        /*!<14  : factor: 0.3048, offset: 0, SIindex:13, short: "ft", long: "foot"*/
    bmYard, 	        /*!<15  : factor: 0.9144, offset: 0, SIindex:13, short: "yd", long: "yard"*/
    bmMile, 	        /*!<16  : factor: 1609.344, offset: 0, SIindex:13, short: "mi", long: "mile"*/
    bmLast,             /*!<17 : last invalid item*/
    bmUnknown = bmLast  /*!<18 : unknown item identical with last invalid item*/
};
/**
 * @brief CBaseMeasure: represents the base-measure part of a measure.<br> 
 * For example milli degree celsius consists of the base-measure part "degree celsius" (see CBaseMeasure)
 * and the pre-measure part "milli" (see CPreMeasure). <br>
 * This class handles vectors of:
 * - SI index (e.g. for #bmDegCelsius the SI index is #bmDegKelvin)
 * - base-measure factor (e.g. for °F with index #bmDegFahrenheit the factor for the conversion to the SI measure °K with index #bmDegKelvin is 5/9)
 * - base-measure offset (e.g. for °C with index #bmDegCelsius the offset for the conversion to the SI measure °K with index #bmDegKelvin is 273.15°K)
 * - the short label (e.g. for Volt with the index #bmVolt the short label is "V")
 * - the long label (e.g. for  Volt with the index #bmVolt the short label is "volt")<br>
 * These vectors are accessed by the indices defined by the enum #eBaseMeasure.<br>
 */
class 
#ifdef _WIN32
FloatingMeasureDLL_API
#endif
 CBaseMeasure : public CVectorHandle
{
    
public:

    /**
     * @brief default constructor: <br>
     *  initialize all member vectors 
     * - CBaseMeasure::vstrShort 
     * - CBaseMeasure::vstrLong
     * - CBaseMeasure::vnSIIndex
     * - CBaseMeasure::vdOffset
     * - CBaseMeasure::vdFactor
     * 
     */
    CBaseMeasure();

    /**
     * @brief destructor:
     * clears all member vectors 
     * - CBaseMeasure::vstrShort 
     * - CBaseMeasure::vstrLong
     * - CBaseMeasure::vnSIIndex
     * - CBaseMeasure::vdOffset
     * - CBaseMeasure::vdFactor
     *  clears all member vectors
     * 
     */
    ~CBaseMeasure();
    
    /**
     * @brief returns the offset for the converstion to the SI measure for the given #eBaseMeasure
     * 
     * @param BaseMeasureEnum: index of the 
     * @return const double
     */
    const double Offset(unsigned int BaseMeasureEnum) 
    {
        return GetElementFromVectorByIndex(vdOffset, BaseMeasureEnum);        
    }

    /**
     * @brief returns the #eBaseMeasure of the SI measure for the given #eBaseMeasure
     * 
     * @param BaseMeasureEnum p_BaseMeasureEnum:...
     * @return eBaseMeasure
     */
    eBaseMeasure SIID(const eBaseMeasure BaseMeasureEnum) 
    {
        return (eBaseMeasure) GetElementFromVectorByIndex(vnSIIndex, (int)BaseMeasureEnum);        
    }

    /**
     * @brief output for debugging purpose for given index
     * 
     * @param BaseMeasureEnum: index of base measure
     * @return const string
     */
    const string DebugOut(const eBaseMeasure BaseMeasureEnum); 

        
    /**
     * @brief returns the enum (index) of the base measure by searching the vstrShort->.
     * 
     * @param strShortLabel: short label of the base measure (e.g. "V" )
     * @return eBaseMeasure: the base-measure index (e.g. eBaseMeasure::bmVolt)
     */
    eBaseMeasure GetIDByShortLabel( const string& strShortLabel)
    {
        return (eBaseMeasure) CVectorHandle::GetIndexByShortLabel(strShortLabel);
    }
        
    /**
     * @brief returns the enum (index) of the base measure by searching the vstrLong
     * 
     * @param strLongLabel: 
     * @return eBaseMeasure
     */
    eBaseMeasure GetIDByLongLabel( const string& strLongLabel)
    {
        return (eBaseMeasure) CVectorHandle::GetIndexByLongLabel(strLongLabel);
    }    
    /**
     * @brief keeps the index of the corresponding SI unit: is its own unit 
     *        in case it is the SI unit itself
     * 
     */
    vector<int>* vnSIIndex;    
    
    /**
     * @brief keeps the offset for the conversion to the SI Unit
     * 
     */
    vector<double>* vdOffset;
};


/**
 * @brief use CBaseMeasure as a singleton 
 * 
 */
typedef CSingleton<CBaseMeasure>    CBaseMeasureSingleton;
/**
 * @brief shortcut to the singleton representation of CBaseMeasure
 * 
 */
#define BASE                        CBaseMeasureSingleton::instance()
    

#endif // CBASEMEASURE_H
