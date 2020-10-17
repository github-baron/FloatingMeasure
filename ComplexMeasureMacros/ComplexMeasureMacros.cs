using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using ComplexMeasureCLI;
using SimpleMeasureCLI;
using static SimpleMeasureCLI.ePreMeasureManaged;
using static SimpleMeasureCLI.eBaseMeasureManaged;

namespace ComplexMeasureWrapperMacros
{
    static public class ComplexMeasureWrapperMacros
    {
        // macros for easy to use ComplexMeasures 
        public static ComplexMeasureWrapper cmIdent = (new ComplexMeasureWrapper(pmIdent, bmNumber));  ///\def  fV macro definition for dimensionless number = "1"


        public static ComplexMeasureWrapper fV = (new ComplexMeasureWrapper(pmFemto, bmVolt));   ///\def  fV macro definition for femtovolt
        public static ComplexMeasureWrapper pV = (new ComplexMeasureWrapper(pmPiko, bmVolt));   ///\def  pV macro definition for pikovolt
        public static ComplexMeasureWrapper nV = (new ComplexMeasureWrapper(pmNano, bmVolt));   ///\def  nV macro definition for nanovolt
        public static ComplexMeasureWrapper uV = (new ComplexMeasureWrapper(pmMicro, bmVolt));   ///\def  uV macro definition for microvolt
        public static ComplexMeasureWrapper mV = (new ComplexMeasureWrapper(pmMilli, bmVolt));   ///\def  mV macro definition for millivolt
        public static ComplexMeasureWrapper cV = (new ComplexMeasureWrapper(pmCenti, bmVolt));   ///\def  cV macro definition for centivolt
        public static ComplexMeasureWrapper dV = (new ComplexMeasureWrapper(pmDeci, bmVolt));   ///\def  dV macro definition for decivolt
        public static ComplexMeasureWrapper V = (new ComplexMeasureWrapper(pmIdent, bmVolt));   ///\def   V macro definition for volt
        public static ComplexMeasureWrapper daV = (new ComplexMeasureWrapper(pmDeca, bmVolt));   ///\def daV macro definition for decavolt
        public static ComplexMeasureWrapper HV = (new ComplexMeasureWrapper(pmHecto, bmVolt));   ///\def  HV macro definition for hectovolt
        public static ComplexMeasureWrapper kV = (new ComplexMeasureWrapper(pmKilo, bmVolt));   ///\def  kV macro definition for kilovolt
        public static ComplexMeasureWrapper MV = (new ComplexMeasureWrapper(pmMega, bmVolt));   ///\def  MV macro definition for megavolt
        public static ComplexMeasureWrapper GV = (new ComplexMeasureWrapper(pmGiga, bmVolt));   ///\def  GV macro definition for gigavolt
        public static ComplexMeasureWrapper TV = (new ComplexMeasureWrapper(pmTera, bmVolt));   ///\def  TV macro definition for teravolt
        public static ComplexMeasureWrapper PV = (new ComplexMeasureWrapper(pmPeta, bmVolt));   ///\def  PV macro definition for petavolt
        public static ComplexMeasureWrapper EV = (new ComplexMeasureWrapper(pmExa, bmVolt));   ///\def  EV macro definition for exavolt
        public static ComplexMeasureWrapper ZV = (new ComplexMeasureWrapper(pmZetta, bmVolt));   ///\def  ZV macro definition for zettavolt
        public static ComplexMeasureWrapper YV = (new ComplexMeasureWrapper(pmYotta, bmVolt));   ///\def  YV macro definition for yottavolt


