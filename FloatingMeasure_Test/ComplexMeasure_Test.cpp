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
#include "Measure/ComplexMeasure.h"
#include "Measure/ComplexMeasureMacros.h"
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
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.PrintAllShort() == "ns" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);        
    }
    void Construction()
    {
        // default constructor
        pCM1 = new CComplexMeasure();
        CPPUNIT_ASSERT_MESSAGE( pCM1->DebugOut() , pCM1->PrintAllShort() == "");
        
        // constructor by ID
        pCM2 = new CComplexMeasure(pmTera,bmHertz);
        CPPUNIT_ASSERT_MESSAGE( pCM2->DebugOut() , pCM2->PrintAllShort() == "THz" );
        
        // constructor by &other
        SecureDeleteObjectPointer(pCM1);
        ComplMeas1 = km;
        pCM1 = new CComplexMeasure(ComplMeas1);
        CPPUNIT_ASSERT_MESSAGE( pCM1->DebugOut() , pCM1->PrintAllShort() == "km" );
        
        // constructor by *other
        SecureDeleteObjectPointer(pCM1);
        pCM1 = new CComplexMeasure(pCM2);
        CPPUNIT_ASSERT_MESSAGE( pCM1->DebugOut() , pCM1->PrintAllShort() == "THz" );
        
    }
    void OperatorAssignAndEqualVoltage()
    {
        ComplMeas1=  fV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "fV" );
        ComplMeas1=  pV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "pV" );
        ComplMeas1=  nV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "nV" );
        ComplMeas1=  uV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==mu+"V" );
        ComplMeas1=  mV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "mV" );
        ComplMeas1=  cV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "cV" );
        ComplMeas1=  dV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "dV" );
        ComplMeas1=   V ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  V );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==   "V" );
        ComplMeas1= daV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()== "daV" );
        ComplMeas1=  HV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "HV" );
        ComplMeas1=  kV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "kV" );
        ComplMeas1=  MV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "MV" );
        ComplMeas1=  GV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "GV" );
        ComplMeas1=  TV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "TV" );
        ComplMeas1=  PV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "PV" );
        ComplMeas1=  EV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "EV" );
        ComplMeas1=  ZV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "ZV" );
        ComplMeas1=  YV ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YV );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "YV" );
    }
    
    void OperatorAssignAndEqualCurrent()
    {
        ComplMeas1=  fA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "fA" );
        ComplMeas1=  pA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "pA" );
        ComplMeas1=  nA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "nA" );
        ComplMeas1=  uA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==mu+"A" );
        ComplMeas1=  mA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "mA" );
        ComplMeas1=  cA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "cA" );
        ComplMeas1=  dA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "dA" );
        ComplMeas1=   A ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  A );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==   "A" );
        ComplMeas1= daA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()== "daA" );
        ComplMeas1=  HA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "HA" );
        ComplMeas1=  kA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "kA" );
        ComplMeas1=  MA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "MA" );
        ComplMeas1=  GA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "GA" );
        ComplMeas1=  TA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "TA" );
        ComplMeas1=  PA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "PA" );
        ComplMeas1=  EA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "EA" );
        ComplMeas1=  ZA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "ZA" );
        ComplMeas1=  YA ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YA );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "YA" );
    }

    void OperatorAssignAndEqualSeconds()
    {
        ComplMeas1=  fs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "fs" );
        ComplMeas1=  ps ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ps );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "ps" );
        ComplMeas1=  ns ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ns );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "ns" );
        ComplMeas1=  us ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== us );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==mu+"s" );
        ComplMeas1=  ms ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ms );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "ms" );
        ComplMeas1=  cs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "cs" );
        ComplMeas1=  ds ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ds );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "ds" );
        ComplMeas1=   s ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  s );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==   "s" );
        ComplMeas1= das ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==das );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()== "das" );
        ComplMeas1=  Hs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Hs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Hs" );
        ComplMeas1=  ks ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ks );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "ks" );
        ComplMeas1=  Ms ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Ms );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Ms" );
        ComplMeas1=  Gs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Gs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Gs" );
        ComplMeas1=  Ts ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Ts );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Ts" );
        ComplMeas1=  Ps ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Ps );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Ps" );
        ComplMeas1=  Es ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Es );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Es" );
        ComplMeas1=  Zs ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Zs );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Zs" );
        ComplMeas1=  Ys ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== Ys );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Ys" );
    }

    void OperatorAssignAndEqualDegCelcius()
    {
        ComplMeas1=  fC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "f°C" );
        ComplMeas1=  pC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "p°C" );
        ComplMeas1=  nC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "n°C" );
        ComplMeas1=  uC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==mu+"°C" );
        ComplMeas1=  mC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "m°C" );
        ComplMeas1=  cC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "c°C" );
        ComplMeas1=  dC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "d°C" );
        ComplMeas1=   C ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  C );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==   "°C" );
        ComplMeas1= daC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()== "da°C" );
        ComplMeas1=  HC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "H°C" );
        ComplMeas1=  kC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "k°C" );
        ComplMeas1=  MC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "M°C" );
        ComplMeas1=  GC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "G°C" );
        ComplMeas1=  TC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "T°C" );
        ComplMeas1=  PC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "P°C" );
        ComplMeas1=  EC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "E°C" );
        ComplMeas1=  ZC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Z°C" );
        ComplMeas1=  YC ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YC );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Y°C" );
    }

    void OperatorAssignAndEqualDegFahrenheit()
    {
        ComplMeas1=  fF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "f°F" );
        ComplMeas1=  pF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "p°F" );
        ComplMeas1=  nF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "n°F" );
        ComplMeas1=  uF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==mu+"°F" );
        ComplMeas1=  mF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "m°F" );
        ComplMeas1=  cF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "c°F" );
        ComplMeas1=  dF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "d°F" );
        ComplMeas1=   F ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  F );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==   "°F" );
        ComplMeas1= daF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()== "da°F" );
        ComplMeas1=  HF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "H°F" );
        ComplMeas1=  kF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "k°F" );
        ComplMeas1=  MF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "M°F" );
        ComplMeas1=  GF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "G°F" );
        ComplMeas1=  TF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "T°F" );
        ComplMeas1=  PF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "P°F" );
        ComplMeas1=  EF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "E°F" );
        ComplMeas1=  ZF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Z°F" );
        ComplMeas1=  YF ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YF );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Y°F" );
    }

    void OperatorAssignAndEqualDegKelvin()
    {
        ComplMeas1=  fK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== fK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "f°K" );
        ComplMeas1=  pK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== pK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "p°K" );
        ComplMeas1=  nK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== nK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "n°K" );
        ComplMeas1=  uK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== uK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==mu+"°K" );
        ComplMeas1=  mK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== mK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "m°K" );
        ComplMeas1=  cK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== cK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "c°K" );
        ComplMeas1=  dK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== dK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "d°K" );
        ComplMeas1=   K ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==  K );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==   "°K" );
        ComplMeas1= daK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1==daK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()== "da°K" );
        ComplMeas1=  HK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== HK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "H°K" );
        ComplMeas1=  kK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== kK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "k°K" );
        ComplMeas1=  MK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== MK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "M°K" );
        ComplMeas1=  GK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== GK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "G°K" );
        ComplMeas1=  TK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== TK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "T°K" );
        ComplMeas1=  PK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== PK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "P°K" );
        ComplMeas1=  EK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== EK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "E°K" );
        ComplMeas1=  ZK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== ZK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Z°K" );
        ComplMeas1=  YK ;CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1== YK );CPPUNIT_ASSERT_MESSAGE(ComplMeas1.DebugOut(),ComplMeas1.PrintAllShort()==  "Y°K" );
    }
