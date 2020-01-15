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

#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TextTestProgressListener.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/XmlOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <stdexcept>
#include <fstream>

// #include "Measure_Test.cpp"

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

// testing stuff
#include <FloatingMeasure/FloatingMeasure.h>
#include <Measure/ComplexMeasureMacros.h>

class Measure_test : public CppUnit::TestFixture{
private:    
    CSimpleMeasure Measure1, Measure2;
    CBaseMeasure bMeasure1, bMeasure2;
    CComplexMeasure ComplMeas1, ComplMeas2, ComplMeas3;
public:
    void setUp()
    {
    }

    void tearDown() 
    {
        
    }
    void FloatingMeasureTest()
    {
        CFloatingMeasure cfTest1;
        cfTest1 = 10*mV;
        cfTest1.Precision(0.000001*kV);
        cfTest1.PrecisionActive(true);
        CPPUNIT_ASSERT_MESSAGE( (cfTest1.PrintShort() + L"\n" +
                                cfTest1.DebugOut()).c_str(),
                                cfTest1.PrintShort() == L"10*mV" );
        
        // scale to
        cfTest1.ScaleTo(1*kV);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut().c_str, cfTest1.Floating() == 0.00001 );
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut().c_str, cfTest1.Measure() == kV );
        
        // operator +=
        CFloatingMeasure cfTest2;
        cfTest2 = 220*V;
        CFloatingMeasure cfTest3;
        cfTest1 += cfTest2;
        cfTest1.Precision(1*mV);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut().c_str, cfTest1.Floating() == 0.220010 );
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut().c_str, cfTest1.Measure() == kV );
        
        cfTest2 = 312.3432*GV;
        // 312.3432         GV - 
        //   0.000000220010 GV = 
        // 312.34319977999
        cfTest2 -= cfTest1;
        cfTest2.Precision(1*cV);
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut().c_str, cfTest2.Floating() == 312.34319977999 );
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut().c_str, cfTest2.Measure() == GV );
        
        cfTest2.Precision(1*dV);
        cfTest2.PrecisionActive(true);
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut().c_str, cfTest2.Floating() == 312.34319978000 );
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut().c_str, cfTest2.Measure() == GV );
        
        cfTest1 = 10*V;
        cfTest2 = 1000*h;
        cfTest3 = 0.134342*uA;
        cfTest3 *= cfTest2*cfTest1;
        cfTest3.ScaleTo(V*A*h);
        CPPUNIT_ASSERT_MESSAGE( cfTest3.DebugOut().c_str, cfTest3.Floating() == 0.00134342 );
        CPPUNIT_ASSERT_MESSAGE( cfTest3.DebugOut().c_str, cfTest3.Measure() == V*A*h );
        
        // operator == ...
        cfTest1 = 0.00000001*uV;
        cfTest2 = 0.01*pV;
        cfTest1.PrecisionActive(false);
        cfTest2.PrecisionActive(false);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut().c_str + L"\n" + cfTest2.DebugOut().c_str + L"\n" +
        cfTest1.PrintShort().c_str + L"\n" + cfTest2.PrintShort().c_str, cfTest1 == cfTest2 );
        
        // ::Valid
        cfTest1 = 10*myNAN*uV;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut().c_str, !cfTest1.Valid());
        
        cfTest1 = 10*uV;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut().c_str, cfTest1.Valid());
        
        cfTest1 = 10*uV/us*kV*ZA/CComplexMeasure(pmUnknown,bmAmpere)*uA/kV;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut().c_str, !cfTest1.Valid());
        
        cfTest1 = 10*uV*us*kV*ZA/CComplexMeasure(pmUnknown,bmAmpere)*uA/kV;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut().c_str, !cfTest1.Valid());
        
        
    }
    void DigFloatTest()
    {
        
        CDigFloat dfFac1(1);
        
        // setting precision 
        dfFac1.Precision(4);
        dfFac1.PrecisionActive(true);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut().c_str, dfFac1.PrecisionActive() );
        
        dfFac1 = 0.99989;
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut().c_str, dfFac1.PrecisionActive() );
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut().c_str, dfFac1 == 0.9999);
        
        dfFac1.PrecisionActive(false);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut().c_str, dfFac1 == 0.99989);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut().c_str, dfFac1 != 0.9999);
        
        
        // checking precision
        CDigFloat dfFac2(0.99988);
        dfFac2.Precision(5);
        dfFac2.PrecisionActive(true);
        dfFac1.Precision(5);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut().c_str + L"\n" + dfFac2.DebugOut().c_str , dfFac1 != dfFac2);
        
        dfFac1.Precision(4);
        dfFac1.PrecisionActive(true);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut().c_str , dfFac1 == 0.9999);
        dfFac2.Precision(4);
        CPPUNIT_ASSERT_MESSAGE( dfFac2.DebugOut().c_str , dfFac2 == 0.9999);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut().c_str + L"\n" + dfFac2.DebugOut().c_str, dfFac1 == dfFac2);
        
        // ::Valid
        CPPUNIT_ASSERT_MESSAGE( dfFac2.DebugOut().c_str , dfFac2.Valid());
        dfFac2 = myNAN;
        CPPUNIT_ASSERT_MESSAGE( dfFac2.DebugOut().c_str , !dfFac2.Valid());
        
        // operator = double
        dfFac2 = 0.1;
        CDigFloat dfFac3(10);
        CPPUNIT_ASSERT_MESSAGE( dfFac3.Print() , dfFac3 == 10);
        
        // ::Value(double)
        dfFac1.Value(101);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.Print() , dfFac1 == 101);

        // operator *=
        dfFac1 *=dfFac3;
        CPPUNIT_ASSERT_MESSAGE( dfFac1.Print() , dfFac1 == 1010);

        dfFac1 *=10;
        CPPUNIT_ASSERT_MESSAGE( dfFac1.Print() , dfFac1 == 10100);


        // operator /=
        dfFac2 /=10.;
        dfFac1 = dfFac2 * 10; 
        CPPUNIT_ASSERT_MESSAGE( L"exp = " + to_wstring(0) + L"\n" + dfFac1.Print() + L"\n" + dfFac2.Print()+ L"\n" + (dfFac1/dfFac2 ).Print(),
                                    dfFac1/dfFac2 == CDigFloat(10));
    
        //check operator /=
        //this is pretty constant and finishes at 307 times 
        dfFac1.Precision(10);
        dfFac2.Precision(10);
        dfFac3.Precision(10);
        for(int iexp = 0; iexp < 307; iexp++)
        {   
            CPPUNIT_ASSERT_MESSAGE( L"exp = " + to_wstring(iexp) + L"\n" + dfFac1.DebugOut().c_str + L"\n" + dfFac2.DebugOut().c_str+ "\n" + (dfFac1/dfFac2).DebugOut().c_str,
                                        (dfFac1/dfFac2) ==10 &&(dfFac1/dfFac2 ).Error() < 0.00004);
            dfFac1 /=10;
            dfFac2 /=10;
            
            
        }
        
        // check operator *=
        // this is pretty constant and finishes at 307 times 
        for(int iexp = 0; iexp < 307; iexp++)
        {   
            CPPUNIT_ASSERT_MESSAGE( L"exp = " + to_wstring(iexp) + L"\n" + dfFac1.Print() + L"\n" + dfFac2.Print()+ "\n" + (dfFac1/dfFac2).Print(),
                                        (dfFac1/dfFac2) == 10 &&
                                  (dfFac3 ).Error() < 0.004);
            dfFac1 *=10;
            dfFac2 *=10;
            
        }
    }
    void BaseMeasureTest()
    {
        // helping variable 
        eBaseMeasure ActBM, SIBM ;
        
        
        // reference to SI for all
        for(int i = 0; i< bmLast; i++)
        {
            ActBM = (eBaseMeasure )(i);
            SIBM = BASE->SIID(ActBM);
                CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(SIBM) + L"\n" +
                                        BASE->DebugOut(BASE->SIID(ActBM )),
                                        BASE->DebugOut(SIBM ) ==BASE->DebugOut(BASE->SIID(ActBM )) );
        
        
            // check for unique namings short and long
            for( int j = i+1; j < bmLast; j++)
            {
                eBaseMeasure OtherActBM = (eBaseMeasure )(j);
                // check for unique short labels
                CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + L"\n" + BASE->DebugOut(OtherActBM), BASE->Short(ActBM) != BASE->Short(OtherActBM) );
                
                // check for unique long labels
                CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + L"\n" + BASE->DebugOut(OtherActBM), BASE->Long(ActBM) != BASE->Long(OtherActBM) );
        
                //check of unique SI recalculation
                if( BASE->SIID(ActBM) == BASE->SIID(OtherActBM) )
                    CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + L"\n" + BASE->DebugOut(OtherActBM), BASE->Factor(ActBM) != BASE->Factor(OtherActBM) || 
                                                                                                       BASE->Offset(ActBM) != BASE->Offset(OtherActBM));
        
                
            }
                
        }
        
        
    }
    
    void ComplexMeasureTest()
    {
        // helping variables
        wostringstream ossDoublSI;
        
        ////////////////////////////////////////////////////
        // CComplexMeasure constructor / operator
        ////////////////////////////////////////////////////
        ComplMeas1 = ns;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.PrintAllShort() == L"ns" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);
        ComplMeas2 = nV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str , ComplMeas2.PrintAllShort() == L"nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str , ComplMeas2.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str , ComplMeas2.CMFactor() == 1.);
        ComplMeas1 *= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.PrintAllShort() == L"ns*nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);
        ComplMeas1 = ns*nV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.PrintAllShort() == L"ns*nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);
        ComplMeas1 = ns*nV/mA*TK/mC;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == L"ns*nV/mA*T°K/m°C" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == L"s*V/A*°K/°C" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);
        ComplMeas1*=mA/ns/mK;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == L"s*V/A*°K/°C*mA/ns/m°K" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == L"V/°C" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 9);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);

        
        ////////////////////////////////////////////////////
        // collect CMFactor and CMExp10
        ////////////////////////////////////////////////////
        ComplMeas1.SetByID(pmNano,bmVolt);
        ComplMeas2.SetByID(pmFemto,bmAmpere);
        
        CComplexMeasure cm1bn(ComplMeas1);
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.PrintAllShort() == L"V");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == -9);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1);
 
        CComplexMeasure cm1an(ComplMeas1);
        
        CComplexMeasure cm2bn(ComplMeas2);
        ComplMeas2.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str , ComplMeas2.PrintAllShort() == L"A");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str , ComplMeas2.CMExp10() == -15);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str , ComplMeas2.CMFactor() == 1);
 
        CComplexMeasure cm2an(ComplMeas2);
        ComplMeas2 *= ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str , ComplMeas2.PrintAllShort() == L"A*V");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str , ComplMeas2.CMExp10() == -24);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str , ComplMeas2.CMFactor() == 1.0);

        CPPUNIT_ASSERT_MESSAGE( L"ComplMeas1 before Norm: \n" +  cm1bn.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas1 after Norm:\n" + cm1an.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas2 before Norm: \n" +  cm2bn.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas2 after Norm:\n" + cm2an.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas2 * ComplMeas1:\n" + ComplMeas2.DebugOut().c_str + L"\n\n",
                                ComplMeas2.PrintAllShort() == L"A*V");
        CPPUNIT_ASSERT_MESSAGE( L"ComplMeas1 before Norm: \n" +  cm1bn.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas1 after Norm:\n" + cm1an.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas2 before Norm: \n" +  cm2bn.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas2 after Norm:\n" + cm2an.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas2 * ComplMeas1:\n" + ComplMeas2.DebugOut().c_str + L"\n\n",
                                ComplMeas2.CMExp10() == -24);
        CPPUNIT_ASSERT_MESSAGE( L"ComplMeas1 before Norm: \n" +  cm1bn.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas1 after Norm:\n" + cm1an.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas2 before Norm: \n" +  cm2bn.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas2 after Norm:\n" + cm2an.DebugOut().c_str + L"\n\n" +
                                L"ComplMeas2 * ComplMeas1:\n" + ComplMeas2.DebugOut().c_str + L"\n\n",
                                ComplMeas2.CMFactor() == 1 );
        //constructor by ID
        ComplMeas1.SetByID(pmMilli,bmVolt);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort()  , ComplMeas1.PrintAllShort() == L"mV" );