        public static ComplexMeasureWrapper fA = (new ComplexMeasureWrapper(pmFemto, bmAmpere)); ///\def  fA macro definition for femtoampere  
        public static ComplexMeasureWrapper pA = (new ComplexMeasureWrapper(pmPiko, bmAmpere)); ///\def  pA macro definition for pikoampere 
        public static ComplexMeasureWrapper nA = (new ComplexMeasureWrapper(pmNano, bmAmpere)); ///\def  nA macro definition for nanoampere 
        public static ComplexMeasureWrapper uA = (new ComplexMeasureWrapper(pmMicro, bmAmpere)); ///\def  uA macro definition for microampere 
        public static ComplexMeasureWrapper mA = (new ComplexMeasureWrapper(pmMilli, bmAmpere)); ///\def  mA macro definition for milliampere 
        public static ComplexMeasureWrapper cA = (new ComplexMeasureWrapper(pmCenti, bmAmpere)); ///\def  cA macro definition for centiampere 
        public static ComplexMeasureWrapper dA = (new ComplexMeasureWrapper(pmDeci, bmAmpere)); ///\def  dA macro definition for deciampere 
        public static ComplexMeasureWrapper A = (new ComplexMeasureWrapper(pmIdent, bmAmpere)); ///\def   A macro definition for ampere 
        public static ComplexMeasureWrapper daA = (new ComplexMeasureWrapper(pmDeca, bmAmpere)); ///\def daA macro definition for decaampere 
        public static ComplexMeasureWrapper HA = (new ComplexMeasureWrapper(pmHecto, bmAmpere)); ///\def  HA macro definition for hectoampere  
        public static ComplexMeasureWrapper kA = (new ComplexMeasureWrapper(pmKilo, bmAmpere)); ///\def  kA macro definition for kiloampere 
        public static ComplexMeasureWrapper MA = (new ComplexMeasureWrapper(pmMega, bmAmpere)); ///\def  MA macro definition for megaampere 
        public static ComplexMeasureWrapper GA = (new ComplexMeasureWrapper(pmGiga, bmAmpere)); ///\def  GA macro definition for gigaampere 
        public static ComplexMeasureWrapper TA = (new ComplexMeasureWrapper(pmTera, bmAmpere)); ///\def  TA macro definition for teraampere 
        public static ComplexMeasureWrapper PA = (new ComplexMeasureWrapper(pmPeta, bmAmpere)); ///\def  PA macro definition for petaampere 
        public static ComplexMeasureWrapper EA = (new ComplexMeasureWrapper(pmExa, bmAmpere)); ///\def  EA macro definition for exaampere 
        public static ComplexMeasureWrapper ZA = (new ComplexMeasureWrapper(pmZetta, bmAmpere)); ///\def  ZA macro definition for zettaampere 
        public static ComplexMeasureWrapper YA = (new ComplexMeasureWrapper(pmYotta, bmAmpere)); ///\def  YA macro definition for yottaampere 


