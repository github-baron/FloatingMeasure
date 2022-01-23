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
#include "../FloatingMeasure/Measure/ComplexMeasure.h"
#include "../FloatingMeasure/Measure/ComplexMeasureMacros.h"
#include <cppunit/TestAssert.h>

class CComplexMeasure_Test : public CppUnit::TestFixture  {

private:
    // helping variables
    ostringstream ossDoublSI;
    CComplexMeasure ComplMeas1, ComplMeas2, ComplMeas3, ComplMeas4;
    CComplexMeasure *pCM1, *pCM2;
    
public:
    void setUp()
    {
        pCM1 = nullptr;
        pCM2 = nullptr;
    }

    void tearDown() 
    {
        SecureDeleteObjectPointer(pCM1);
        SecureDeleteObjectPointer(pCM2);
    }

    void OperatorEqualDetail()
    {
        ComplMeas1 = fC;
        CComplexMeasure CheckThis(ComplMeas1);
        CComplexMeasure CheckOther(fC);
 /*       CheckThis.Normalize();
        CheckOther.Normalize();
 */       CPPUNIT_ASSERT_MESSAGE( CheckThis.DebugOut() + "\n" + CheckOther.DebugOut() , CheckThis == CheckOther );
        
    // first handle the simple case: pMeasureRight == nullptr
    // compare the simple measures only: pMeasureLeft == other.pMeasureLeft
//     if( CheckThis.pMeasureRight == nullptr && CheckOther.pMeasureRight == nullptr)
//     {
//         return CheckThis.pMeasureLeft == CheckOther.pMeasureLeft;
//     }

        
    }
    
