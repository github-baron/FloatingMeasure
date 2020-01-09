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
        CPPUNIT_ASSERT_MESSAGE( cfTest1.PrintShort() + "\n" +
                                cfTest1.DebugOut(),
                                cfTest1.PrintShort() == "10*mV" );
        
        // scale to
        cfTest1.ScaleTo(1*kV);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 0.00001 );
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == kV );
        
        // operator +=
        CFloatingMeasure cfTest2;
        cfTest2 = 220*V;
        CFloatingMeasure cfTest3;
        cfTest1 += cfTest2;
        cfTest1.Precision(1*mV);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 0.220010 );
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == kV );
        
        cfTest2 = 312.3432*GV;
        // 312.3432         GV - 
        //   0.000000220010 GV = 
        // 312.34319977999
        cfTest2 -= cfTest1;
        cfTest2.Precision(1*cV);
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut(), cfTest2.Floating() == 312.34319977999 );
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut(), cfTest2.Measure() == GV );
        
        cfTest2.Precision(1*dV);
        cfTest2.PrecisionActive(true);
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut(), cfTest2.Floating() == 312.34319978000 );
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut(), cfTest2.Measure() == GV );
        
        cfTest1 = 10*V;
        cfTest2 = 1000*h;
        cfTest3 = 0.134342*uA;
        cfTest3 *= cfTest2*cfTest1;
        cfTest3.ScaleTo(V*A*h);
        CPPUNIT_ASSERT_MESSAGE( cfTest3.DebugOut(), cfTest3.Floating() == 0.00134342 );
        CPPUNIT_ASSERT_MESSAGE( cfTest3.DebugOut(), cfTest3.Measure() == V*A*h );
        
        // operator == ...
        cfTest1 = 0.00000001*uV;
        cfTest2 = 0.01*pV;
        cfTest1.PrecisionActive(false);
        cfTest2.PrecisionActive(false);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut() + "\n" + cfTest2.DebugOut() + "\n" +
        cfTest1.PrintShort() + "\n" + cfTest2.PrintShort(), cfTest1 == cfTest2 );
        
        // ::Valid
        cfTest1 = 10*myNAN*uV;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), !cfTest1.Valid());
        
        cfTest1 = 10*uV;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Valid());
        
        cfTest1 = 10*uV/us*kV*ZA/CComplexMeasure(pmUnknown,bmAmpere)*uA/kV;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), !cfTest1.Valid());
        
        cfTest1 = 10*uV*us*kV*ZA/CComplexMeasure(pmUnknown,bmAmpere)*uA/kV;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), !cfTest1.Valid());
        
        
    }
    void DigFloatTest()
    {
        
        CDigFloat dfFac1(1);
        
        // setting precision 
        dfFac1.Precision(4);
        dfFac1.PrecisionActive(true);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut(), dfFac1.PrecisionActive() );
        
        dfFac1 = 0.99989;
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut(), dfFac1.PrecisionActive() );
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut(), dfFac1 == 0.9999);
        
        dfFac1.PrecisionActive(false);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut(), dfFac1 == 0.99989);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut(), dfFac1 != 0.9999);
        
        
        // checking precision
        CDigFloat dfFac2(0.99988);
        dfFac2.Precision(5);
        dfFac2.PrecisionActive(true);
        dfFac1.Precision(5);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut() + "\n" + dfFac2.DebugOut() , dfFac1 != dfFac2);
        
        dfFac1.Precision(4);
        dfFac1.PrecisionActive(true);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut() , dfFac1 == 0.9999);
        dfFac2.Precision(4);
        CPPUNIT_ASSERT_MESSAGE( dfFac2.DebugOut() , dfFac2 == 0.9999);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut() + "\n" + dfFac2.DebugOut(), dfFac1 == dfFac2);
        
        // ::Valid
        CPPUNIT_ASSERT_MESSAGE( dfFac2.DebugOut() , dfFac2.Valid());
        dfFac2 = myNAN;
        CPPUNIT_ASSERT_MESSAGE( dfFac2.DebugOut() , !dfFac2.Valid());
        
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
        dfFac1/dfFac2 == CDigFloat(10);
        CPPUNIT_ASSERT_MESSAGE( "exp = " + to_string(0) + "\n" + dfFac1.Print() + "\n" + dfFac2.Print()+ "\n" + (dfFac1/dfFac2 ).Print(),
                                    dfFac1/dfFac2 == CDigFloat(10));
    
        //check operator /=
        //this is pretty constant and finishes at 307 times 
        dfFac1.Precision(10);
        dfFac2.Precision(10);
        dfFac3.Precision(10);
        for(int iexp = 0; iexp < 307; iexp++)
        {   
            CPPUNIT_ASSERT_MESSAGE( "exp = " + to_string(iexp) + "\n" + dfFac1.DebugOut() + "\n" + dfFac2.DebugOut()+ "\n" + (dfFac1/dfFac2).DebugOut(),
                                        (dfFac1/dfFac2) ==10 &&(dfFac1/dfFac2 ).Error() < 0.00004);
            dfFac1 /=10;
            dfFac2 /=10;
            
            
        }
        
        // check operator *=
        // this is pretty constant and finishes at 307 times 
        for(int iexp = 0; iexp < 307; iexp++)
        {   
            CPPUNIT_ASSERT_MESSAGE( "exp = " + to_string(iexp) + "\n" + dfFac1.Print() + "\n" + dfFac2.Print()+ "\n" + (dfFac1/dfFac2).Print(),
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
                CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(SIBM) + "\n" +
                                        BASE->DebugOut(BASE->SIID(ActBM )),
                                        BASE->DebugOut(SIBM ) ==BASE->DebugOut(BASE->SIID(ActBM )) );
        
        
            // check for unique namings short and long
            for( int j = i+1; j < bmLast; j++)
            {
                eBaseMeasure OtherActBM = (eBaseMeasure )(j);
                // check for unique short labels
                CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + "\n" + BASE->DebugOut(OtherActBM), BASE->Short(ActBM) != BASE->Short(OtherActBM) );
                
                // check for unique long labels
                CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + "\n" + BASE->DebugOut(OtherActBM), BASE->Long(ActBM) != BASE->Long(OtherActBM) );
        
                //check of unique SI recalculation
                if( BASE->SIID(ActBM) == BASE->SIID(OtherActBM) )
                    CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + "\n" + BASE->DebugOut(OtherActBM), BASE->Factor(ActBM) != BASE->Factor(OtherActBM) || 
                                                                                                       BASE->Offset(ActBM) != BASE->Offset(OtherActBM));
        
                
            }
                
        }
        
        
    }
    
    void ComplexMeasureTest()
    {
        // helping variables
        ostringstream ossDoublSI;
        
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
        
        // ::Valid
        ComplMeas1 = mV*A*us*CComplexMeasure(pmUnknown,bmAmpere)*m/us;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), !ComplMeas1.Valid());
        
        ComplMeas1 = mV*A*us*CComplexMeasure(pmIdent,bmAmpere)*m/us;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), ComplMeas1.Valid());
        
        ComplMeas1 = mV*A*us*CComplexMeasure(pmIdent,bmUnknown)*m/us;
        CPPUNIT_ASSERT_MESSAGE( ComplMeas1.DebugOut(), !ComplMeas1.Valid());
    }
    
    void SimpleMeasureTest()
    {
        
        Measure1.SetByShort("f","V");
        
        // copy constructor
        CSimpleMeasure Measure4( Measure1);
        CPPUNIT_ASSERT_MESSAGE( Measure4.DebugOut() + "\n"+ Measure1.DebugOut() , Measure4.DebugOut() == Measure1.DebugOut());
        
        // SetByID
        Measure2.SetByID( Measure1.PreID(), Measure1.BaseID());
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut());
            
        // = operator 
        Measure2.SetByShort("m","A");
        Measure2 = Measure1;
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut());
        
        Measure1.SetByShort("f","V");    
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "fV");
        
        Measure1.SetByShort("p","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "pV");
        
        Measure1.SetByShort("n","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "nV");
        
        Measure1.SetByShort(mu,"V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == mu + "V");

        Measure1.SetByShort("m","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "mV");

        Measure1.SetByShort("c","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.01);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "cV");

        Measure1.SetByShort("d","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.1);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "dV");

        Measure1.SetByShort("","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "V");

        Measure1.SetByShort("da","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 10);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "daV");

        Measure1.SetByShort("H","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 100);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "HV");

        Measure1.SetByShort("k","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "kV");

        Measure1.SetByShort("M","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "MV");

        Measure1.SetByShort("G","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "GV");

        Measure1.SetByShort("T","V");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000000000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "TV");
        //------------------------ resistor --------------------------------
        
        
        Measure1.SetByShort("f",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "f"+Omega);
        
        Measure1.SetByShort("p",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "p"+Omega);
        
        Measure1.SetByShort("n",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "n"+Omega);
        
        Measure1.SetByShort(mu,Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == mu + Omega);

        Measure1.SetByShort("m",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "m"+Omega);

        Measure1.SetByShort("c",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.01);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "c"+Omega);

        Measure1.SetByShort("d",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 0.1);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "d"+Omega);

        Measure1.SetByShort("",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == Omega);

        Measure1.SetByShort("da",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 10);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "da"+Omega);

        Measure1.SetByShort("H",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 100);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "H"+Omega);

        Measure1.SetByShort("k",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "k"+Omega);

        Measure1.SetByShort("M",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "M"+Omega);

        Measure1.SetByShort("G",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "G"+Omega);

        Measure1.SetByShort("T",Omega);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000000000000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "T"+Omega);
        
        // ----------------- temperature ------------------
        Measure1.SetByShort("f","°F");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 5./9.*0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "f°F");
        
        Measure1.SetByShort("","°F");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 5./9.);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIOffset() == 32-5./9.*273.15);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "°F");
        
        Measure1.SetByShort("m","°F");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 5./9.*0.001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIOffset() == (32-5./9.*273.15) * 0.001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "m°F");
        
        Measure1.SetByShort("","°C");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1.);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIOffset() == 273.15);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "°C");
        
        Measure1.SetByShort("k","°C");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000.);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIOffset() == (273.15)*1000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "k°C");
        
        // ----------------- temperature ------------------
        Measure1.SetByShort("f","h");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 3600.*0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "fh");
                
        Measure1.SetByShort("k","d");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 3600.*24.*1000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "kd");
        
    }
    void PreMeasureTest()
    {
        // check factors
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmFemto) , PRE->Factor(pmFemto)== 0.000000000000001 )        ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPiko)  , PRE->Factor(pmPiko) == 0.000000000001 )           ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmNano)  , PRE->Factor(pmNano) == 0.000000001 )              ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMicro) , PRE->Factor(pmMicro)== 0.000001 )                 ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMilli) , PRE->Factor(pmMilli)== 0.001 )                    ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmCenti) , PRE->Factor(pmCenti)== 0.01 )                     ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeci)  , PRE->Factor(pmDeci) == 0.1 )                      ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmIdent) , PRE->Factor(pmIdent)== 1.0 )                      ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeca)  , PRE->Factor(pmDeca) == 10.)                        ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmHecto) , PRE->Factor(pmHecto)== 100.)                       ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmKilo)  , PRE->Factor(pmKilo) == 1000.)                      ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMega)  , PRE->Factor(pmMega) == 1000000.)                   ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmGiga)  , PRE->Factor(pmGiga) == 1000000000.)                ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmTera)  , PRE->Factor(pmTera) == 1000000000000.)             ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPeta)  , PRE->Factor(pmPeta) == 1000000000000000.)          ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmExa)   , PRE->Factor(pmExa)  == 1000000000000000000.)       ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmZetta) , PRE->Factor(pmZetta)== 1000000000000000000000.)    ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmYotta) , PRE->Factor(pmYotta)== 1000000000000000000000000.) ;
        
           
        // simply check expected exponents
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmFemto) + " : " + to_string(PRE->Exp10(pmFemto))  , PRE->Exp10(pmFemto)== -15) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPiko)  + " : " + to_string(PRE->Exp10(pmPiko) )  , PRE->Exp10(pmPiko) == -12) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmNano)  + " : " + to_string(PRE->Exp10(pmNano) )  , PRE->Exp10(pmNano) == -9 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMicro) + " : " + to_string(PRE->Exp10(pmMicro))  , PRE->Exp10(pmMicro)== -6 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMilli) + " : " + to_string(PRE->Exp10(pmMilli))  , PRE->Exp10(pmMilli)== -3 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmCenti) + " : " + to_string(PRE->Exp10(pmCenti))  , PRE->Exp10(pmCenti)== -2 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeci)  + " : " + to_string(PRE->Exp10(pmDeci) )  , PRE->Exp10(pmDeci) == -1 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmIdent) + " : " + to_string(PRE->Exp10(pmIdent))  , PRE->Exp10(pmIdent)==  0 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeca)  + " : " + to_string(PRE->Exp10(pmDeca) )  , PRE->Exp10(pmDeca) == +1 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmHecto) + " : " + to_string(PRE->Exp10(pmHecto))  , PRE->Exp10(pmHecto)== +2 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmKilo)  + " : " + to_string(PRE->Exp10(pmKilo) )  , PRE->Exp10(pmKilo) == +3 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMega)  + " : " + to_string(PRE->Exp10(pmMega) )  , PRE->Exp10(pmMega) == +6 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmGiga)  + " : " + to_string(PRE->Exp10(pmGiga) )  , PRE->Exp10(pmGiga) == +9 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmTera)  + " : " + to_string(PRE->Exp10(pmTera) )  , PRE->Exp10(pmTera) == +12) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPeta)  + " : " + to_string(PRE->Exp10(pmPeta) )  , PRE->Exp10(pmPeta) == +15) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmExa)   + " : " + to_string(PRE->Exp10(pmExa)  )  , PRE->Exp10(pmExa)  == +18) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmZetta) + " : " + to_string(PRE->Exp10(pmZetta))  , PRE->Exp10(pmZetta)== +21) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmYotta) + " : " + to_string(PRE->Exp10(pmYotta))  , PRE->Exp10(pmYotta)== +24) ;
     
        // getting PreMeasure ID by factor                                  
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000000000000001 )) + "' : " + to_string(PRE->GetIDByFactor(0.000000000000001 ) )  , PRE->GetIDByFactor(0.000000000000001 ) == (pmFemto));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000000000001 )   ) + "' : " + to_string(PRE->GetIDByFactor(0.000000000001 )    )  , PRE->GetIDByFactor(0.000000000001 )    == (pmPiko) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000000001 )      ) + "' : " + to_string(PRE->GetIDByFactor(0.000000001 )       )  , PRE->GetIDByFactor(0.000000001 )       == (pmNano) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000001 )         ) + "' : " + to_string(PRE->GetIDByFactor(0.000001 )          )  , PRE->GetIDByFactor(0.000001 )          == (pmMicro));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.001 )            ) + "' : " + to_string(PRE->GetIDByFactor(0.001 )             )  , PRE->GetIDByFactor(0.001 )             == (pmMilli));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.01 )             ) + "' : " + to_string(PRE->GetIDByFactor(0.01 )              )  , PRE->GetIDByFactor(0.01 )              == (pmCenti));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.1 )              ) + "' : " + to_string(PRE->GetIDByFactor(0.1 )               )  , PRE->GetIDByFactor(0.1 )               == (pmDeci) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1.0 )              ) + "' : " + to_string(PRE->GetIDByFactor(1.0 )               )  , PRE->GetIDByFactor(1.0 )               == (pmIdent));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(10)                ) + "' : " + to_string(PRE->GetIDByFactor(10)                 )  , PRE->GetIDByFactor(10)                 == (pmDeca) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(100)               ) + "' : " + to_string(PRE->GetIDByFactor(100)                )  , PRE->GetIDByFactor(100)                == (pmHecto));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000)              ) + "' : " + to_string(PRE->GetIDByFactor(1000)               )  , PRE->GetIDByFactor(1000)               == (pmKilo) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000000)           ) + "' : " + to_string(PRE->GetIDByFactor(1000000)            )  , PRE->GetIDByFactor(1000000)            == (pmMega) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000000000)        ) + "' : " + to_string(PRE->GetIDByFactor(1000000000)         )  , PRE->GetIDByFactor(1000000000)         == (pmGiga) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000000000000)     ) + "' : " + to_string(PRE->GetIDByFactor(1000000000000)      )  , PRE->GetIDByFactor(1000000000000)      == (pmTera) );
        
        
        // check for GetIDByExp10:
        // this function gets an exponent and takes the closest preMeasure index
        int nExp10 = -15;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmFemto) );
         nExp10 = -14;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmFemto) );
         nExp10 = -13;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPiko) );
         nExp10 = -12;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPiko) );
         nExp10 = -11;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPiko) );
         nExp10 = -10;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmNano) );
         nExp10 = -9;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmNano) );
         nExp10 = -8;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmNano) );
         nExp10 = -7;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMicro) );
         nExp10 = -6;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMicro) );
         nExp10 = -5;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMicro) );
         nExp10 = -4;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMilli) );
         nExp10 = -3;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMilli) );
         nExp10 = -2;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmCenti));
         nExp10 = -1;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmDeci)  );
         nExp10 = 0;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmIdent) );
         nExp10 = 1;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmDeca) );
         nExp10 = 2;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmHecto) );
         nExp10 = 3;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmKilo) );
         nExp10 = 4;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmKilo) );
        nExp10 = 5;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMega) );
        nExp10 = 6;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMega) );
        nExp10 = 7;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMega) );
        nExp10 = 8;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmGiga) );
        nExp10 = 9;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmGiga) );
        nExp10 = 10;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmGiga) );
        nExp10 = 11;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmTera) );
        nExp10 = 12;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmTera) );
        nExp10 = 13;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmTera) );
        nExp10 = 14;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPeta) );
        nExp10 = 15;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPeta) );
        nExp10 = 16;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPeta) );
        nExp10 = 17;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmExa) );
        nExp10 = 18;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmExa) );
        nExp10 = 19;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmExa) );
        nExp10 = 20;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmZetta) );
        nExp10 = 21;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmZetta) );
        nExp10 = 22;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmZetta) );
        nExp10 = 23;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmYotta) );
        nExp10 = 24;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmYotta) );
        nExp10 = 25;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmYotta) );
        
        
        

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
    std::string testPath = (argc > 1) ? string(argv[1]) : std::string("");
    
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