        public static ComplexMeasureWrapper fs = (new ComplexMeasureWrapper(pmFemto, bmSecond));  ///\def  fs macro definition for femtosecond
        public static ComplexMeasureWrapper ps = (new ComplexMeasureWrapper(pmPiko, bmSecond));  ///\def  ps macro definition for pikosecond
        public static ComplexMeasureWrapper ns = (new ComplexMeasureWrapper(pmNano, bmSecond));  ///\def  ns macro definition for nanosecond
        public static ComplexMeasureWrapper us = (new ComplexMeasureWrapper(pmMicro, bmSecond));  ///\def  us macro definition for microsecond
        public static ComplexMeasureWrapper ms = (new ComplexMeasureWrapper(pmMilli, bmSecond));  ///\def  ms macro definition for millisecond
        public static ComplexMeasureWrapper cs = (new ComplexMeasureWrapper(pmCenti, bmSecond));  ///\def  cs macro definition for centisecond
        public static ComplexMeasureWrapper ds = (new ComplexMeasureWrapper(pmDeci, bmSecond));  ///\def  ds macro definition for decisecond
        public static ComplexMeasureWrapper s = (new ComplexMeasureWrapper(pmIdent, bmSecond));  ///\def   s macro definition for second
        public static ComplexMeasureWrapper das = (new ComplexMeasureWrapper(pmDeca, bmSecond));  ///\def das macro definition for decasecond
        public static ComplexMeasureWrapper Hs = (new ComplexMeasureWrapper(pmHecto, bmSecond));  ///\def  Hs macro definition for ectosecond 
        public static ComplexMeasureWrapper ks = (new ComplexMeasureWrapper(pmKilo, bmSecond));  ///\def  ks macro definition for kilosecond
        public static ComplexMeasureWrapper Ms = (new ComplexMeasureWrapper(pmMega, bmSecond));  ///\def  Ms macro definition for megasecond
        public static ComplexMeasureWrapper Gs = (new ComplexMeasureWrapper(pmGiga, bmSecond));  ///\def  Gs macro definition for gigasecond
        public static ComplexMeasureWrapper Ts = (new ComplexMeasureWrapper(pmTera, bmSecond));  ///\def  Ts macro definition for terasecond
        public static ComplexMeasureWrapper Ps = (new ComplexMeasureWrapper(pmPeta, bmSecond));  ///\def  Ps macro definition for petasecond
        public static ComplexMeasureWrapper Es = (new ComplexMeasureWrapper(pmExa, bmSecond));  ///\def  Es macro definition for exasecond
        public static ComplexMeasureWrapper Zs = (new ComplexMeasureWrapper(pmZetta, bmSecond));  ///\def  Zs macro definition for zettasecond
        public static ComplexMeasureWrapper Ys = (new ComplexMeasureWrapper(pmYotta, bmSecond));  ///\def  Ys macro definition for yottasecond
        public static ComplexMeasureWrapper min = (new ComplexMeasureWrapper(pmIdent, bmMinute));  ///\def   m macro definition for minute
        public static ComplexMeasureWrapper h = (new ComplexMeasureWrapper(pmIdent, bmHour));    ///\def   h macro definition for hour 
        public static ComplexMeasureWrapper d = (new ComplexMeasureWrapper(pmIdent, bmDay));     ///\def   d macro definition for day 

        public static ComplexMeasureWrapper fC = (new ComplexMeasureWrapper(pmFemto, bmDegCelsius));       ///\def   fC   macro definition for femto-degree celsiusus
        public static ComplexMeasureWrapper pC = (new ComplexMeasureWrapper(pmPiko, bmDegCelsius));       ///\def   pC   macro definition for piko-degree celsiusus
        public static ComplexMeasureWrapper nC = (new ComplexMeasureWrapper(pmNano, bmDegCelsius));       ///\def   nC   macro definition for nano-degree celsiusus
        public static ComplexMeasureWrapper uC = (new ComplexMeasureWrapper(pmMicro, bmDegCelsius));       ///\def   uC   macro definition for micro-degree celsiusus
        public static ComplexMeasureWrapper mC = (new ComplexMeasureWrapper(pmMilli, bmDegCelsius));       ///\def   mC   macro definition for milli-degree celsiusus
        public static ComplexMeasureWrapper cC = (new ComplexMeasureWrapper(pmCenti, bmDegCelsius));       ///\def   cC   macro definition for centi-degree celsiusus
        public static ComplexMeasureWrapper dC = (new ComplexMeasureWrapper(pmDeci, bmDegCelsius));       ///\def   dC   macro definition for deci-degree celsiusus
        public static ComplexMeasureWrapper C = (new ComplexMeasureWrapper(pmIdent, bmDegCelsius));       ///\def    C   macro definition for ident-degree celsiusus
        public static ComplexMeasureWrapper daC = (new ComplexMeasureWrapper(pmDeca, bmDegCelsius));       ///\def  daC   macro definition for deca-degree celsiusus
        public static ComplexMeasureWrapper HC = (new ComplexMeasureWrapper(pmHecto, bmDegCelsius));       ///\def   HC   macro definition for hecto-degree celsiusus
        public static ComplexMeasureWrapper kC = (new ComplexMeasureWrapper(pmKilo, bmDegCelsius));       ///\def   kC   macro definition for kilo-degree celsiusus
        public static ComplexMeasureWrapper MC = (new ComplexMeasureWrapper(pmMega, bmDegCelsius));       ///\def   MC   macro definition for mega-degree celsiusus
        public static ComplexMeasureWrapper GC = (new ComplexMeasureWrapper(pmGiga, bmDegCelsius));       ///\def   GC   macro definition for giga-degree celsiusus
        public static ComplexMeasureWrapper TC = (new ComplexMeasureWrapper(pmTera, bmDegCelsius));       ///\def   TC   macro definition for tera-degree celsiusus
        public static ComplexMeasureWrapper PC = (new ComplexMeasureWrapper(pmPeta, bmDegCelsius));       ///\def   PC   macro definition for peta-degree celsiusus
        public static ComplexMeasureWrapper EC = (new ComplexMeasureWrapper(pmExa, bmDegCelsius));       ///\def   EC   macro definition for exa-degree celsiusus
        public static ComplexMeasureWrapper ZC = (new ComplexMeasureWrapper(pmZetta, bmDegCelsius));       ///\def   ZC   macro definition for zetta-degree celsiusus
        public static ComplexMeasureWrapper YC = (new ComplexMeasureWrapper(pmYotta, bmDegCelsius));       ///\def   YC   macro definition for yotta-degree celsiusus