    void OperatorEqual()
    {
        ComplMeas1 = ns;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.Short() == "ns" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);        
    }
    void Construction()
    {
        // default constructor
        pCM1 = new CComplexMeasure();
        CPPUNIT_ASSERT_MESSAGE( pCM1->DebugOut() , pCM1->Short() == "");
        
        // constructor by ID
        pCM2 = new CComplexMeasure(pmTera,bmHertz);
        CPPUNIT_ASSERT_MESSAGE( pCM2->DebugOut() , pCM2->Short() == "THz" );
        
        // constructor by &other
        SecureDeleteObjectPointer(pCM1);
        ComplMeas1 = km;
        pCM1 = new CComplexMeasure(ComplMeas1);
        CPPUNIT_ASSERT_MESSAGE( pCM1->DebugOut() , pCM1->Short() == "km" );
        
        // constructor by *other
        SecureDeleteObjectPointer(pCM1);
        pCM1 = new CComplexMeasure(pCM2);
        CPPUNIT_ASSERT_MESSAGE( pCM1->DebugOut() , pCM1->Short() == "THz" );
        
    }
    void OperatorAssignAndEqualVoltage()
    {
        // debug 
        CPPUNIT_ASSERT_MESSAGE((fV).DebugOut(),fV == fV);
        
        ComplMeas1=  fV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "fV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fV );
        ComplMeas1=  pV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "pV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pV );
        ComplMeas1=  nV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "nV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nV );
        ComplMeas1=  uV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==mu+"V" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uV );
        ComplMeas1=  mV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "mV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mV );
        ComplMeas1=  cV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "cV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cV );
        ComplMeas1=  dV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "dV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dV );
        ComplMeas1=   V ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==   "V" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  V );
        ComplMeas1= daV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()== "daV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daV );
        ComplMeas1=  HV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "HV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HV );
        ComplMeas1=  kV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "kV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kV );
        ComplMeas1=  MV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "MV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MV );
        ComplMeas1=  GV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "GV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GV );
        ComplMeas1=  TV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "TV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TV );
        ComplMeas1=  PV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "PV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PV );
        ComplMeas1=  EV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "EV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EV );
        ComplMeas1=  ZV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "ZV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZV );
        ComplMeas1=  YV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "YV" );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YV );
    }
    
    void OperatorAssignAndEqualCurrent()
    {
        ComplMeas1=  fA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "fA" );
        ComplMeas1=  pA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "pA" );
        ComplMeas1=  nA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "nA" );
        ComplMeas1=  uA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==mu+"A" );
        ComplMeas1=  mA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "mA" );
        ComplMeas1=  cA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "cA" );
        ComplMeas1=  dA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "dA" );
        ComplMeas1=   A ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  A );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==   "A" );
        ComplMeas1= daA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()== "daA" );
        ComplMeas1=  HA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "HA" );
        ComplMeas1=  kA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "kA" );
        ComplMeas1=  MA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "MA" );
        ComplMeas1=  GA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "GA" );
        ComplMeas1=  TA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "TA" );
        ComplMeas1=  PA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "PA" );
        ComplMeas1=  EA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "EA" );
        ComplMeas1=  ZA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "ZA" );
        ComplMeas1=  YA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "YA" );
    }

    void OperatorAssignAndEqualSeconds()
    {
        ComplMeas1=  fs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "fs" );
        ComplMeas1=  ps ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ps );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "ps" );
        ComplMeas1=  ns ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ns );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "ns" );
        ComplMeas1=  us ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== us );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==mu+"s" );
        ComplMeas1=  ms ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ms );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "ms" );
        ComplMeas1=  cs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "cs" );
        ComplMeas1=  ds ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ds );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "ds" );
        ComplMeas1=   s ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  s );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==   "s" );
        ComplMeas1= das ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==das );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()== "das" );
        ComplMeas1=  Hs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Hs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Hs" );
        ComplMeas1=  ks ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ks );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "ks" );
        ComplMeas1=  Ms ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Ms );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Ms" );
        ComplMeas1=  Gs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Gs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Gs" );
        ComplMeas1=  Ts ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Ts );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Ts" );
        ComplMeas1=  Ps ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Ps );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Ps" );
        ComplMeas1=  Es ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Es );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Es" );
        ComplMeas1=  Zs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Zs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Zs" );
        ComplMeas1=  Ys ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Ys );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Ys" );
    }

    void OperatorAssignAndEqualDegCelcius()
    {
        ComplMeas1=  fC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "f°C" );
        ComplMeas1=  pC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "p°C" );
        ComplMeas1=  nC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "n°C" );
        ComplMeas1=  uC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==mu+"°C" );
        ComplMeas1=  mC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "m°C" );
        ComplMeas1=  cC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "c°C" );
        ComplMeas1=  dC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "d°C" );
        ComplMeas1=   C ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  C );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==   "°C" );
        ComplMeas1= daC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()== "da°C" );
        ComplMeas1=  HC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "H°C" );
        ComplMeas1=  kC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "k°C" );
        ComplMeas1=  MC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "M°C" );
        ComplMeas1=  GC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "G°C" );
        ComplMeas1=  TC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "T°C" );
        ComplMeas1=  PC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "P°C" );
        ComplMeas1=  EC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "E°C" );
        ComplMeas1=  ZC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Z°C" );
        ComplMeas1=  YC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Y°C" );
    }

    void OperatorAssignAndEqualDegFahrenheit()
    {
        ComplMeas1=  fF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "f°F" );
        ComplMeas1=  pF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "p°F" );
        ComplMeas1=  nF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "n°F" );
        ComplMeas1=  uF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==mu+"°F" );
        ComplMeas1=  mF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "m°F" );
        ComplMeas1=  cF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "c°F" );
        ComplMeas1=  dF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "d°F" );
        ComplMeas1=   F ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  F );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==   "°F" );
        ComplMeas1= daF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()== "da°F" );
        ComplMeas1=  HF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "H°F" );
        ComplMeas1=  kF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "k°F" );
        ComplMeas1=  MF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "M°F" );
        ComplMeas1=  GF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "G°F" );
        ComplMeas1=  TF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "T°F" );
        ComplMeas1=  PF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "P°F" );
        ComplMeas1=  EF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "E°F" );
        ComplMeas1=  ZF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Z°F" );
        ComplMeas1=  YF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Y°F" );
    }

    void OperatorAssignAndEqualDegKelvin()
    {
        ComplMeas1=  fK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "f°K" );
        ComplMeas1=  pK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "p°K" );
        ComplMeas1=  nK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "n°K" );
        ComplMeas1=  uK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==mu+"°K" );
        ComplMeas1=  mK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "m°K" );
        ComplMeas1=  cK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "c°K" );
        ComplMeas1=  dK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "d°K" );
        ComplMeas1=   K ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  K );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==   "°K" );
        ComplMeas1= daK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()== "da°K" );
        ComplMeas1=  HK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "H°K" );
        ComplMeas1=  kK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "k°K" );
        ComplMeas1=  MK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "M°K" );
        ComplMeas1=  GK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "G°K" );
        ComplMeas1=  TK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "T°K" );
        ComplMeas1=  PK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "P°K" );
        ComplMeas1=  EK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "E°K" );
        ComplMeas1=  ZK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Z°K" );
        ComplMeas1=  YK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.Short()==  "Y°K" );
    }
    void OperatorAssignAndEqualComplexExpression()
    {
        // debug uA*V*kF == V*uA*kF
        CComplexMeasure CheckThis(uA*F*kF);
        CComplexMeasure CheckOther(V*uA*kF);
        CheckThis.Normalize();
        CheckOther.Normalize();
        CComplexMeasure Step1;
        Step1 = CheckThis / CheckOther;
        
        CComplexMeasure Step2(Step1);
        Step2.Simplify();
        CComplexMeasure Step3(Step2);
        Step3.Normalize();
        
        ComplMeas1 = uA*V*kF;
        CPPUNIT_ASSERT_MESSAGE( CheckThis.Short() + "\t" + CheckOther.Short() + "\n" +
                                Step1.Short() + "\n" +
                                Step2.Short() + "\n"+
                                Step3.Short() , ComplMeas1 == (V*uA*kF));
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + ComplMeas1.Short(), ComplMeas1.CMExp10() == 0 );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + ComplMeas1.Short(), ComplMeas1.CMFactor() == 1 );
    }
    void Simplify()
    {
        
        ComplMeas1 = uK/cC*V*uA/K*kF*MC;
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short()+ "\n" +  (V*uA*kF).Short(), ComplMeas1.Short() == (V*uA*kF).Short() );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + ComplMeas1.Short(), ComplMeas1.CMExp10() == -6+8);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + ComplMeas1.Short(), ComplMeas1.CMFactor() == 1);
    }
