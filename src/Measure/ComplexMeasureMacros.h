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

#ifndef CCOMPLEXMEASUREMACROS_H
#define CCOMPLEXMEASUREMACROS_H

// macros for easy to use ComplexMeasures 
#define    fV CComplexMeasure(pmFemto,bmVolt)   ///\def  fV macro definition for femtovolt
#define    pV CComplexMeasure(pmPiko, bmVolt)   ///\def  pV macro definition for pikovolt
#define    nV CComplexMeasure(pmNano, bmVolt)   ///\def  nV macro definition for nanovolt
#define    uV CComplexMeasure(pmMicro,bmVolt)   ///\def  uV macro definition for microvolt
#define    mV CComplexMeasure(pmMilli,bmVolt)   ///\def  mV macro definition for millivolt
#define    cV CComplexMeasure(pmCenti,bmVolt)   ///\def  cV macro definition for centivolt
#define    dV CComplexMeasure(pmDeci, bmVolt)   ///\def  dV macro definition for decivolt
#define     V CComplexMeasure(pmIdent,bmVolt)   ///\def   V macro definition for volt
#define   daV CComplexMeasure(pmDeca, bmVolt)   ///\def daV macro definition for decavolt
#define    HV CComplexMeasure(pmHecto,bmVolt)   ///\def  HV macro definition for hectovolt
#define    kV CComplexMeasure(pmKilo, bmVolt)   ///\def  kV macro definition for kilovolt
#define    MV CComplexMeasure(pmMega, bmVolt)   ///\def  MV macro definition for megavolt
#define    GV CComplexMeasure(pmGiga, bmVolt)   ///\def  GV macro definition for gigavolt
#define    TV CComplexMeasure(pmTera, bmVolt)   ///\def  TV macro definition for teravolt
#define    PV CComplexMeasure(pmPeta, bmVolt)   ///\def  PV macro definition for petavolt
#define    EV CComplexMeasure(pmExa,  bmVolt)   ///\def  EV macro definition for exavolt
#define    ZV CComplexMeasure(pmZetta,bmVolt)   ///\def  ZV macro definition for zettavolt
#define    YV CComplexMeasure(pmYotta,bmVolt)   ///\def  YV macro definition for yottavolt


#define  fA   CComplexMeasure(pmFemto,bmAmpere) ///\def  fA macro definition for femtoampere  
#define  pA   CComplexMeasure(pmPiko, bmAmpere) ///\def  pA macro definition for pikoampere 
#define  nA   CComplexMeasure(pmNano, bmAmpere) ///\def  nA macro definition for nanoampere 
#define  uA   CComplexMeasure(pmMicro,bmAmpere) ///\def  uA macro definition for microampere 
#define  mA   CComplexMeasure(pmMilli,bmAmpere) ///\def  mA macro definition for milliampere 
#define  cA   CComplexMeasure(pmCenti,bmAmpere) ///\def  cA macro definition for centiampere 
#define  dA   CComplexMeasure(pmDeci, bmAmpere) ///\def  dA macro definition for deciampere 
#define   A   CComplexMeasure(pmIdent,bmAmpere) ///\def   A macro definition for ampere 
#define daA   CComplexMeasure(pmDeca, bmAmpere) ///\def daA macro definition for decaampere 
#define  HA   CComplexMeasure(pmHecto,bmAmpere) ///\def  HA macro definition for hectoampere  
#define  kA   CComplexMeasure(pmKilo, bmAmpere) ///\def  kA macro definition for kiloampere 
#define  MA   CComplexMeasure(pmMega, bmAmpere) ///\def  MA macro definition for megaampere 
#define  GA   CComplexMeasure(pmGiga, bmAmpere) ///\def  GA macro definition for gigaampere 
#define  TA   CComplexMeasure(pmTera, bmAmpere) ///\def  TA macro definition for teraampere 
#define  PA   CComplexMeasure(pmPeta, bmAmpere) ///\def  PA macro definition for petaampere 
#define  EA   CComplexMeasure(pmExa,  bmAmpere) ///\def  EA macro definition for exaampere 
#define  ZA   CComplexMeasure(pmZetta,bmAmpere) ///\def  ZA macro definition for zettaampere 
#define  YA   CComplexMeasure(pmYotta,bmAmpere) ///\def  YA macro definition for yottaampere 