        public static ComplexMeasureWrapper fF = (new ComplexMeasureWrapper(pmFemto, bmDegFahrenheit));    ///\def   fF   macro definition for femto-degree fahrenheitnheit
        public static ComplexMeasureWrapper pF = (new ComplexMeasureWrapper(pmPiko, bmDegFahrenheit));    ///\def   pF   macro definition for piko-degree fahrenheitnheit
        public static ComplexMeasureWrapper nF = (new ComplexMeasureWrapper(pmNano, bmDegFahrenheit));    ///\def   nF   macro definition for nano-degree fahrenheitnheit
        public static ComplexMeasureWrapper uF = (new ComplexMeasureWrapper(pmMicro, bmDegFahrenheit));    ///\def   uF   macro definition for micro-degree fahrenheitnheit
        public static ComplexMeasureWrapper mF = (new ComplexMeasureWrapper(pmMilli, bmDegFahrenheit));    ///\def   mF   macro definition for milli-degree fahrenheitnheit
        public static ComplexMeasureWrapper cF = (new ComplexMeasureWrapper(pmCenti, bmDegFahrenheit));    ///\def   cF   macro definition for centi-degree fahrenheitnheit
        public static ComplexMeasureWrapper dF = (new ComplexMeasureWrapper(pmDeci, bmDegFahrenheit));    ///\def   dF   macro definition for deci-degree fahrenheitnheit
        public static ComplexMeasureWrapper F = (new ComplexMeasureWrapper(pmIdent, bmDegFahrenheit));    ///\def    F   macro definition for ident-degree fahrenheitnheit
        public static ComplexMeasureWrapper daF = (new ComplexMeasureWrapper(pmDeca, bmDegFahrenheit));    ///\def  daF   macro definition for deca-degree fahrenheitnheit
        public static ComplexMeasureWrapper HF = (new ComplexMeasureWrapper(pmHecto, bmDegFahrenheit));    ///\def   HF   macro definition for hecto-degree fahrenheitnheit
        public static ComplexMeasureWrapper kF = (new ComplexMeasureWrapper(pmKilo, bmDegFahrenheit));    ///\def   kF   macro definition for kilo-degree fahrenheitnheit
        public static ComplexMeasureWrapper MF = (new ComplexMeasureWrapper(pmMega, bmDegFahrenheit));    ///\def   MF   macro definition for mega-degree fahrenheitnheit
        public static ComplexMeasureWrapper GF = (new ComplexMeasureWrapper(pmGiga, bmDegFahrenheit));    ///\def   GF   macro definition for giga-degree fahrenheitnheit
        public static ComplexMeasureWrapper TF = (new ComplexMeasureWrapper(pmTera, bmDegFahrenheit));    ///\def   TF   macro definition for tera-degree fahrenheitnheit
        public static ComplexMeasureWrapper PF = (new ComplexMeasureWrapper(pmPeta, bmDegFahrenheit));    ///\def   PF   macro definition for peta-degree fahrenheitnheit
        public static ComplexMeasureWrapper EF = (new ComplexMeasureWrapper(pmExa, bmDegFahrenheit));    ///\def   EF   macro definition for exa-degree fahrenheitnheit
        public static ComplexMeasureWrapper ZF = (new ComplexMeasureWrapper(pmZetta, bmDegFahrenheit));    ///\def   ZF   macro definition for zetta-degree fahrenheitnheit
        public static ComplexMeasureWrapper YF = (new ComplexMeasureWrapper(pmYotta, bmDegFahrenheit));    ///\def   YF   macro definition for yotta-degree fahrenheitnheit