void ComplexMeasureTest()
    {
       
        ////////////////////////////////////////////////////
        // CComplexMeasure constructor / operator
        ////////////////////////////////////////////////////
        ComplMeas1 = ns;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.Short() == "ns" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas2 = nV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.Short() == "nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMFactor() == 1.);
        ComplMeas1 *= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.Short() == "ns*nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1 = ns*nV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.Short() == "ns*nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1 = ns*nV/mA*TK/mC;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() , ComplMeas1.Short() == "ns*nV/mA*T°K/m°C" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() , ComplMeas1.Short() == "s*V/A*°K/°C" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1*=mA/ns/mK;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() , ComplMeas1.Short() == "s*V/A*°K/°C*mA/ns/m°K" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() , ComplMeas1.Short() == "V/°C" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 9);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);

        
        ////////////////////////////////////////////////////
        // collect CMFactor and CMExp10
        ////////////////////////////////////////////////////
        ComplMeas1.SetByID(pmNano,bmVolt);
        ComplMeas2.SetByID(pmFemto,bmAmpere);
        
        CComplexMeasure cm1bn(ComplMeas1);
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.Short() == "V");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == -9);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1);
 
        CComplexMeasure cm1an(ComplMeas1);
        
        CComplexMeasure cm2bn(ComplMeas2);
        ComplMeas2.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.Short() == "A");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMExp10() == -15);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMFactor() == 1);
 
        CComplexMeasure cm2an(ComplMeas2);
        ComplMeas2 *= ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.Short() == "A*V");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMExp10() == -24);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMFactor() == 1.0);

        CPPUNIT_ASSERT_MESSAGE( "ComplMeas1 before Norm: \n" +  cm1bn.DebugOut() + "\n\n" +
                                "ComplMeas1 after Norm:\n" + cm1an.DebugOut() + "\n\n" +
                                "ComplMeas2 before Norm: \n" +  cm2bn.DebugOut() + "\n\n" +
                                "ComplMeas2 after Norm:\n" + cm2an.DebugOut() + "\n\n" +
                                "ComplMeas2 * ComplMeas1:\n" + ComplMeas2.DebugOut() + "\n\n",
                                ComplMeas2.Short() == "A*V");
        CPPUNIT_ASSERT_MESSAGE( "ComplMeas1 before Norm: \n" +  cm1bn.DebugOut() + "\n\n" +
                                "ComplMeas1 after Norm:\n" + cm1an.DebugOut() + "\n\n" +
                                "ComplMeas2 before Norm: \n" +  cm2bn.DebugOut() + "\n\n" +
                                "ComplMeas2 after Norm:\n" + cm2an.DebugOut() + "\n\n" +
                                "ComplMeas2 * ComplMeas1:\n" + ComplMeas2.DebugOut() + "\n\n",
                                ComplMeas2.CMExp10() == -24);
        CPPUNIT_ASSERT_MESSAGE( "ComplMeas1 before Norm: \n" +  cm1bn.DebugOut() + "\n\n" +
                                "ComplMeas1 after Norm:\n" + cm1an.DebugOut() + "\n\n" +
                                "ComplMeas2 before Norm: \n" +  cm2bn.DebugOut() + "\n\n" +
                                "ComplMeas2 after Norm:\n" + cm2an.DebugOut() + "\n\n" +
                                "ComplMeas2 * ComplMeas1:\n" + ComplMeas2.DebugOut() + "\n\n",
                                ComplMeas2.CMFactor() == 1 );
        //constructor by ID
        ComplMeas1.SetByID(pmMilli,bmVolt);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short()  , ComplMeas1.Short() == "mV" );