#define  fs   CComplexMeasure(pmFemto,bmSecond)  ///\def  fs macro definition for femtosecond
#define  ps   CComplexMeasure(pmPiko, bmSecond)  ///\def  ps macro definition for pikosecond
#define  ns   CComplexMeasure(pmNano, bmSecond)  ///\def  ns macro definition for nanosecond
#define  us   CComplexMeasure(pmMicro,bmSecond)  ///\def  us macro definition for microsecond
#define  ms   CComplexMeasure(pmMilli,bmSecond)  ///\def  ms macro definition for millisecond
#define  cs   CComplexMeasure(pmCenti,bmSecond)  ///\def  cs macro definition for centisecond
#define  ds   CComplexMeasure(pmDeci, bmSecond)  ///\def  ds macro definition for decisecond
#define   s   CComplexMeasure(pmIdent,bmSecond)  ///\def   s macro definition for second
#define das   CComplexMeasure(pmDeca, bmSecond)  ///\def das macro definition for decasecond
#define  Hs   CComplexMeasure(pmHecto,bmSecond)  ///\def  Hs macro definition for ectosecond 
#define  ks   CComplexMeasure(pmKilo, bmSecond)  ///\def  ks macro definition for kilosecond
#define  Ms   CComplexMeasure(pmMega, bmSecond)  ///\def  Ms macro definition for megasecond
#define  Gs   CComplexMeasure(pmGiga, bmSecond)  ///\def  Gs macro definition for gigasecond
#define  Ts   CComplexMeasure(pmTera, bmSecond)  ///\def  Ts macro definition for terasecond
#define  Ps   CComplexMeasure(pmPeta, bmSecond)  ///\def  Ps macro definition for petasecond
#define  Es   CComplexMeasure(pmExa,  bmSecond)  ///\def  Es macro definition for exasecond
#define  Zs   CComplexMeasure(pmZetta,bmSecond)  ///\def  Zs macro definition for zettasecond
#define  Ys   CComplexMeasure(pmYotta,bmSecond)  ///\def  Ys macro definition for yottasecond
#define   m   CComplexMeasure(pmIdent,bmMinute)  ///\def   m macro definition for minute
#define   h   CComplexMeasure(pmIdent,bmHour)    ///\def   h macro definition for hour 
#define   d   CComplexMeasure(pmIdent,bmDay)     ///\def   d macro definition for day 

#define  fC   CComplexMeasure(pmFemto,bmDegCelsius)       ///\def   fC   macro definition for femto-degree celsiusus
#define  pC   CComplexMeasure(pmPiko, bmDegCelsius)       ///\def   pC   macro definition for piko-degree celsiusus
#define  nC   CComplexMeasure(pmNano, bmDegCelsius)       ///\def   nC   macro definition for nano-degree celsiusus
#define  uC   CComplexMeasure(pmMicro,bmDegCelsius)       ///\def   uC   macro definition for micro-degree celsiusus
#define  mC   CComplexMeasure(pmMilli,bmDegCelsius)       ///\def   mC   macro definition for milli-degree celsiusus
#define  cC   CComplexMeasure(pmCenti,bmDegCelsius)       ///\def   cC   macro definition for centi-degree celsiusus
#define  dC   CComplexMeasure(pmDeci, bmDegCelsius)       ///\def   dC   macro definition for deci-degree celsiusus
#define   C   CComplexMeasure(pmIdent,bmDegCelsius)       ///\def    C   macro definition for ident-degree celsiusus
#define daC   CComplexMeasure(pmDeca, bmDegCelsius)       ///\def  daC   macro definition for deca-degree celsiusus
#define  HC   CComplexMeasure(pmHecto,bmDegCelsius)       ///\def   HC   macro definition for hecto-degree celsiusus
#define  kC   CComplexMeasure(pmKilo, bmDegCelsius)       ///\def   kC   macro definition for kilo-degree celsiusus
#define  MC   CComplexMeasure(pmMega, bmDegCelsius)       ///\def   MC   macro definition for mega-degree celsiusus
#define  GC   CComplexMeasure(pmGiga, bmDegCelsius)       ///\def   GC   macro definition for giga-degree celsiusus
#define  TC   CComplexMeasure(pmTera, bmDegCelsius)       ///\def   TC   macro definition for tera-degree celsiusus
#define  PC   CComplexMeasure(pmPeta, bmDegCelsius)       ///\def   PC   macro definition for peta-degree celsiusus
#define  EC   CComplexMeasure(pmExa,  bmDegCelsius)       ///\def   EC   macro definition for exa-degree celsiusus
#define  ZC   CComplexMeasure(pmZetta,bmDegCelsius)       ///\def   ZC   macro definition for zetta-degree celsiusus
#define  YC   CComplexMeasure(pmYotta,bmDegCelsius)       ///\def   YC   macro definition for yotta-degree celsiusus