void ComplexMeasureTest()
    {
       
        ////////////////////////////////////////////////////
        // CComplexMeasure constructor / operator
        ////////////////////////////////////////////////////
        ComplMeas1 = ns;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.PrintAllShort() == "ns" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas2 = nV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.PrintAllShort() == "nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMFactor() == 1.);
        ComplMeas1 *= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.PrintAllShort() == "ns*nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1 = ns*nV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.PrintAllShort() == "ns*nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1 = ns*nV/mA*TK/mC;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == "ns*nV/mA*T°K/m°C" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == "s*V/A*°K/°C" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1*=mA/ns/mK;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == "s*V/A*°K/°C*mA/ns/m°K" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == "V/°C" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 9);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);

        
        ////////////////////////////////////////////////////
        // collect CMFactor and CMExp10
        ////////////////////////////////////////////////////
        ComplMeas1.SetByID(pmNano,bmVolt);
        ComplMeas2.SetByID(pmFemto,bmAmpere);
        
        CComplexMeasure cm1bn(ComplMeas1);
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.PrintAllShort() == "V");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == -9);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1);
 
        CComplexMeasure cm1an(ComplMeas1);
        
        CComplexMeasure cm2bn(ComplMeas2);
        ComplMeas2.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.PrintAllShort() == "A");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMExp10() == -15);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMFactor() == 1);
 
        CComplexMeasure cm2an(ComplMeas2);
        ComplMeas2 *= ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.PrintAllShort() == "A*V");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMExp10() == -24);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() , ComplMeas2.CMFactor() == 1.0);

        CPPUNIT_ASSERT_MESSAGE( "ComplMeas1 before Norm: \n" +  cm1bn.DebugOut() + "\n\n" +
                                "ComplMeas1 after Norm:\n" + cm1an.DebugOut() + "\n\n" +
                                "ComplMeas2 before Norm: \n" +  cm2bn.DebugOut() + "\n\n" +
                                "ComplMeas2 after Norm:\n" + cm2an.DebugOut() + "\n\n" +
                                "ComplMeas2 * ComplMeas1:\n" + ComplMeas2.DebugOut() + "\n\n",
                                ComplMeas2.PrintAllShort() == "A*V");
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
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort()  , ComplMeas1.PrintAllShort() == "mV" );