//         copy constructor with pointer
        CComplexMeasure ComplMeas4(ComplMeas1);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas4.Short()  , ComplMeas4.Short() == "mV" );

//         = operator
        ComplMeas1.SetByID(pmCenti,bmAmpere);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short()  , ComplMeas1.Short() == "cA" );
        ComplMeas2 = ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.Short() + "\n" + ComplMeas1.Short() , ComplMeas2.Short() == ComplMeas1.Short() );
        
//         operator *= for expression with *operator
        ComplMeas2.SetByID(pmMicro,bmDegCelsius);
        ComplMeas2 *= ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.Short()  , ComplMeas2.Short() ==  mu + "°C*cA");
                
//         operator = with complex measurses (= 2)
        ComplMeas3 = ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() + "\n" + ComplMeas3.Short() , ComplMeas3.Short() == ComplMeas1.Short());
        
//         operator /=
        ComplMeas1 /= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short()  , ComplMeas1.Short() ==  "cA/" + mu + "°C/cA" );

        
//         check longer expressions for complex measures
        ComplMeas1 /= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short()  , ComplMeas1.Short() ==  "cA/" + mu + "°C/cA/" + mu + "°C/cA" );
        ComplMeas2 *= ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.Short()  , ComplMeas2.Short() ==  mu + "°C*cA*cA/" + mu + "°C/cA/" + mu + "°C/cA" );

//         todo: operator= shorter than before e.g. from 7 elements to 6 elements or less
        ComplMeas2 = ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.Short()  , ComplMeas2.Short() ==  "cA/" + mu + "°C/cA/" + mu + "°C/cA" ); 
        
        
//         operator = with complex measurses (= 7)  
        ComplMeas3 = ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.Short() + string("\n") + ComplMeas3.Short() , ComplMeas3.Short() == ComplMeas2.Short());
        
//         check external operator*
        ComplMeas3 = ComplMeas1*ComplMeas2;
        ComplMeas1 *= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() + string("\n") + ComplMeas3.Short() , ComplMeas3.Short() == ComplMeas1.Short());
        
//         simple check for status of the complex measure
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() , ComplMeas1.Short() == "cA/" + mu + "°C/cA/" + mu + "°C/cA*" +
            "cA/" + mu + "°C/cA/" + mu + "°C/cA");
        
