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

// include all test classes
#include "PreMeasure_Test.cpp"
#include "BaseMeasure_Test.cpp"
#include "SimpleMeasure_Test.cpp"
#include "ComplexMeasure_Test.cpp"

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
        // scale to temperature
        cfTest1 = 10*mC;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 10);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == mC );

        cfTest1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 273.15+0.01);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == K );
         
        
        cfTest1.ScaleTo(mC);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 10);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == mC );
        
        
        
        
   
        cfTest1 = 10*mV;
        // scale to
        cfTest1.ScaleTo(1*kV);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 0.00001 );
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == kV );
        
        cfTest1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 0.01 );
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == V );
         
        cfTest1.ScaleTo(mV);
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
        
        // check operators with inversion
        cfTest1 = mV*10;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1 == 10*mV);
        
        cfTest1 = 10*uA/mV*10;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1 == 100*uA/mV);
        
        
        // velocity check
        cfTest1 = 3.6*m;
        cfTest2 = 1*s;
        cfTest3 = cfTest1 / cfTest2;
        CPPUNIT_ASSERT_MESSAGE( cfTest3.DebugOut(), cfTest3 == 3.6*m/s);
        cfTest3.Precision(0.1*m/s);
        cfTest3.PrecisionActive(true);
        CPPUNIT_ASSERT_MESSAGE( cfTest3.PrintShort(), cfTest3.PrintShort() == "3.6*m/s");
        
        cfTest3.Precision(0.00001*km/h);
        cfTest3.ScaleTo(km/h);
        CPPUNIT_ASSERT_MESSAGE( cfTest3.DebugOut() + "\n" + cfTest3.PrintShort(), cfTest3 == 3.6*km/h/1000.*3600.);
        
  /*      debugging scalTo
        cfTest2 = 10/s;
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut() + "\n" + cfTest2.PrintShort(), cfTest2 == 10/s);
        cfTest2.ScaleTo(1/h);
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut() + "\n" + cfTest2.PrintShort(), cfTest2 == 10/h*3600.);
        
        
        cfTest3.ScaleTo(km/h);
        CPPUNIT_ASSERT_MESSAGE( cfTest3.DebugOut() + "\n" + cfTest3.PrintShort(), cfTest3 == 3.6*km/h/1000./1000.*3600.);
  */      
        
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
//     void BaseMeasureTest()
//     {
//         helping variable 
//         eBaseMeasure ActBM, SIBM ;
//         
//         
//         reference to SI for all
//         for(int i = 0; i< bmLast; i++)
//         {
//             ActBM = (eBaseMeasure )(i);
//             SIBM = BASE->SIID(ActBM);
//                 CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(SIBM) + "\n" +
//                                         BASE->DebugOut(BASE->SIID(ActBM )),
//                                         BASE->DebugOut(SIBM ) ==BASE->DebugOut(BASE->SIID(ActBM )) );
//         
//         
//             check for unique namings short and long
//             for( int j = i+1; j < bmLast; j++)
//             {
//                 eBaseMeasure OtherActBM = (eBaseMeasure )(j);
//                 check for unique short labels
//                 CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + "\n" + BASE->DebugOut(OtherActBM), BASE->Short(ActBM) != BASE->Short(OtherActBM) );
//                 
//                 check for unique long labels
//                 CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + "\n" + BASE->DebugOut(OtherActBM), BASE->Long(ActBM) != BASE->Long(OtherActBM) );
//         
//                 check of unique SI recalculation
//                 if( BASE->SIID(ActBM) == BASE->SIID(OtherActBM) )
//                     CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + "\n" + BASE->DebugOut(OtherActBM), BASE->Factor(ActBM) != BASE->Factor(OtherActBM) || 
//                                                                                                        BASE->Offset(ActBM) != BASE->Offset(OtherActBM));
//         
//                 
//             }
//                 
//         }
//         
//         
//     }
//     
    
     
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
    
    // declare all tests
    CPreMeasure_Test PreMeasureTest;
    CBaseMeasure_Test BaseMeasureTest;
    CSimpleMeasure_Test SimpleMeasureTest;
    CComplexMeasure_Test ComplexMeasureTest;
    
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

    ///////////////////////////////////////////////
    // add all tests of CBaseMeasure_Test
    ///////////////////////////////////////////////
    runner.addTest( new CppUnit::TestCaller<CBaseMeasure_Test> ( 
                    "BaseMeasure: consistent SI references",
                    &CBaseMeasure_Test::SIReference,
                    &BaseMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CBaseMeasure_Test> ( 
                    "BaseMeasure: unique short labels",
                    &CBaseMeasure_Test::UniqueShortLabel,
                    &BaseMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CBaseMeasure_Test> ( 
                    "BaseMeasure: unique long labels",
                    &CBaseMeasure_Test::UniqueLongLabel,
                    &BaseMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CBaseMeasure_Test> ( 
                    "BaseMeasure: unique SI factors",
                    &CBaseMeasure_Test::UniqueSIFactor,
                    &BaseMeasureTest
                    )
                  );
    
    ///////////////////////////////////////////////
    // add all tests of CPreMeasure_Test
    ///////////////////////////////////////////////
    runner.addTest( new CppUnit::TestCaller<CPreMeasure_Test> ( 
                    "PreMeasure: check factors",
                    &CPreMeasure_Test::CheckFactors,
                    &PreMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CPreMeasure_Test> ( 
                    "PreMeasure: check exponents",
                    &CPreMeasure_Test::CheckExponents,
                    &PreMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CPreMeasure_Test> ( 
                    "PreMeasure: check getting ID by factor",
                    &CPreMeasure_Test::CheckGetIDByFactor,
                    &PreMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CPreMeasure_Test> ( 
                    "PreMeasure: check getting ID by exp10",
                    &CPreMeasure_Test::CheckGetIDByExp10,
                    &PreMeasureTest
                    )
                  );


    ///////////////////////////////////////////////
    // add all tests of CSimpleMeasure_Test
    ///////////////////////////////////////////////
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: copy constructor",
                    &CSimpleMeasure_Test::CopyConstructor,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: operator =",
                    &CSimpleMeasure_Test::OperatorEqual,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByID by other",
                    &CSimpleMeasure_Test::SetByIDOther,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort voltage measure",
                    &CSimpleMeasure_Test::SetByShortVoltage,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort resistor measure",
                    &CSimpleMeasure_Test::SetByShortResistor,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort temperature measure",
                    &CSimpleMeasure_Test::SetByShortTemperature,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort time measure",
                    &CSimpleMeasure_Test::SetByShortTime,
                    &SimpleMeasureTest
                    )
                  );

    ///////////////////////////////////////////////
    // add all tests of CComplexMeasure_Test
    ///////////////////////////////////////////////
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: construction",
                        &CComplexMeasure_Test::Construction,
                        &ComplexMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: operator= and operator== for voltage",
                        &CComplexMeasure_Test::OperatorAssignAndEqualVoltage,
                        &ComplexMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: operator= and operator== for current",
                        &CComplexMeasure_Test::OperatorAssignAndEqualCurrent,
                        &ComplexMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: operator= and operator== for seconds",
                        &CComplexMeasure_Test::OperatorAssignAndEqualSeconds,
                        &ComplexMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: operator= and operator== for °C",
                        &CComplexMeasure_Test::OperatorAssignAndEqualDegCelcius,
                        &ComplexMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: operator= and operator== for °F",
                        &CComplexMeasure_Test::OperatorAssignAndEqualDegFahrenheit,
                        &ComplexMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: operator= and operator== for °K",
                        &CComplexMeasure_Test::OperatorAssignAndEqualDegKelvin,
                        &ComplexMeasureTest
                        )
                  );
    
    
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: operator== detail f°C",
                        &CComplexMeasure_Test::OperatorEqualDetail,
                        &ComplexMeasureTest
                        )
                  );
    
    
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

