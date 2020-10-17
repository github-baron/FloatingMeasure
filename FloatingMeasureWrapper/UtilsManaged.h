#pragma once
using namespace System;
namespace SimpleMeasureCLI
{
    public enum class ePreMeasureManaged : int
    {
        pmFemto = 0,        /*!<0 factor = 10 <SUP> ⁻15 </SUP>, exp10: -15, short: "f", long: "femto"   */
        pmFirst = pmFemto,  /*!<0 starting index "femto"*/
        pmPiko = 1,         /*!<1  :  factor = 10 <SUP>⁻12</SUP>,  exp10: -12, short: "p",   long: "piko" */
        pmNano = 2,         /*!<2  :  factor = 10 <SUP>⁻9 </SUP>,  exp10: -9,  short: "n",   long: "nano" */
        pmMicro = 3,        /*!<3  :  factor = 10 <SUP>⁻6 </SUP>,  exp10: ⁻6,  short: \"&mu,\", long: "micro"*/
        pmMilli = 4,        /*!<4  :  factor = 10 <SUP>⁻3 </SUP>,  exp10: ⁻3,  short: "m",   long: "milli"*/
        pmCenti = 5,        /*!<5  :  factor = 10 <SUP>⁻2 </SUP>,  exp10: ⁻2,  short: "c",   long: "centi"*/
        pmDeci = 6,         /*!<6  :  factor = 10 <SUP>⁻1 </SUP>,  exp10: ⁻1,  short: "d",   long: "deci" */
        pmIdent = 7,        /*!<7  :  factor = 10 <SUP> 0 </SUP>,  exp10:  0,  short: "",    long: ""     */
        pmDeca = 8,         /*!<8  :  factor = 10 <SUP>+1 </SUP>,  exp10: +1,  short: "da",  long: "deca" */
        pmHecto = 9,        /*!<9  :  factor = 10 <SUP>+2 </SUP>,  exp10: +2,  short: "h",   long: "hecto"*/
        pmKilo = 10,        /*!<10 :  factor = 10 <SUP>+3 </SUP>,  exp10: +3,  short: "k",   long: "kilo" */
        pmMega = 11,        /*!<11 :  factor = 10 <SUP>+6 </SUP>,  exp10: +6,  short: "M",   long: "mega" */
        pmGiga = 12,        /*!<12 :  factor = 10 <SUP>+9 </SUP>,  exp10: +9,  short: "G",   long: "giga" */
        pmTera = 13,        /*!<13 :  factor = 10 <SUP>+12</SUP>,  exp10: +12, short: "T",   long: "tera" */
        pmPeta = 14,        /*!<14 :  factor = 10 <SUP>+15</SUP>,  exp10: +15, short: "P",   long: "peta" */
        pmExa = 15,         /*!<15 :  factor = 10 <SUP>+18</SUP>,  exp10: +18, short: "E",   long: "exa"  */
        pmZetta = 16,       /*!<16 :  factor = 10 <SUP>+21</SUP>,  exp10: +21, short: "Z",   long: "zetta"*/
        pmYotta = 17,       /*!<17 :  factor = 10 <SUP>+24</SUP>,  exp10: +24, short: "Y",   long: "yotta"*/
        pmLast = 18,        /*!<18 :  invalid last index */
        pmUnknown = pmLast, /*!<18 :  identical with last index */
    };
    public enum class eBaseMeasureManaged : int
    {
        bmNumber = 0,         /*!<0  : simple measure-less number 1, short: "1"*/
        bmFirst = bmNumber,   /*!<0  : simple measure-less number is the starting element*/
        bmVolt = 1,           /*!<1  : factor: 1, offset: 0, SIindex:1, short: "V", long: "volt"*/
        bmAmpere = 2,         /*!<2  : factor: 1, offset: 0, SIindex:2, short: "A", long: "ampere"*/
        bmDegKelvin = 4,      /*!<3  : factor: 1, offset: 0, SIindex:3, short: "°K", long: "degree kelvin"*/
        bmDegCelsius = 5,     /*!<4  : factor: 1, offset: -273,15, SIindex:3, short: "°C", long: "degree celsius"*/
        bmDegFahrenheit = 6,  /*!<5  : factor: 5/9, offset: 32-5./9.*273.15, SIindex:3, short: "°F", long: "degree fahrenheit"*/
        bmOhm = 7,            /*!<6  : factor: 1, offset: 0, SIindex:6, short: \"&Omega,\", long: "ohm"*/
        bmFarad = 8,          /*!<7  : factor: 1, offset: 0, SIindex:7, short: "F", long: "farad"*/
        bmHertz = 9,          /*!<8  : factor: 1, offset: 0, SIindex:8, short: "Hz", long: "hertz"*/
        bmSecond = 11,        /*!<9  : factor: 1, offset: 0, SIindex:9, short: "s", long: "second"*/
        bmMinute = 12,        /*!<10 : factor: 60,offset: 0, SIindex:9, short: "min", long: "minute"*/
        bmHour = 13,          /*!<11 : factor: 3600,offset: 0, SIindex:9, short: "h", long: "hour"*/
        bmDay = 14,           /*!<12  : factor: 3600*24,offset: 0, SIindex:9, short: "d", long: "day"*/
        bmMeter = 15,         /*!<12  : factor: 1, offset: 0, SIindex:13, short: "m", long: "meter"*/
        bmInch = 16,          /*!<13  : factor: 0.0254, offset: 0, SIindex:13, short: "in", long: "inch"*/
        bmFoot = 17,          /*!<14  : factor: 0.3048, offset: 0, SIindex:13, short: "ft", long: "foot"*/
        bmYard = 18,          /*!<15  : factor: 0.9144, offset: 0, SIindex:13, short: "yd", long: "yard"*/
        bmMile = 19,          /*!<16  : factor: 1609.344, offset: 0, SIindex:13, short: "mi", long: "mile"*/
        bmLast = 20,          /*!<17 : last invalid item*/
        bmUnknown = bmLast,   /*!<18 : unknown item identical with last invalid item*/
    };
}