        public static ComplexMeasureWrapper fK = (new ComplexMeasureWrapper(pmFemto, bmDegKelvin));        ///\def   fK   macro definition for femto-degree kelvin
        public static ComplexMeasureWrapper pK = (new ComplexMeasureWrapper(pmPiko, bmDegKelvin));        ///\def   pK   macro definition for piko-degree kelvin
        public static ComplexMeasureWrapper nK = (new ComplexMeasureWrapper(pmNano, bmDegKelvin));        ///\def   nK   macro definition for nano-degree kelvin
        public static ComplexMeasureWrapper uK = (new ComplexMeasureWrapper(pmMicro, bmDegKelvin));        ///\def   uK   macro definition for micro-degree kelvin
        public static ComplexMeasureWrapper mK = (new ComplexMeasureWrapper(pmMilli, bmDegKelvin));        ///\def   mK   macro definition for milli-degree kelvin
        public static ComplexMeasureWrapper cK = (new ComplexMeasureWrapper(pmCenti, bmDegKelvin));        ///\def   cK   macro definition for centi-degree kelvin
        public static ComplexMeasureWrapper dK = (new ComplexMeasureWrapper(pmDeci, bmDegKelvin));        ///\def   dK   macro definition for deci-degree kelvin
        public static ComplexMeasureWrapper K = (new ComplexMeasureWrapper(pmIdent, bmDegKelvin));        ///\def    K   macro definition for ident-degree kelvin
        public static ComplexMeasureWrapper daK = (new ComplexMeasureWrapper(pmDeca, bmDegKelvin));        ///\def  daK   macro definition for deca-degree kelvin
        public static ComplexMeasureWrapper HK = (new ComplexMeasureWrapper(pmHecto, bmDegKelvin));        ///\def   HK   macro definition for hecto-degree kelvin
        public static ComplexMeasureWrapper kK = (new ComplexMeasureWrapper(pmKilo, bmDegKelvin));        ///\def   kK   macro definition for kilo-degree kelvin
        public static ComplexMeasureWrapper MK = (new ComplexMeasureWrapper(pmMega, bmDegKelvin));        ///\def   MK   macro definition for mega-degree kelvin
        public static ComplexMeasureWrapper GK = (new ComplexMeasureWrapper(pmGiga, bmDegKelvin));        ///\def   GK   macro definition for giga-degree kelvin
        public static ComplexMeasureWrapper TK = (new ComplexMeasureWrapper(pmTera, bmDegKelvin));        ///\def   TK   macro definition for tera-degree kelvin
        public static ComplexMeasureWrapper PK = (new ComplexMeasureWrapper(pmPeta, bmDegKelvin));        ///\def   PK   macro definition for peta-degree kelvin
        public static ComplexMeasureWrapper EK = (new ComplexMeasureWrapper(pmExa, bmDegKelvin));        ///\def   EK   macro definition for exa-degree kelvin
        public static ComplexMeasureWrapper ZK = (new ComplexMeasureWrapper(pmZetta, bmDegKelvin));        ///\def   ZK   macro definition for zetta-degree kelvin
        public static ComplexMeasureWrapper YK = (new ComplexMeasureWrapper(pmYotta, bmDegKelvin));        ///\def   YK   macro definition for yotta-degree kelvin