//         normalize ... where possible
//         cA/u°C/cA/u°C/cA*cA/u°C/cA/u°C/cA
//         --> A/°C/A/°C/A*A/°C/A/°C/A
//         --> nCMExp10: c/u/c/u/c*c/u/c/u/c
//                           = -2+6+2+6+2-2+6+2+6+2 
//                           = 4*6 + 2*2 = 24 +4 = 28
//         --> dfCMFactor 1
        ComplMeas2=ComplMeas1;
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() , ComplMeas1.Short() == "A/°C/A/°C/A*A/°C/A/°C/A" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 28 );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1 );
        
        ComplMeas1 = cV*ms/mV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() , ComplMeas1.Short() == "cV*ms/mV" );
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short() , ComplMeas1.Short() == "V*s/V" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == -2 );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1 );
        
        ComplMeas2 = ComplMeas1;
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() + "\nafter:\n" + ComplMeas1.DebugOut() , ComplMeas1.Short() == "s" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == -2);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1 );
         
        ComplMeas1 = ms;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.Short() == "ms" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
         
        ComplMeas1 = ms*mV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.Short() == "ms*mV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        
        ComplMeas1 = ms*mV/nV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.Short() == "ms*mV/nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        
        // expected "ms" / pmMilli / 1.0
        // received: "ms" / pmPiko / 1.0
        ComplMeas2 = ComplMeas1;
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() + "\nafter:\n" + ComplMeas1.DebugOut(), ComplMeas1.Short() == "ms");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() + "\nafter:\n" + ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 6);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.0);
        
        // check operator ==
        ComplMeas1 = mV/mA;
        ComplMeas2 = V/mA;
        ComplMeas3 = ComplMeas1 / ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.Short()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.Short() == "mV/mA/V*mA");
        ComplMeas3.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.Short()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.Short() == "1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.Short()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.CMExp10() == -3);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.Short()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.CMFactor() == 1);
        ComplMeas3.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.Short()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.Short() == "1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.Short()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.CMExp10() == -3);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.Short()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.CMFactor() == 1);
        
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + 
                                ComplMeas2.DebugOut() + "\n"+ 
                                ComplMeas3.DebugOut() , ComplMeas1 != ComplMeas2);
        
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + 
                                ComplMeas2.DebugOut() + "\n"+ 
                                ComplMeas3.DebugOut() , ComplMeas1.Compatible(ComplMeas2));
        
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + 
                                ComplMeas2.DebugOut() + "\n"+ 
                                ComplMeas3.DebugOut() , ComplMeas2.Compatible(ComplMeas1));
        
        ComplMeas1 = mV/mA;
        ComplMeas1.Simplify();
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Short() == "V/A");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMFactor() == 1);
        
        ComplMeas1 = mV/mA;
        ComplMeas2 = V/A;
        ComplMeas1 /= ComplMeas2;
        ComplMeas1.Simplify();
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Short() == "1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMFactor() == 1);
        
        ComplMeas1 = mV/mA;
        ComplMeas2 = V/A;
        ComplMeas3 = ComplMeas1;
        ComplMeas3 /= ComplMeas2;
        ComplMeas4 = ComplMeas3;
        ComplMeas4.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + 
                                ComplMeas2.DebugOut() + "\n"+ 
                                (ComplMeas3).DebugOut() + "\n"+ 
                                (ComplMeas4).DebugOut() + "\n", ComplMeas1 == ComplMeas2);
        ComplMeas2 = ZV/ZA;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + 
                                ComplMeas2.DebugOut() + "\n", ComplMeas1 == ComplMeas2);
        
        
        ComplMeas1 = V/mA*TK/ps*uV;
        ComplMeas2 = ZV/cA*mV*daK/s;
        ComplMeas3 = ComplMeas1 / ComplMeas2;
        ComplMeas3.Simplify();
        ComplMeas3.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() + "\n" + 
                                ComplMeas2.DebugOut() + "\n" + 
                                ComplMeas3.DebugOut(), ComplMeas1 == ComplMeas2);
        
        // ScaleTo
        ComplMeas1 = mV;
        ComplMeas1.ScaleTo(kV);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Short() == "kV");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == -6);
        
        
               // rescaling: do this->operator/( other )--> Simplify:
        // should result in a dimensionless number with the corresponding factors
        ComplMeas1 = uA/mV;
        ComplMeas1 /= uA/kV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Short() == mu+"A/mV/" + mu + "A*kV");
        
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Short() == "1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMFactor() == 1);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 6);
        
        ComplMeas1 = uA/mV;
        ComplMeas1.ScaleTo(uA/kV);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Short() == mu+"A/kV");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 6);
        
        ComplMeas1.SetByID(pmIdent,bmNumber);
        ComplMeas1 = cmIdent/s;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Short() == "1/s");
        
        ComplMeas1 /= cmIdent/h;        
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short(), ComplMeas1.Short() == "1/s/1*h");
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.Short(), ComplMeas1.Short() == "1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMFactor() == 3600.);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 0);
        
        
        
        
        
        
        ComplMeas1 = cmIdent/s;
        ComplMeas1.ScaleTo(cmIdent/h);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Short() == "1/h");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMFactor() == 3600.);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 0);
        
        // ::Valid
        ComplMeas1 = mV*A*us*CComplexMeasure(pmUnknown,bmAmpere)*m/us;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), !ComplMeas1.Valid());
        
        ComplMeas1 = mV*A*us*CComplexMeasure(pmIdent,bmAmpere)*m/us;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Valid());
        
        ComplMeas1 = mV*A*us*CComplexMeasure(pmIdent,bmUnknown)*m/us;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), !ComplMeas1.Valid());
    }
    
    void ComplexMeasure_Parse()
    {
        CComplexMeasure cm2Compare = mm * ks / mm / h / min * V / mA;
        CComplexMeasure cmResult; cmResult.Parse(cm2Compare.Short());
        
        CPPUNIT_ASSERT_MESSAGE( cmResult.DebugOut(), cmResult == cm2Compare);
    }
     
 };