//         copy constructor with pointer
        CComplexMeasure ComplMeas4(ComplMeas1);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas4.PrintAllShort()  , ComplMeas4.PrintAllShort() == "mV" );

//         = operator
        ComplMeas1.SetByID(pmCenti,bmAmpere);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort()  , ComplMeas1.PrintAllShort() == "cA" );
        ComplMeas2 = ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.PrintAllShort() + "\n" + ComplMeas1.PrintAllShort() , ComplMeas2.PrintAllShort() == ComplMeas1.PrintAllShort() );
        
//         operator *= for expression with *operator
        ComplMeas2.SetByID(pmMicro,bmDegCelsius);
        ComplMeas2 *= ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.PrintAllShort()  , ComplMeas2.PrintAllShort() ==  mu + "°C*cA");
                
//         operator = with complex measurses (= 2)
        ComplMeas3 = ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() + "\n" + ComplMeas3.PrintAllShort() , ComplMeas3.PrintAllShort() == ComplMeas1.PrintAllShort());
        
//         operator /=
        ComplMeas1 /= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort()  , ComplMeas1.PrintAllShort() ==  "cA/" + mu + "°C/cA" );

        
//         check longer expressions for complex measures
        ComplMeas1 /= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort()  , ComplMeas1.PrintAllShort() ==  "cA/" + mu + "°C/cA/" + mu + "°C/cA" );
        ComplMeas2 *= ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.PrintAllShort()  , ComplMeas2.PrintAllShort() ==  mu + "°C*cA*cA/" + mu + "°C/cA/" + mu + "°C/cA" );