        public static ComplexMeasureWrapper fOhm = (new ComplexMeasureWrapper(pmFemto, bmOhm));            ///\def   fOhm   macro definition for femtoohm  
        public static ComplexMeasureWrapper pOhm = (new ComplexMeasureWrapper(pmPiko, bmOhm));            ///\def   pOhm   macro definition for pikoohm  
        public static ComplexMeasureWrapper nOhm = (new ComplexMeasureWrapper(pmNano, bmOhm));            ///\def   nOhm   macro definition for nanoohm  
        public static ComplexMeasureWrapper uOhm = (new ComplexMeasureWrapper(pmMicro, bmOhm));            ///\def   uOhm   macro definition for microohm  
        public static ComplexMeasureWrapper mOhm = (new ComplexMeasureWrapper(pmMilli, bmOhm));            ///\def   mOhm   macro definition for milliohm  
        public static ComplexMeasureWrapper cOhm = (new ComplexMeasureWrapper(pmCenti, bmOhm));            ///\def   cOhm   macro definition for centiohm  
        public static ComplexMeasureWrapper dOhm = (new ComplexMeasureWrapper(pmDeci, bmOhm));            ///\def   dOhm   macro definition for deciohm  
        public static ComplexMeasureWrapper Ohm = (new ComplexMeasureWrapper(pmIdent, bmOhm));            ///\def    Ohm   macro definition for identohm  
        public static ComplexMeasureWrapper daOhm = (new ComplexMeasureWrapper(pmDeca, bmOhm));            ///\def  daOhm   macro definition for decaohm  
        public static ComplexMeasureWrapper HOhm = (new ComplexMeasureWrapper(pmHecto, bmOhm));            ///\def   HOhm   macro definition for hectoohm  
        public static ComplexMeasureWrapper kOhm = (new ComplexMeasureWrapper(pmKilo, bmOhm));            ///\def   kOhm   macro definition for kiloohm  
        public static ComplexMeasureWrapper MOhm = (new ComplexMeasureWrapper(pmMega, bmOhm));            ///\def   MOhm   macro definition for megaohm  
        public static ComplexMeasureWrapper GOhm = (new ComplexMeasureWrapper(pmGiga, bmOhm));            ///\def   GOhm   macro definition for gigaohm  
        public static ComplexMeasureWrapper TOhm = (new ComplexMeasureWrapper(pmTera, bmOhm));            ///\def   TOhm   macro definition for teraohm  
        public static ComplexMeasureWrapper POhm = (new ComplexMeasureWrapper(pmPeta, bmOhm));            ///\def   POhm   macro definition for petaohm  
        public static ComplexMeasureWrapper EOhm = (new ComplexMeasureWrapper(pmExa, bmOhm));            ///\def   EOhm   macro definition for exaohm  
        public static ComplexMeasureWrapper ZOhm = (new ComplexMeasureWrapper(pmZetta, bmOhm));            ///\def   ZOhm   macro definition for zettaohm  
        public static ComplexMeasureWrapper YOhm = (new ComplexMeasureWrapper(pmYotta, bmOhm));            ///\def   YOhm   macro definition for yottaohm 