#define  fF   CComplexMeasure(pmFemto,bmDegFahrenheit)    ///\def   fF   macro definition for femto-degree fahrenheitnheit
#define  pF   CComplexMeasure(pmPiko, bmDegFahrenheit)    ///\def   pF   macro definition for piko-degree fahrenheitnheit
#define  nF   CComplexMeasure(pmNano, bmDegFahrenheit)    ///\def   nF   macro definition for nano-degree fahrenheitnheit
#define  uF   CComplexMeasure(pmMicro,bmDegFahrenheit)    ///\def   uF   macro definition for micro-degree fahrenheitnheit
#define  mF   CComplexMeasure(pmMilli,bmDegFahrenheit)    ///\def   mF   macro definition for milli-degree fahrenheitnheit
#define  cF   CComplexMeasure(pmCenti,bmDegFahrenheit)    ///\def   cF   macro definition for centi-degree fahrenheitnheit
#define  dF   CComplexMeasure(pmDeci, bmDegFahrenheit)    ///\def   dF   macro definition for deci-degree fahrenheitnheit
#define   F   CComplexMeasure(pmIdent,bmDegFahrenheit)    ///\def    F   macro definition for ident-degree fahrenheitnheit
#define daF   CComplexMeasure(pmDeca, bmDegFahrenheit)    ///\def  daF   macro definition for deca-degree fahrenheitnheit
#define  HF   CComplexMeasure(pmHecto,bmDegFahrenheit)    ///\def   HF   macro definition for hecto-degree fahrenheitnheit
#define  kF   CComplexMeasure(pmKilo, bmDegFahrenheit)    ///\def   kF   macro definition for kilo-degree fahrenheitnheit
#define  MF   CComplexMeasure(pmMega, bmDegFahrenheit)    ///\def   MF   macro definition for mega-degree fahrenheitnheit
#define  GF   CComplexMeasure(pmGiga, bmDegFahrenheit)    ///\def   GF   macro definition for giga-degree fahrenheitnheit
#define  TF   CComplexMeasure(pmTera, bmDegFahrenheit)    ///\def   TF   macro definition for tera-degree fahrenheitnheit
#define  PF   CComplexMeasure(pmPeta, bmDegFahrenheit)    ///\def   PF   macro definition for peta-degree fahrenheitnheit
#define  EF   CComplexMeasure(pmExa,  bmDegFahrenheit)    ///\def   EF   macro definition for exa-degree fahrenheitnheit
#define  ZF   CComplexMeasure(pmZetta,bmDegFahrenheit)    ///\def   ZF   macro definition for zetta-degree fahrenheitnheit
#define  YF   CComplexMeasure(pmYotta,bmDegFahrenheit)    ///\def   YF   macro definition for yotta-degree fahrenheitnheit

