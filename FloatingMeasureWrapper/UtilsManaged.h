#pragma once
using namespace System;

#include "Measure/PreMeasure.h"
#include "Measure/BaseMeasure.h"

namespace SimpleMeasureCLI
{
    public enum class ePreMeasureManaged : int
    {
        pmFemto = ePreMeasure::pmFemto, /*!<0 factor = 10 <SUP> ⁻15 </SUP>, exp10: -15, short: "f", long: "femto"   */
        pmFirst = ePreMeasure::pmFirst, /*!<0 starting index "femto"*/
        pmPiko = ePreMeasure::pmPiko,   /*!<1  :  factor = 10 <SUP>⁻12</SUP>,  exp10: -12, short: "p",   long: "piko" */
        pmNano = ePreMeasure::pmNano,   /*!<2  :  factor = 10 <SUP>⁻9 </SUP>,  exp10: -9,  short: "n",   long: "nano" */
        pmMicro = ePreMeasure::pmMicro, /*!<3  :  factor = 10 <SUP>⁻6 </SUP>,  exp10: ⁻6,  short: \"&mu,\", long: "micro"*/
        pmMilli = ePreMeasure::pmMilli, /*!<4  :  factor = 10 <SUP>⁻3 </SUP>,  exp10: ⁻3,  short: "m",   long: "milli"*/
        pmCenti = ePreMeasure::pmCenti, /*!<5  :  factor = 10 <SUP>⁻2 </SUP>,  exp10: ⁻2,  short: "c",   long: "centi"*/
        pmDeci = ePreMeasure::pmDeci,   /*!<6  :  factor = 10 <SUP>⁻1 </SUP>,  exp10: ⁻1,  short: "d",   long: "deci" */
        pmIdent = ePreMeasure::pmIdent, /*!<7  :  factor = 10 <SUP> 0 </SUP>,  exp10:  0,  short: "",    long: ""     */
        pmDeca = ePreMeasure::pmDeca,   /*!<8  :  factor = 10 <SUP>+1 </SUP>,  exp10: +1,  short: "da",  long: "deca" */
        pmHecto = ePreMeasure::pmHecto, /*!<9  :  factor = 10 <SUP>+2 </SUP>,  exp10: +2,  short: "h",   long: "hecto"*/
        pmKilo = ePreMeasure::pmKilo,   /*!<10 :  factor = 10 <SUP>+3 </SUP>,  exp10: +3,  short: "k",   long: "kilo" */
        pmMega = ePreMeasure::pmMega,   /*!<11 :  factor = 10 <SUP>+6 </SUP>,  exp10: +6,  short: "M",   long: "mega" */
        pmGiga = ePreMeasure::pmGiga,   /*!<12 :  factor = 10 <SUP>+9 </SUP>,  exp10: +9,  short: "G",   long: "giga" */
        pmTera = ePreMeasure::pmTera,   /*!<13 :  factor = 10 <SUP>+12</SUP>,  exp10: +12, short: "T",   long: "tera" */
        pmPeta = ePreMeasure::pmPeta,   /*!<14 :  factor = 10 <SUP>+15</SUP>,  exp10: +15, short: "P",   long: "peta" */
        pmExa = ePreMeasure::pmExa,     /*!<15 :  factor = 10 <SUP>+18</SUP>,  exp10: +18, short: "E",   long: "exa"  */
        pmZetta = ePreMeasure::pmZetta, /*!<16 :  factor = 10 <SUP>+21</SUP>,  exp10: +21, short: "Z",   long: "zetta"*/
        pmYotta = ePreMeasure::pmYotta, /*!<17 :  factor = 10 <SUP>+24</SUP>,  exp10: +24, short: "Y",   long: "yotta"*/
        pmLast = ePreMeasure::pmLast,   /*!<18 :  invalid last index */
        pmUnknown = ePreMeasure::pmLast /*!<18 :  identical with last index */
    };
    public enum class eBaseMeasureManaged : int
    {
        bmNumber = eBaseMeasure::bmNumber,                  /*!<0  : simple measure-less number 1, short: "1"*/
        bmFirst = eBaseMeasure::bmNumber,                   /*!<0  : simple measure-less number is the starting element*/
        bmVolt = eBaseMeasure::bmVolt,                      /*!<1  : factor: 1, offset: 0, SIindex:1, short: "V", long: "volt"*/
        bmAmpere = eBaseMeasure::bmAmpere,                  /*!<2  : factor: 1, offset: 0, SIindex:2, short: "A", long: "ampere"*/
        bmDegKelvin = eBaseMeasure::bmDegKelvin,            /*!<3  : factor: 1, offset: 0, SIindex:3, short: "°K", long: "degree kelvin"*/
        bmDegCelsius = eBaseMeasure::bmDegCelsius,          /*!<4  : factor: 1, offset: -273,15, SIindex:3, short: "°C", long: "degree celsius"*/
        bmDegFahrenheit = eBaseMeasure::bmDegFahrenheit,    /*!<5  : factor: 5/9, offset: 32-5./9.*273.15, SIindex:3, short: "°F", long: "degree fahrenheit"*/
        bmOhm = eBaseMeasure::bmOhm,                        /*!<6  : factor: 1, offset: 0, SIindex:6, short: \"&Omega,\", long: "ohm"*/
        bmFarad = eBaseMeasure::bmFarad,                    /*!<7  : factor: 1, offset: 0, SIindex:7, short: "F", long: "farad"*/
        bmHertz = eBaseMeasure::bmHertz,                    /*!<8  : factor: 1, offset: 0, SIindex:8, short: "Hz", long: "hertz"*/
        bmSecond = eBaseMeasure::bmSecond,                  /*!<9  : factor: 1, offset: 0, SIindex:9, short: "s", long: "second"*/
        bmMinute = eBaseMeasure::bmMinute,                  /*!<10 : factor: 60,offset: 0, SIindex:9, short: "min", long: "minute"*/
        bmHour = eBaseMeasure::bmHour,                      /*!<11 : factor: 3600,offset: 0, SIindex:9, short: "h", long: "hour"*/
        bmDay = eBaseMeasure::bmDay,                        /*!<12  : factor: 3600*24,offset: 0, SIindex:9, short: "d", long: "day"*/
        bmMeter = eBaseMeasure::bmMeter,                    /*!<12  : factor: 1, offset: 0, SIindex:13, short: "m", long: "meter"*/
        bmInch = eBaseMeasure::bmInch,                      /*!<13  : factor: 0.0254, offset: 0, SIindex:13, short: "in", long: "inch"*/
        bmFoot = eBaseMeasure::bmFoot,                      /*!<14  : factor: 0.3048, offset: 0, SIindex:13, short: "ft", long: "foot"*/
        bmYard = eBaseMeasure::bmYard,                      /*!<15  : factor: 0.9144, offset: 0, SIindex:13, short: "yd", long: "yard"*/
        bmMile = eBaseMeasure::bmMile,                      /*!<16  : factor: 1609.344, offset: 0, SIindex:13, short: "mi", long: "mile"*/
        bmLast = eBaseMeasure::bmLast,                      /*!<17 : last invalid item*/
        bmUnknown = eBaseMeasure::bmLast                    /*!<18 : unknown item identical with last invalid item*/
    };
}