        public static ComplexMeasureWrapper fHz = (new ComplexMeasureWrapper(pmFemto, bmHertz));           ///\def   fHz   macro definition for femtohertz 
        public static ComplexMeasureWrapper pHz = (new ComplexMeasureWrapper(pmPiko, bmHertz));           ///\def   pHz   macro definition for pikohertz 
        public static ComplexMeasureWrapper nHz = (new ComplexMeasureWrapper(pmNano, bmHertz));           ///\def   nHz   macro definition for nanohertz 
        public static ComplexMeasureWrapper uHz = (new ComplexMeasureWrapper(pmMicro, bmHertz));           ///\def   uHz   macro definition for microhertz 
        public static ComplexMeasureWrapper mHz = (new ComplexMeasureWrapper(pmMilli, bmHertz));           ///\def   mHz   macro definition for millihertz 
        public static ComplexMeasureWrapper cHz = (new ComplexMeasureWrapper(pmCenti, bmHertz));           ///\def   cHz   macro definition for centihertz 
        public static ComplexMeasureWrapper dHz = (new ComplexMeasureWrapper(pmDeci, bmHertz));           ///\def   dHz   macro definition for decihertz 
        public static ComplexMeasureWrapper Hz = (new ComplexMeasureWrapper(pmIdent, bmHertz));           ///\def    Hz   macro definition for identhertz 
        public static ComplexMeasureWrapper daHz = (new ComplexMeasureWrapper(pmDeca, bmHertz));           ///\def  daHz   macro definition for decahertz 
        public static ComplexMeasureWrapper HHz = (new ComplexMeasureWrapper(pmHecto, bmHertz));           ///\def   HHz   macro definition for hectohertz 
        public static ComplexMeasureWrapper kHz = (new ComplexMeasureWrapper(pmKilo, bmHertz));           ///\def   kHz   macro definition for kilohertz 
        public static ComplexMeasureWrapper MHz = (new ComplexMeasureWrapper(pmMega, bmHertz));           ///\def   MHz   macro definition for megahertz 
        public static ComplexMeasureWrapper GHz = (new ComplexMeasureWrapper(pmGiga, bmHertz));           ///\def   GHz   macro definition for gigahertz 
        public static ComplexMeasureWrapper THz = (new ComplexMeasureWrapper(pmTera, bmHertz));           ///\def   THz   macro definition for terahertz 
        public static ComplexMeasureWrapper PHz = (new ComplexMeasureWrapper(pmPeta, bmHertz));           ///\def   PHz   macro definition for petahertz 
        public static ComplexMeasureWrapper EHz = (new ComplexMeasureWrapper(pmExa, bmHertz));           ///\def   EHz   macro definition for exahertz 
        public static ComplexMeasureWrapper ZHz = (new ComplexMeasureWrapper(pmZetta, bmHertz));           ///\def   ZHz   macro definition for zettahertz 
        public static ComplexMeasureWrapper YHz = (new ComplexMeasureWrapper(pmYotta, bmHertz));           ///\def   YHz   macro definition for yottahertz 

        public static ComplexMeasureWrapper fm = (new ComplexMeasureWrapper(pmFemto, bmMeter));   ///\def   fm   macro definition for femtometer
        public static ComplexMeasureWrapper pm = (new ComplexMeasureWrapper(pmPiko, bmMeter));   ///\def   pm   macro definition for  pikometer
        public static ComplexMeasureWrapper nm = (new ComplexMeasureWrapper(pmNano, bmMeter));   ///\def   nm   macro definition for  nanometer
        public static ComplexMeasureWrapper um = (new ComplexMeasureWrapper(pmMicro, bmMeter));   ///\def   um   macro definition for micrometer
        public static ComplexMeasureWrapper mm = (new ComplexMeasureWrapper(pmMilli, bmMeter));   ///\def   mm   macro definition for millimeter
        public static ComplexMeasureWrapper cm = (new ComplexMeasureWrapper(pmCenti, bmMeter));   ///\def   cm   macro definition for centimeter
        public static ComplexMeasureWrapper dm = (new ComplexMeasureWrapper(pmDeci, bmMeter));   ///\def   dm   macro definition for  decimeter
        public static ComplexMeasureWrapper m = (new ComplexMeasureWrapper(pmIdent, bmMeter));   ///\def    m   macro definition for      meter
        public static ComplexMeasureWrapper dam = (new ComplexMeasureWrapper(pmDeca, bmMeter));   ///\def  dam   macro definition for  decameter
        public static ComplexMeasureWrapper Hm = (new ComplexMeasureWrapper(pmHecto, bmMeter));   ///\def   Hm   macro definition for hectometer 
        public static ComplexMeasureWrapper km = (new ComplexMeasureWrapper(pmKilo, bmMeter));   ///\def   km   macro definition for  kilometer
        public static ComplexMeasureWrapper Mm = (new ComplexMeasureWrapper(pmMega, bmMeter));   ///\def   Mm   macro definition for  megameter
        public static ComplexMeasureWrapper Gm = (new ComplexMeasureWrapper(pmGiga, bmMeter));   ///\def   Gm   macro definition for  gigameter
        public static ComplexMeasureWrapper Tm = (new ComplexMeasureWrapper(pmTera, bmMeter));   ///\def   Tm   macro definition for  terameter
        public static ComplexMeasureWrapper Pm = (new ComplexMeasureWrapper(pmPeta, bmMeter));   ///\def   Pm   macro definition for  petameter
        public static ComplexMeasureWrapper Em = (new ComplexMeasureWrapper(pmExa, bmMeter));   ///\def   Em   macro definition for   exameter
        public static ComplexMeasureWrapper Zm = (new ComplexMeasureWrapper(pmZetta, bmMeter));   ///\def   Zm   macro definition for zettameter
        public static ComplexMeasureWrapper Ym = (new ComplexMeasureWrapper(pmYotta, bmMeter));   ///\def   Ym   macro definition for yottameter

