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

#include "Measure/PreMeasure.h"

CPreMeasure::CPreMeasure()
{
    // allocate vnExp10
    vnExp10 = new vector<int>;
    
    vdFactor->resize(pmLast+1);
    vnExp10->resize(pmLast+1);
    vstrShort->resize(pmLast+1);
    vstrLong->resize(pmLast+1);
    
    
    (*vdFactor)[pmFemto]=(1e-15);
    (*vnExp10)[pmFemto]=(-15);   
    (*vstrShort)[pmFemto]=("f");    
    (*vstrLong)[pmFemto]=("femto");
    
    (*vdFactor)[pmPiko]=(1e-12); 
    (*vnExp10)[pmPiko]=(-12);    
    (*vstrShort)[pmPiko]=("p");    
    (*vstrLong)[pmPiko]=("piko");
    
    (*vdFactor)[pmNano]=(1e-9);
    (*vnExp10)[pmNano]=(-9);
    (*vstrShort)[pmNano]=("n");    
    (*vstrLong)[pmNano]=("nano");
    
    (*vdFactor)[pmMicro]=(1e-6);    
    (*vnExp10)[pmMicro]=(-6);    
    (*vstrShort)[pmMicro]=(mu);    
    (*vstrLong)[pmMicro]=("micro");
    
    (*vdFactor)[pmMilli]=(1e-3);    
    (*vnExp10)[pmMilli]=(-3);    
    (*vstrShort)[pmMilli]=("m");    
    (*vstrLong)[pmMilli]=("milli");
    
    (*vdFactor)[pmCenti]=(1e-2);    
    (*vnExp10)[pmCenti]=(-2);    
    (*vstrShort)[pmCenti]=("c");    
    (*vstrLong)[pmCenti]=("centi");
    
    (*vdFactor)[pmDeci]=(1e-1);    
    (*vnExp10)[pmDeci]=(-1);    
    (*vstrShort)[pmDeci]=("d");    
    (*vstrLong)[pmDeci]=("deci");
    
    (*vdFactor)[pmIdent]=(1e+0);    
    (*vnExp10)[pmIdent]=(+0);    
    (*vstrShort)[pmIdent]=("");    
    (*vstrLong)[pmIdent]=("");
    
    (*vdFactor)[pmDeca]=(1e+1);    
    (*vnExp10)[pmDeca]=(+1);    
    (*vstrShort)[pmDeca]=("da");    
    (*vstrLong)[pmDeca]=("deca");
    
    (*vdFactor)[pmHecto]=(1e+2);    
    (*vnExp10)[pmHecto]=(+2);    
    (*vstrShort)[pmHecto]=("h");    
    (*vstrLong)[pmHecto]=("hecto");
    
    (*vdFactor)[pmKilo]=(1e+3);    
    (*vnExp10)[pmKilo]=(+3);    
    (*vstrShort)[pmKilo]=("k");    
    (*vstrLong)[pmKilo]=("kilo");
    
    (*vdFactor)[pmMega]=(1e+6);    
    (*vnExp10)[pmMega]=(+6);    
    (*vstrShort)[pmMega]=("M");    
    (*vstrLong)[pmMega]=("mega");
    
    (*vdFactor)[pmGiga]=(1e+9);    
    (*vnExp10)[pmGiga]=(+9);    
    (*vstrShort)[pmGiga]=("G");    
    (*vstrLong)[pmGiga]=("giga");
    
    (*vdFactor)[pmTera]=(1e+12);    
    (*vnExp10)[pmTera]=(+12);    
    (*vstrShort)[pmTera]=("T");    
    (*vstrLong)[pmTera]=("tera");
    
    (*vdFactor)[pmPeta]=(1e+15);    
    (*vnExp10)[pmPeta]=(+15);    
    (*vstrShort)[pmPeta]=("P");    
    (*vstrLong)[pmPeta]=("Peta");
    
    (*vdFactor)[pmExa]=(1e+18);    
    (*vnExp10)[pmExa]=(+18);    
    (*vstrShort)[pmExa]=("E");    
    (*vstrLong)[pmExa]=("Exa");
    
    (*vdFactor)[pmZetta]=(1e+21);    
    (*vnExp10)[pmZetta]=(+21);    
    (*vstrShort)[pmZetta]=("Z");    
    (*vstrLong)[pmZetta]=("Zetta");
    
    (*vdFactor)[pmYotta]=(1e+24);    
    (*vnExp10)[pmYotta]=(+24);    
    (*vstrShort)[pmYotta]=("Y");    
    (*vstrLong)[pmYotta]=("Yotta");
    
    (*vdFactor)[pmUnknown]=(nan("1"));    
    (*vnExp10)[pmUnknown]=(INVALID_EXPONENT);    
    (*vstrShort)[pmUnknown]=(UNKNOWN_SHORT);    
    (*vstrLong)[pmUnknown]=(UNKNOWN_LONG); 
    
}

CPreMeasure::~CPreMeasure()
{
    vnExp10->clear();
    SecureDeleteObjectPointer(vnExp10);

}

ePreMeasure CPreMeasure::GetIDByFactor(const double dPreMeasureFactor)
{
    // handle extreme cases: 
    //dPreMeasureFactor smaller equal than smallest value of PreMeasure factors
    if(dPreMeasureFactor <= Factor(pmFirst))
        return pmFirst;
    
    //dPreMeasureFactor bigger equal than biggest value of PreMeasure factors
    if(dPreMeasureFactor >= Factor(pmLast-1))
        return (ePreMeasure)(pmLast-1);
    
    // if we come here iterate over all other PreMeasure factors:
    // stop in case the remaining factor is between 0.1 and 10
    ePreMeasure pmOpt = pmUnknown;
    for(unsigned int idx = 0; idx < vdFactor->size(); idx++)
    {   
        // set the limits depending of the consecutive and previous measure:
        // default is a factor 1000 distance:
        // there are only factors of 1000 or 10 (ideally)
        double dLowerLimit = 0.099999999;   //ideally 0.1
        double dUpperLimit = 10.000000001;   //ideally 10
        
        if(idx>0)
            if( (Factor(idx)/Factor(idx-1)) < 100)
                dLowerLimit = 0.9;
            
        if((Factor(idx+1)/Factor(idx)) < 100)
            dUpperLimit = 1.1;
        
        double dRatio = dPreMeasureFactor/Factor(idx); 
        if( (dLowerLimit < dRatio) && (dRatio < dUpperLimit))
        {
             pmOpt = (ePreMeasure)(idx);
             break;
        }
        
    }
    
    return pmOpt;
}

ePreMeasure CPreMeasure::GetIDByExp10(const int nExp10)
{ 
  
    // at this point: find the closest
    ePreMeasure optPM = pmFirst;
    int nAbsDiff = abs(nExp10-Exp10(optPM));
    for(unsigned int idx = 0; idx < vnExp10->size(); idx++)
        if( nAbsDiff > (abs(nExp10-Exp10(idx))) )
        {
            nAbsDiff = abs(nExp10 - Exp10(idx));
            optPM = (ePreMeasure)idx;
        }
        
    return optPM;
    
}

string CPreMeasure::DebugOut(const int nIndex)
{
    return "Factor = " + to_string(Factor(nIndex)) + "\n" +
           "Short = " + Short(nIndex) + "\n"   +
           "Long = " + Long(nIndex);
}

string CPreMeasure::DebugOut(const ePreMeasure PreMeasureEnum)
{
    return DebugOut((int)PreMeasureEnum);
}