//         copy constructor with pointer
        CComplexMeasure ComplMeas4(ComplMeas1);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas4.PrintAllShort()  , ComplMeas4.PrintAllShort() == L"mV" );

//         = operator
        ComplMeas1.SetByID(pmCenti,bmAmpere);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort()  , ComplMeas1.PrintAllShort() == L"cA" );
        ComplMeas2 = ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.PrintAllShort() + L"\n" + ComplMeas1.PrintAllShort() , ComplMeas2.PrintAllShort() == ComplMeas1.PrintAllShort() );
        
//         operator *= for expression with *operator
        ComplMeas2.SetByID(pmMicro,bmDegCelsius);
        ComplMeas2 *= ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.PrintAllShort()  , ComplMeas2.PrintAllShort() ==  mu + "°C*cA");
                
//         operator = with complex measurses (= 2)
        ComplMeas3 = ComplMeas1;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() + L"\n" + ComplMeas3.PrintAllShort() , ComplMeas3.PrintAllShort() == ComplMeas1.PrintAllShort());
        
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
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.PrintAllShort() + wstring(L"\n") + ComplMeas3.PrintAllShort() , ComplMeas3.PrintAllShort() == ComplMeas2.PrintAllShort());
        
//         check external operator*
        ComplMeas3 = ComplMeas1*ComplMeas2;
        ComplMeas1 *= ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() + wstring(L"\n") + ComplMeas3.PrintAllShort() , ComplMeas3.PrintAllShort() == ComplMeas1.PrintAllShort());
        