#define  fK   CComplexMeasure(pmFemto,bmDegKelvin)        ///\def   fK   macro definition for femto-degree kelvin
#define  pK   CComplexMeasure(pmPiko, bmDegKelvin)        ///\def   pK   macro definition for piko-degree kelvin
#define  nK   CComplexMeasure(pmNano, bmDegKelvin)        ///\def   nK   macro definition for nano-degree kelvin
#define  uK   CComplexMeasure(pmMicro,bmDegKelvin)        ///\def   uK   macro definition for micro-degree kelvin
#define  mK   CComplexMeasure(pmMilli,bmDegKelvin)        ///\def   mK   macro definition for milli-degree kelvin
#define  cK   CComplexMeasure(pmCenti,bmDegKelvin)        ///\def   cK   macro definition for centi-degree kelvin
#define  dK   CComplexMeasure(pmDeci, bmDegKelvin)        ///\def   dK   macro definition for deci-degree kelvin
#define   K   CComplexMeasure(pmIdent,bmDegKelvin)        ///\def    K   macro definition for ident-degree kelvin
#define daK   CComplexMeasure(pmDeca, bmDegKelvin)        ///\def  daK   macro definition for deca-degree kelvin
#define  HK   CComplexMeasure(pmHecto,bmDegKelvin)        ///\def   HK   macro definition for hecto-degree kelvin
#define  kK   CComplexMeasure(pmKilo, bmDegKelvin)        ///\def   kK   macro definition for kilo-degree kelvin
#define  MK   CComplexMeasure(pmMega, bmDegKelvin)        ///\def   MK   macro definition for mega-degree kelvin
#define  GK   CComplexMeasure(pmGiga, bmDegKelvin)        ///\def   GK   macro definition for giga-degree kelvin
#define  TK   CComplexMeasure(pmTera, bmDegKelvin)        ///\def   TK   macro definition for tera-degree kelvin
#define  PK   CComplexMeasure(pmPeta, bmDegKelvin)        ///\def   PK   macro definition for peta-degree kelvin
#define  EK   CComplexMeasure(pmExa,  bmDegKelvin)        ///\def   EK   macro definition for exa-degree kelvin
#define  ZK   CComplexMeasure(pmZetta,bmDegKelvin)        ///\def   ZK   macro definition for zetta-degree kelvin
#define  YK   CComplexMeasure(pmYotta,bmDegKelvin)        ///\def   YK   macro definition for yotta-degree kelvin

#define  fOhm   CComplexMeasure(pmFemto,bmOhm)            ///\def   fOhm   macro definition for femtoohm  
#define  pOhm   CComplexMeasure(pmPiko, bmOhm)            ///\def   pOhm   macro definition for pikoohm  
#define  nOhm   CComplexMeasure(pmNano, bmOhm)            ///\def   nOhm   macro definition for nanoohm  
#define  uOhm   CComplexMeasure(pmMicro,bmOhm)            ///\def   uOhm   macro definition for microohm  
#define  mOhm   CComplexMeasure(pmMilli,bmOhm)            ///\def   mOhm   macro definition for milliohm  
#define  cOhm   CComplexMeasure(pmCenti,bmOhm)            ///\def   cOhm   macro definition for centiohm  
#define  dOhm   CComplexMeasure(pmDeci, bmOhm)            ///\def   dOhm   macro definition for deciohm  
#define   Ohm   CComplexMeasure(pmIdent,bmOhm)            ///\def    Ohm   macro definition for identohm  
#define daOhm   CComplexMeasure(pmDeca, bmOhm)            ///\def  daOhm   macro definition for decaohm  
#define  HOhm   CComplexMeasure(pmHecto,bmOhm)            ///\def   HOhm   macro definition for hectoohm  
#define  kOhm   CComplexMeasure(pmKilo, bmOhm)            ///\def   kOhm   macro definition for kiloohm  
#define  MOhm   CComplexMeasure(pmMega, bmOhm)            ///\def   MOhm   macro definition for megaohm  
#define  GOhm   CComplexMeasure(pmGiga, bmOhm)            ///\def   GOhm   macro definition for gigaohm  
#define  TOhm   CComplexMeasure(pmTera, bmOhm)            ///\def   TOhm   macro definition for teraohm  
#define  POhm   CComplexMeasure(pmPeta, bmOhm)            ///\def   POhm   macro definition for petaohm  
#define  EOhm   CComplexMeasure(pmExa,  bmOhm)            ///\def   EOhm   macro definition for exaohm  
#define  ZOhm   CComplexMeasure(pmZetta,bmOhm)            ///\def   ZOhm   macro definition for zettaohm  
#define  YOhm   CComplexMeasure(pmYotta,bmOhm)            ///\def   YOhm   macro definition for yottaohm 