        // public static ComplexMeasureWrapper  f   = (new ComplexMeasureWrapper(pmFemto,));   ///\def   f   macro definition for femto
        // public static ComplexMeasureWrapper  p   = (new ComplexMeasureWrapper(pmPiko, ));   ///\def   p   macro definition for  piko
        // public static ComplexMeasureWrapper  n   = (new ComplexMeasureWrapper(pmNano, ));   ///\def   n   macro definition for  nano
        // public static ComplexMeasureWrapper  u   = (new ComplexMeasureWrapper(pmMicro,));   ///\def   u   macro definition for micro
        // public static ComplexMeasureWrapper  m   = (new ComplexMeasureWrapper(pmMilli,));   ///\def   m   macro definition for milli
        // public static ComplexMeasureWrapper  c   = (new ComplexMeasureWrapper(pmCenti,));   ///\def   c   macro definition for centi
        // public static ComplexMeasureWrapper  d   = (new ComplexMeasureWrapper(pmDeci, ));   ///\def   d   macro definition for  deci
        // public static ComplexMeasureWrapper      = (new ComplexMeasureWrapper(pmIdent,));   ///\def       macro definition for      
        // public static ComplexMeasureWrapper da   = (new ComplexMeasureWrapper(pmDeca, ));   ///\def  da   macro definition for  deca
        // public static ComplexMeasureWrapper  H   = (new ComplexMeasureWrapper(pmHecto,));   ///\def   H   macro definition for hecto 
        // public static ComplexMeasureWrapper  k   = (new ComplexMeasureWrapper(pmKilo, ));   ///\def   k   macro definition for  kilo
        // public static ComplexMeasureWrapper  M   = (new ComplexMeasureWrapper(pmMega, ));   ///\def   M   macro definition for  mega
        // public static ComplexMeasureWrapper  G   = (new ComplexMeasureWrapper(pmGiga, ));   ///\def   G   macro definition for  giga
        // public static ComplexMeasureWrapper  T   = (new ComplexMeasureWrapper(pmTera, ));   ///\def   T   macro definition for  tera
        // public static ComplexMeasureWrapper  P   = (new ComplexMeasureWrapper(pmPeta, ));   ///\def   P   macro definition for  peta
        // public static ComplexMeasureWrapper  E   = (new ComplexMeasureWrapper(pmExa,  ));   ///\def   E   macro definition for   exa
        // public static ComplexMeasureWrapper  Z   = (new ComplexMeasureWrapper(pmZetta,));   ///\def   Z   macro definition for zetta
        // public static ComplexMeasureWrapper  Y   = (new ComplexMeasureWrapper(pmYotta,));   ///\def   Y   macro definition for yotta
    };
}
