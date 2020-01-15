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

#include"BaseMeasure.h"

/**
 * @brief initializes all relevant vectors describing a unit
 * 
 */
void CBaseMeasure::_Init()
{
    _DeInit();
    
    vstrShort.resize(bmLast+1);
    vstrLong.resize(bmLast+1);
    vnSIIndex.resize(bmLast+1);
    vdOffset.resize(bmLast+1);
    vdFactor.resize(bmLast+1);
    
    vstrShort[bmNumber]=(L"1");
    vstrLong[bmNumber]=(L"one");
    vnSIIndex[bmNumber]=(bmNumber);
    vdOffset[bmNumber]=(0.);
    vdFactor[bmNumber]=(1.);
    
    vstrShort[bmVolt]=(L"V");
    vstrLong[bmVolt]=(L"volt");
    vnSIIndex[bmVolt]=(bmVolt);
    vdOffset[bmVolt]=(0.);
    vdFactor[bmVolt]=(1.);
    
    vstrShort[bmAmpere]=(L"A");
    vstrLong[bmAmpere]=(L"ampere");
    vnSIIndex[bmAmpere]=(bmAmpere);
    vdOffset[bmAmpere]=(0.);
    vdFactor[bmAmpere]=(1.);
    
    vstrShort[bmDegKelvin]=(L"°K");
    vstrLong[bmDegKelvin]=(L"degree kelvin");
    vnSIIndex[bmDegKelvin]=(bmDegKelvin);
    vdOffset[bmDegKelvin]=(0.);
    vdFactor[bmDegKelvin]=(1.);
    
    vstrShort[bmDegCelsius]=(L"°C");
    vstrLong[bmDegCelsius]=(L"degree celsius");
    vnSIIndex[bmDegCelsius]=(bmDegKelvin);
    vdOffset[bmDegCelsius]=(273.15);
    vdFactor[bmDegCelsius]=(1.);
    
    vstrShort[bmDegFahrenheit]=(L"°F");
    vstrLong[bmDegFahrenheit]=(bmDegKelvin);
    vnSIIndex[bmDegFahrenheit]=(bmDegKelvin);
    vdOffset[bmDegFahrenheit]=(32-5./9.*273.15);
    vdFactor[bmDegFahrenheit]=(5./9.);
    
    vstrShort[bmOhm]=(Omega);
    vstrLong[bmOhm]=(L"ohm");
    vnSIIndex[bmOhm]=(bmOhm);
    vdOffset[bmOhm]=(0.);
    vdFactor[bmOhm]=(1.);
    
    vstrShort[bmFarad]=(L"F");
    vstrLong[bmFarad]=(L"farad");
    vnSIIndex[bmFarad]=(bmFarad);
    vdOffset[bmFarad]=(0.);
    vdFactor[bmFarad]=(1.);
    
    vstrShort[bmHertz]=(L"Hz");
    vstrLong[bmHertz]=(L"hertz");
    vnSIIndex[bmHertz]=(bmHertz);
    vdOffset[bmHertz]=(0.);
    vdFactor[bmHertz]=(1.);
    
    vstrShort[bmSecond]=(L"s");
    vstrLong[bmSecond]=(L"second");
    vnSIIndex[bmSecond]=(bmSecond);
    vdOffset[bmSecond]=(0.);
    vdFactor[bmSecond]=(1.);
    
    vstrShort[bmMinute]=(L"min");
    vstrLong[bmMinute]=(L"minute");
    vnSIIndex[bmMinute]=(bmSecond);
    vdOffset[bmMinute]=(0.);
    vdFactor[bmMinute]=(60.);
    
    vstrShort[bmHour]=(L"h");
    vstrLong[bmHour]=(L"hour");
    vnSIIndex[bmHour]=(bmSecond);
    vdOffset[bmHour]=(0.);
    vdFactor[bmHour]=(3600);
    
    vstrShort[bmDay]=(L"d");
    vstrLong[bmDay]=(L"day");
    vnSIIndex[bmDay]=(bmSecond);
    vdOffset[bmDay]=(0.);
    vdFactor[bmDay]=(86400.);
    
    vstrShort[bmMeter]=(L"m");
    vstrLong[bmMeter]=(L"meter");
    vnSIIndex[bmMeter]=(bmMeter);
    vdOffset[bmMeter]=(0.);
    vdFactor[bmMeter]=(1.);
    
    vstrShort[bmInch]=(L"in");
    vstrLong[bmInch]=(L"inch");
    vnSIIndex[bmInch]=(bmMeter);
    vdOffset[bmInch]=(0.);
    vdFactor[bmInch]=(0.0254);
    
    vstrShort[bmFoot]=(L"ft");
    vstrLong[bmFoot]=(L"foot");
    vnSIIndex[bmFoot]=(bmMeter);
    vdOffset[bmFoot]=(0.);
    vdFactor[bmFoot]=(0.3048);
    
    vstrShort[bmYard]=(L"yd");
    vstrLong[bmYard]=(L"yard");
    vnSIIndex[bmYard]=(bmMeter);
    vdOffset[bmYard]=(0.);
    vdFactor[bmYard]=(0.9144);
    
    vstrShort[bmMile]=(L"mi");
    vstrLong[bmMile]=(L"mile");
    vnSIIndex[bmMile]=(bmMeter);
    vdOffset[bmMile]=(0.);
    vdFactor[bmMile]=(1609.344);
    
    vstrShort[bmUnknown]=(UNKNOWN_SHORT);
    vstrLong[bmUnknown]=(UNKNOWN_LONG);
    vnSIIndex[bmUnknown]=(UNKNOWN_INDEX);
    vdOffset[bmUnknown]=(UNKNOWN_VALUE);
    vdFactor[bmUnknown]=(UNKNOWN_VALUE);
    
}

void CBaseMeasure::_DeInit()
{ 
    CVectorHandle::_DeInit();
    vdOffset.clear();
    vnSIIndex.clear();
}

const wstring CBaseMeasure::DebugOut(const eBaseMeasure BaseMeasureEnum)
{
    return L"Offset = " + to_wstring(Offset(BaseMeasureEnum)) + L"\n" +
           L"Factor = " + to_wstring(Factor(BaseMeasureEnum)) + L"\n" +   
           L"Short = " + Short(BaseMeasureEnum) + L"\n" +
           L"Long = " + Long(BaseMeasureEnum)  + L"\n" +
           L"SIIndex = " + to_wstring( SIID(BaseMeasureEnum) );
  
}