#define  fHz   CComplexMeasure(pmFemto,bmHertz)           ///\def   fHz   macro definition for femtohertz 
#define  pHz   CComplexMeasure(pmPiko, bmHertz)           ///\def   pHz   macro definition for pikohertz 
#define  nHz   CComplexMeasure(pmNano, bmHertz)           ///\def   nHz   macro definition for nanohertz 
#define  uHz   CComplexMeasure(pmMicro,bmHertz)           ///\def   uHz   macro definition for microhertz 
#define  mHz   CComplexMeasure(pmMilli,bmHertz)           ///\def   mHz   macro definition for millihertz 
#define  cHz   CComplexMeasure(pmCenti,bmHertz)           ///\def   cHz   macro definition for centihertz 
#define  dHz   CComplexMeasure(pmDeci, bmHertz)           ///\def   dHz   macro definition for decihertz 
#define   Hz   CComplexMeasure(pmIdent,bmHertz)           ///\def    Hz   macro definition for identhertz 
#define daHz   CComplexMeasure(pmDeca, bmHertz)           ///\def  daHz   macro definition for decahertz 
#define  HHz   CComplexMeasure(pmHecto,bmHertz)           ///\def   HHz   macro definition for hectohertz 
#define  kHz   CComplexMeasure(pmKilo, bmHertz)           ///\def   kHz   macro definition for kilohertz 
#define  MHz   CComplexMeasure(pmMega, bmHertz)           ///\def   MHz   macro definition for megahertz 
#define  GHz   CComplexMeasure(pmGiga, bmHertz)           ///\def   GHz   macro definition for gigahertz 
#define  THz   CComplexMeasure(pmTera, bmHertz)           ///\def   THz   macro definition for terahertz 
#define  PHz   CComplexMeasure(pmPeta, bmHertz)           ///\def   PHz   macro definition for petahertz 
#define  EHz   CComplexMeasure(pmExa,  bmHertz)           ///\def   EHz   macro definition for exahertz 
#define  ZHz   CComplexMeasure(pmZetta,bmHertz)           ///\def   ZHz   macro definition for zettahertz 
#define  YHz   CComplexMeasure(pmYotta,bmHertz)           ///\def   YHz   macro definition for yottahertz 

// #define  f   CComplexMeasure(pmFemto,)   ///\def   f   macro definition for femto
// #define  p   CComplexMeasure(pmPiko, )   ///\def   p   macro definition for  piko
// #define  n   CComplexMeasure(pmNano, )   ///\def   n   macro definition for  nano
// #define  u   CComplexMeasure(pmMicro,)   ///\def   u   macro definition for micro
// #define  m   CComplexMeasure(pmMilli,)   ///\def   m   macro definition for milli
// #define  c   CComplexMeasure(pmCenti,)   ///\def   c   macro definition for centi
// #define  d   CComplexMeasure(pmDeci, )   ///\def   d   macro definition for  deci
// #define      CComplexMeasure(pmIdent,)   ///\def       macro definition for      
// #define da   CComplexMeasure(pmDeca, )   ///\def  da   macro definition for  deca
// #define  H   CComplexMeasure(pmHecto,)   ///\def   H   macro definition for hecto 
// #define  k   CComplexMeasure(pmKilo, )   ///\def   k   macro definition for  kilo
// #define  M   CComplexMeasure(pmMega, )   ///\def   M   macro definition for  mega
// #define  G   CComplexMeasure(pmGiga, )   ///\def   G   macro definition for  giga
// #define  T   CComplexMeasure(pmTera, )   ///\def   T   macro definition for  tera
// #define  P   CComplexMeasure(pmPeta, )   ///\def   P   macro definition for  peta
// #define  E   CComplexMeasure(pmExa,  )   ///\def   E   macro definition for   exa
// #define  Z   CComplexMeasure(pmZetta,)   ///\def   Z   macro definition for zetta
// #define  Y   CComplexMeasure(pmYotta,)   ///\def   Y   macro definition for yotta

#endif // CCOMPLEXMEASUREMACROS_H