//         simple check for status of the complex measure
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == L"cA/" + mu + "°C/cA/" + mu + "°C/cA*" +
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
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == L"A/°C/A/°C/A*A/°C/A/°C/A" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 28 );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1 );
        
        ComplMeas1 = cV*ms/mV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == L"cV*ms/mV" );
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.PrintAllShort() , ComplMeas1.PrintAllShort() == L"V*s/V" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == -2 );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1 );
        
        ComplMeas2 = ComplMeas1;
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str + "\nafter:\n" + ComplMeas1.DebugOut().c_str , ComplMeas1.PrintAllShort() == L"s" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == -2);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1 );
         
        ComplMeas1 = ms;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.PrintAllShort() == L"ms" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);
         
        ComplMeas1 = ms*mV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.PrintAllShort() == L"ms*mV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);
        
        ComplMeas1 = ms*mV/nV;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.PrintAllShort() == L"ms*mV/nV" );
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.);
        
        // expected "ms" / pmMilli / 1.0
        // received: "ms" / pmPiko / 1.0
        ComplMeas2 = ComplMeas1;
        ComplMeas1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str + "\nafter:\n" + ComplMeas1.DebugOut().c_str, ComplMeas1.PrintAllShort() == L"ms");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas2.DebugOut().c_str + "\nafter:\n" + ComplMeas1.DebugOut().c_str, ComplMeas1.CMExp10() == 6);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str , ComplMeas1.CMFactor() == 1.0);
        
        // check operator ==
        ComplMeas1 = mV/mA;
        ComplMeas2 = V/mA;
        ComplMeas3 = ComplMeas1 / ComplMeas2;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + L"\n" +ComplMeas3.DebugOut().c_str, ComplMeas3.PrintAllShort() == L"mV/mA/V*mA");
        ComplMeas3.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + L"\n" +ComplMeas3.DebugOut().c_str, ComplMeas3.PrintAllShort() == L"1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + L"\n" +ComplMeas3.DebugOut().c_str, ComplMeas3.CMExp10() == -3);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + L"\n" +ComplMeas3.DebugOut().c_str, ComplMeas3.CMFactor() == 1);
        ComplMeas3.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + L"\n" +ComplMeas3.DebugOut().c_str, ComplMeas3.PrintAllShort() == L"1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + L"\n" +ComplMeas3.DebugOut().c_str, ComplMeas3.CMExp10() == -3);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas3.PrintAllShort()  + L"\n" +ComplMeas3.DebugOut().c_str, ComplMeas3.CMFactor() == 1);
        
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str + L"\n" + 
                                ComplMeas2.DebugOut().c_str + L"\n"+ 
                                ComplMeas3.DebugOut().c_str , ComplMeas1 != ComplMeas2);
        
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str + L"\n" + 
                                ComplMeas2.DebugOut().c_str + L"\n"+ 
                                ComplMeas3.DebugOut().c_str , ComplMeas1.Compatible(ComplMeas2));
        
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str + L"\n" + 
                                ComplMeas2.DebugOut().c_str + L"\n"+ 
                                ComplMeas3.DebugOut().c_str , ComplMeas2.Compatible(ComplMeas1));
        
        ComplMeas1 = mV/mA;
        ComplMeas1.Simplify();
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, ComplMeas1.PrintAllShort() == L"V/A");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, ComplMeas1.CMFactor() == 1);
        
        ComplMeas1 = mV/mA;
        ComplMeas2 = V/A;
        ComplMeas1 /= ComplMeas2;
        ComplMeas1.Simplify();
        ComplMeas1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, ComplMeas1.PrintAllShort() == L"1");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, ComplMeas1.CMExp10() == 0);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, ComplMeas1.CMFactor() == 1);
        
        ComplMeas1 = mV/mA;
        ComplMeas2 = V/A;
        ComplMeas3 = ComplMeas1;
        ComplMeas3 /= ComplMeas2;
        ComplMeas4 = ComplMeas3;
        ComplMeas4.Simplify();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str + L"\n" + 
                                ComplMeas2.DebugOut().c_str + L"\n"+ 
                                (ComplMeas3).DebugOut().c_str + L"\n"+ 
                                (ComplMeas4).DebugOut().c_str + L"\n", ComplMeas1 == ComplMeas2);
        ComplMeas2 = ZV/ZA;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str + L"\n" + 
                                ComplMeas2.DebugOut().c_str + L"\n", ComplMeas1 == ComplMeas2);
        
        
        ComplMeas1 = V/mA*TK/ps*uV;
        ComplMeas2 = ZV/cA*mV*daK/s;
        ComplMeas3 = ComplMeas1 / ComplMeas2;
        ComplMeas3.Simplify();
        ComplMeas3.Normalize();
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str + L"\n" + 
                                ComplMeas2.DebugOut().c_str + L"\n" + 
                                ComplMeas3.DebugOut().c_str, ComplMeas1 == ComplMeas2);
        
        // ScaleTo
        ComplMeas1 = mV;
        ComplMeas1.ScaleTo(kV);
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, ComplMeas1.PrintAllShort() == L"kV");
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, ComplMeas1.CMExp10() == -6);
        
        // ::Valid
        ComplMeas1 = mV*A*us*CComplexMeasure(pmUnknown,bmAmpere)*m/us;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, !ComplMeas1.Valid());
        
        ComplMeas1 = mV*A*us*CComplexMeasure(pmIdent,bmAmpere)*m/us;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, ComplMeas1.Valid());
        
        ComplMeas1 = mV*A*us*CComplexMeasure(pmIdent,bmUnknown)*m/us;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut().c_str, !ComplMeas1.Valid());
    }
    
    void SimpleMeasureTest()
    {
        
        Measure1.SetByShort(L"f",L"V");
        
        // copy constructor
        CSimpleMeasure Measure4( Measure1);
        CPPUNIT_ASSERT_MESSAGE( Measure4.DebugOut().c_str + L"\n"+ Measure1.DebugOut().c_str , Measure4.DebugOut() == Measure1.DebugOut().c_str);
        
        // SetByID
        Measure2.SetByID( Measure1.PreID(), Measure1.BaseID());
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str + L"\n"+ Measure2.DebugOut().c_str , Measure1.DebugOut() == Measure2.DebugOut().c_str);
            
        // = operator 
        Measure2.SetByShort(L"m","A");
        Measure2 = Measure1;
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str + L"\n"+ Measure2.DebugOut().c_str , Measure1.DebugOut() == Measure2.DebugOut().c_str);
        
        Measure1.SetByShort(L"f",L"V");    
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"fV");
        
        Measure1.SetByShort(L"p",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"pV");
        
        Measure1.SetByShort(L"n",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"nV");
        
        Measure1.SetByShort(mu,L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == mu + "V");

        Measure1.SetByShort(L"m",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"mV");

        Measure1.SetByShort(L"c",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.01);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"cV");

        Measure1.SetByShort(L"d",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.1);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"dV");

        Measure1.SetByShort(L"",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"V");

        Measure1.SetByShort(L"da",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 10);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"daV");

        Measure1.SetByShort(L"H",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 100);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"HV");

        Measure1.SetByShort(L"k",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"kV");

        Measure1.SetByShort(L"M",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"MV");

        Measure1.SetByShort(L"G",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1000000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"GV");

        Measure1.SetByShort(L"T",L"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1000000000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"TV");
        //------------------------ resistor --------------------------------
        
        
        Measure1.SetByShort(L"f",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"f"+Omega);
        
        Measure1.SetByShort(L"p",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"p"+Omega);
        
        Measure1.SetByShort(L"n",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"n"+Omega);
        
        Measure1.SetByShort(mu,Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == mu + Omega);

        Measure1.SetByShort(L"m",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"m"+Omega);

        Measure1.SetByShort(L"c",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.01);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"c"+Omega);

        Measure1.SetByShort(L"d",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 0.1);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"d"+Omega);

        Measure1.SetByShort(L"",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == Omega);

        Measure1.SetByShort(L"da",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 10);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"da"+Omega);

        Measure1.SetByShort(L"H",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 100);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"H"+Omega);

        Measure1.SetByShort(L"k",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"k"+Omega);

        Measure1.SetByShort(L"M",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"M"+Omega);

        Measure1.SetByShort(L"G",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1000000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"G"+Omega);

        Measure1.SetByShort(L"T",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1000000000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"T"+Omega);
        
        // ----------------- temperature ------------------
        Measure1.SetByShort(L"f",L"°F");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 5./9.*0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"f°F");
        
        Measure1.SetByShort(L"",L"°F");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 5./9.);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIOffset() == 32-5./9.*273.15);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"°F");
        
        Measure1.SetByShort(L"m",L"°F");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 5./9.*0.001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIOffset() == (32-5./9.*273.15) * 0.001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"m°F");
        
        Measure1.SetByShort(L"",L"°C");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1.);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIOffset() == 273.15);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"°C");
        
        Measure1.SetByShort(L"k",L"°C");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 1000.);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIOffset() == (273.15)*1000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"k°C");
        
        // ----------------- temperature ------------------
        Measure1.SetByShort(L"f",L"h");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 3600.*0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"fh");
                
        Measure1.SetByShort(L"k",L"d");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.SIFactor() == 3600.*24.*1000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut().c_str  , Measure1.Short() == L"kd");
        
    }
    void PreMeasureTest()
    {
        // check factors
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmFemto).c_str , PRE->Factor(pmFemto)== 0.000000000000001 )        ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPiko).c_str  , PRE->Factor(pmPiko) == 0.000000000001 )           ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmNano).c_str  , PRE->Factor(pmNano) == 0.000000001 )              ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMicro).c_str , PRE->Factor(pmMicro)== 0.000001 )                 ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMilli).c_str , PRE->Factor(pmMilli)== 0.001 )                    ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmCenti).c_str , PRE->Factor(pmCenti)== 0.01 )                     ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeci).c_str  , PRE->Factor(pmDeci) == 0.1 )                      ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmIdent).c_str , PRE->Factor(pmIdent)== 1.0 )                      ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeca).c_str  , PRE->Factor(pmDeca) == 10.)                        ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmHecto).c_str , PRE->Factor(pmHecto)== 100.)                       ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmKilo).c_str  , PRE->Factor(pmKilo) == 1000.)                      ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMega).c_str  , PRE->Factor(pmMega) == 1000000.)                   ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmGiga).c_str  , PRE->Factor(pmGiga) == 1000000000.)                ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmTera).c_str  , PRE->Factor(pmTera) == 1000000000000.)             ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPeta).c_str  , PRE->Factor(pmPeta) == 1000000000000000.)          ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmExa).c_str   , PRE->Factor(pmExa)  == 1000000000000000000.)       ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmZetta).c_str , PRE->Factor(pmZetta)== 1000000000000000000000.)    ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmYotta).c_str , PRE->Factor(pmYotta)== 1000000000000000000000000.) ;
        
           
        // simply check expected exponents
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmFemto).c_str + " : " + to_wstring(PRE->Exp10(pmFemto)), PRE->Exp10(pmFemto) == -15);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmPiko).c_str + " : " + to_wstring(PRE->Exp10(pmPiko)), PRE->Exp10(pmPiko) == -12);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmNano).c_str + " : " + to_wstring(PRE->Exp10(pmNano)), PRE->Exp10(pmNano) == -9);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmMicro).c_str + " : " + to_wstring(PRE->Exp10(pmMicro)), PRE->Exp10(pmMicro) == -6);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmMilli).c_str + " : " + to_wstring(PRE->Exp10(pmMilli)), PRE->Exp10(pmMilli) == -3);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmCenti).c_str + " : " + to_wstring(PRE->Exp10(pmCenti)), PRE->Exp10(pmCenti) == -2);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmDeci).c_str + " : " + to_wstring(PRE->Exp10(pmDeci)), PRE->Exp10(pmDeci) == -1);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmIdent).c_str + " : " + to_wstring(PRE->Exp10(pmIdent)), PRE->Exp10(pmIdent) == 0);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmDeca).c_str + " : " + to_wstring(PRE->Exp10(pmDeca)), PRE->Exp10(pmDeca) == +1);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmHecto).c_str + " : " + to_wstring(PRE->Exp10(pmHecto)), PRE->Exp10(pmHecto) == +2);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmKilo).c_str + " : " + to_wstring(PRE->Exp10(pmKilo)), PRE->Exp10(pmKilo) == +3);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmMega).c_str + " : " + to_wstring(PRE->Exp10(pmMega)), PRE->Exp10(pmMega) == +6);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmGiga).c_str + " : " + to_wstring(PRE->Exp10(pmGiga)), PRE->Exp10(pmGiga) == +9);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmTera).c_str + " : " + to_wstring(PRE->Exp10(pmTera)), PRE->Exp10(pmTera) == +12);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmPeta).c_str + " : " + to_wstring(PRE->Exp10(pmPeta)), PRE->Exp10(pmPeta) == +15);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmExa).c_str + " : " + to_wstring(PRE->Exp10(pmExa)), PRE->Exp10(pmExa) == +18);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmZetta).c_str + " : " + to_wstring(PRE->Exp10(pmZetta)), PRE->Exp10(pmZetta) == +21);
        CPPUNIT_ASSERT_MESSAGE(PRE->Short(pmYotta).c_str + " : " + to_wstring(PRE->Exp10(pmYotta))  , PRE->Exp10(pmYotta)== +24) ;
     
        // getting PreMeasure ID by factor                                  
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000000000000001 )).c_str + "' : " + to_wstring(PRE->GetIDByFactor(0.000000000000001 ) )  , PRE->GetIDByFactor(0.000000000000001 ) == (pmFemto));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000000000001 )   ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(0.000000000001 )    )  , PRE->GetIDByFactor(0.000000000001 )    == (pmPiko) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000000001 )      ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(0.000000001 )       )  , PRE->GetIDByFactor(0.000000001 )       == (pmNano) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000001 )         ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(0.000001 )          )  , PRE->GetIDByFactor(0.000001 )          == (pmMicro));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.001 )            ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(0.001 )             )  , PRE->GetIDByFactor(0.001 )             == (pmMilli));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.01 )             ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(0.01 )              )  , PRE->GetIDByFactor(0.01 )              == (pmCenti));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.1 )              ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(0.1 )               )  , PRE->GetIDByFactor(0.1 )               == (pmDeci) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1.0 )              ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(1.0 )               )  , PRE->GetIDByFactor(1.0 )               == (pmIdent));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(10)                ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(10)                 )  , PRE->GetIDByFactor(10)                 == (pmDeca) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(100)               ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(100)                )  , PRE->GetIDByFactor(100)                == (pmHecto));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000)              ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(1000)               )  , PRE->GetIDByFactor(1000)               == (pmKilo) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000000)           ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(1000000)            )  , PRE->GetIDByFactor(1000000)            == (pmMega) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000000000)        ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(1000000000)         )  , PRE->GetIDByFactor(1000000000)         == (pmGiga) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000000000000)     ).c_str + "' : " + to_wstring(PRE->GetIDByFactor(1000000000000)      )  , PRE->GetIDByFactor(1000000000000)      == (pmTera) );
        
        
        // check for GetIDByExp10:
        // this function gets an exponent and takes the closest preMeasure index
        int nExp10 = -15;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmFemto) );
         nExp10 = -14;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmFemto) );
         nExp10 = -13;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmPiko) );
         nExp10 = -12;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmPiko) );
         nExp10 = -11;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmPiko) );
         nExp10 = -10;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmNano) );
         nExp10 = -9;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmNano) );
         nExp10 = -8;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmNano) );
         nExp10 = -7;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmMicro) );
         nExp10 = -6;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmMicro) );
         nExp10 = -5;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmMicro) );
         nExp10 = -4;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmMilli) );
         nExp10 = -3;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmMilli) );
         nExp10 = -2;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmCenti));
         nExp10 = -1;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmDeci)  );
         nExp10 = 0;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmIdent) );
         nExp10 = 1;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmDeca) );
         nExp10 = 2;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmHecto) );
         nExp10 = 3;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmKilo) );
         nExp10 = 4;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmKilo) );
        nExp10 = 5;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmMega) );
        nExp10 = 6;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmMega) );
        nExp10 = 7;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmMega) );
        nExp10 = 8;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmGiga) );
        nExp10 = 9;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmGiga) );
        nExp10 = 10;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmGiga) );
        nExp10 = 11;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmTera) );
        nExp10 = 12;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmTera) );
        nExp10 = 13;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmTera) );
        nExp10 = 14;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmPeta) );
        nExp10 = 15;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmPeta) );
        nExp10 = 16;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmPeta) );
        nExp10 = 17;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmExa) );
        nExp10 = 18;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmExa) );
        nExp10 = 19;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmExa) );
        nExp10 = 20;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmZetta) );
        nExp10 = 21;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmZetta) );
        nExp10 = 22;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmZetta) );
        nExp10 = 23;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmYotta) );
        nExp10 = 24;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmYotta) );
        nExp10 = 25;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10)).c_str+"':"+to_wstring(PRE->GetIDByExp10(nExp10)).c_str, PRE->GetIDByExp10(nExp10) == (pmYotta) );
        
        
        

    }
    