//         todo: operator= shorter than before e.g. from 7 elements to 6 elements or less
        ComplMeas2 = ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.PrintAllShort()  , ComplMeas2.PrintAllShort() ==  "cA/" + mu + "°C/cA/" + mu + "°C/cA" ); 
        
        
//         operator = with complex measurses (= 7)  
        ComplMeas3 = ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.PrintAllShort() + string("\n") + ComplMeas3.PrintAllShort() , ComplMeas3.PrintAllShort() == ComplMeas2.PrintAllShort());
        
//         check external operator*
        ComplMeas3 = ComplMeas1*ComplMeas2;
        ComplMeas1 *= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() + string("\n") + ComplMeas3.PrintAllShort() , ComplMeas3.PrintAllShort() == ComplMeas1.PrintAllShort());
        
//         simple check for status of the complex measure
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == "cA/" + mu + "°C/cA/" + mu + "°C/cA*" +
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
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == "A/°C/A/°C/A*A/°C/A/°C/A" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 28 );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1 );
        
        ComplMeas1 = cV*ms/mV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == "cV*ms/mV" );
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == "V*s/V" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == -2 );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1 );
        
        ComplMeas2 = ComplMeas1;
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() + "\nafter:\n" + ComplMeas1.DebugOut() , ComplMeas1.PrintAllShort() == "s" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == -2);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1 );
         
        ComplMeas1 = ms;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.PrintAllShort() == "ms" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
         
        ComplMeas1 = ms*mV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.PrintAllShort() == "ms*mV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        
        ComplMeas1 = ms*mV/nV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.PrintAllShort() == "ms*mV/nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.);
        
        // expected "ms" / pmMilli / 1.0
        // received: "ms" / pmPiko / 1.0
        ComplMeas2 = ComplMeas1;
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() + "\nafter:\n" + ComplMeas1.DebugOut(), ComplMeas1.PrintAllShort() == "ms");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut() + "\nafter:\n" + ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 6);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut() , ComplMeas1.CMFactor() == 1.0);
        
        // check operator ==
        ComplMeas1 = mV/mA;
        ComplMeas2 = V/mA;
        ComplMeas3 = ComplMeas1 / ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.PrintAllShort() == "mV/mA/V*mA");
        ComplMeas3.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.PrintAllShort() == "1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.CMExp10() == -3);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.CMFactor() == 1);
        ComplMeas3.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.PrintAllShort() == "1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.CMExp10() == -3);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + "\n" +ComplMeas3.DebugOut(), ComplMeas3.CMFactor() == 1);
        
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
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.PrintAllShort() == "V/A");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMFactor() == 1);
        
        ComplMeas1 = mV/mA;
        ComplMeas2 = V/A;
        ComplMeas1 /= ComplMeas2;
        ComplMeas1.Simplify();
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.PrintAllShort() == "1");
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
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.PrintAllShort() == "kV");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == -6);
        
        
               // rescaling: do this->operator/( other )--> Simplify:
        // should result in a dimensionless number with the corresponding factors
        ComplMeas1 = uA/mV;
        ComplMeas1 /= uA/kV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.PrintAllShort() == mu+"A/mV/" + mu + "A*kV");
        
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.PrintAllShort() == "1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMFactor() == 1);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 6);
        
        ComplMeas1 = uA/mV;
        ComplMeas1.ScaleTo(uA/kV);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.PrintAllShort() == mu+"A/kV");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 6);
        
        ComplMeas1.SetByID(pmIdent,bmNumber);
        ComplMeas1 = cmIdent/s;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.PrintAllShort() == "1/s");
        
        ComplMeas1 /= cmIdent/h;        
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort(), ComplMeas1.PrintAllShort() == "1/s/1*h");
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort(), ComplMeas1.PrintAllShort() == "1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMFactor() == 3600.);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.CMExp10() == 0);
        
        
        
        
        
        
        ComplMeas1 = cmIdent/s;
        ComplMeas1.ScaleTo(cmIdent/h);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.PrintAllShort() == "1/h");
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
     
 };