//     CPPUNIT_TEST_SUITE( Unit_test );
//     CPPUNIT_TEST(UnitOperation);
//     CPPUNIT_TEST(UnitConversion);
//     CPPUNIT_TEST_SUITE_END();
//     
// public:
//     void UnitOperation();
//     void UnitConversion();    
};
// void Unit_test::UnitConversion()
// {
// }
// void Unit_test::UnitOperation()
// {
// }

int main( int argc, char* argv[] )
{
    // Retreive test path from command line first argument. Default to "" which resolve
    // to the top level suite.
    std::wstring testPath = (argc > 1) ? wstring(argv[1]) : std::string(L"");
    
    // declar the Measure test variable
    Measure_test measTest;

    // Create the event manager and test controller
    CPPUNIT_NS::TestResult controller;

    // Add a listener that colllects test result
    CPPUNIT_NS::TestResultCollector result;
    controller.addListener( &result );        

    // Add a listener that print dots as test run.
    #ifdef WIN32
    CPPUNIT_NS::TextTestProgressListener progress;
    #else
    CPPUNIT_NS::BriefTestProgressListener progress;
    #endif
    controller.addListener( &progress );      

    // Add the top suite to the test runner 
    CPPUNIT_NS::TestRunner runner;
    runner.addTest( new CppUnit::TestCaller<Measure_test> ( 
                        "FloatingMeasure-Test",
                        &Measure_test::FloatingMeasureTest,
                        &measTest
                        )
            );
    runner.addTest( new CppUnit::TestCaller<Measure_test> ( 
                        "DigFloat-Test",
                        &Measure_test::DigFloatTest,
                        &measTest
                        )
            );
    runner.addTest( new CppUnit::TestCaller<Measure_test> ( 
                        "BaseMeasure-Test",
                        &Measure_test::BaseMeasureTest,
                        &measTest
                        )
            );
    runner.addTest( new CppUnit::TestCaller<Measure_test> ( 
                        "PreMeasure-Test",
                        &Measure_test::PreMeasureTest,
                        &measTest
                        )
            );
    runner.addTest( new CppUnit::TestCaller<Measure_test> ( 
                        "SimpleMeasure-Test",
                        &Measure_test::SimpleMeasureTest,
                        &measTest
                        )
            );
    runner.addTest( new CppUnit::TestCaller<Measure_test> ( 
                        "ComplexMeasure-Test",
                        &Measure_test::ComplexMeasureTest,
                        &measTest
                        )
            );
    try
    {
        CPPUNIT_NS::stdCOut() << "Running "  <<  testPath;
        runner.run( controller, testPath );

        CPPUNIT_NS::stdCOut() << "\n";

        // Print test in a compiler compatible format.
        CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
        outputter.write(); 

    // Uncomment this for XML output
    //    std::ofstream file( "tests.xml" );
    //    CPPUNIT_NS::XmlOutputter xml( &result, file );
    //    xml.setStyleSheet( "report.xsl" );
    //    xml.write();
    //    file.close();
    }
    catch ( std::invalid_argument &e )  // Test path not resolved
    {
        CPPUNIT_NS::stdCOut()  <<  "\n"  
                                <<  "ERROR: "  <<  e.what()
                                << "\n";
        return 0;
    }

    return result.wasSuccessful() ? 0 : 1;
    }

