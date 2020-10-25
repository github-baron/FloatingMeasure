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

// include all test classes
#include "PreMeasure_Test.cpp"
#include "BaseMeasure_Test.cpp"
#include "SimpleMeasure_Test.cpp"
#include "ComplexMeasure_Test.cpp"
#include "DigFloat_Test.cpp"
#include "FloatingMeasure_Test.cpp"

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
    CDigFloat_Test DigFloatTest;
    CFloatingMeasure_Test FloatingMeasureTest;

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

    /////////////////////////////////////////////////
    //// add all tests of CBaseMeasure_Test
    /////////////////////////////////////////////////
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
                    "SimpleMeasure: SetByShort, operator = , and operator== voltage",
                    &CSimpleMeasure_Test::SetByShortOperatorAssignAndqEualVoltage,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort, operator = , and operator== current",
                    &CSimpleMeasure_Test::SetByShortOperatorAssignAndqEualCurrent,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort, operator = , and operator== frequency",
                    &CSimpleMeasure_Test::SetByShortOperatorAssignAndqEualFrequency,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort, operator = , and operator== resistor",
                    &CSimpleMeasure_Test::SetByShortOperatorAssignAndqEualResistor, 
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort, operator = , and operator== seconds",
                    &CSimpleMeasure_Test::SetByShortOperatorAssignAndqEualSeconds,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort, operator = , and operator== meter",
                    &CSimpleMeasure_Test::SetByShortOperatorAssignAndqEualMeter,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort, operator = , and operator== °K",
                    &CSimpleMeasure_Test::SetByShortOperatorAssignAndqEualDegKelvin,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort, operator = , and operator== °F",
                    &CSimpleMeasure_Test::SetByShortOperatorAssignAndqEualDegFahrenheit,
                    &SimpleMeasureTest
                    )
                  );
    runner.addTest( new CppUnit::TestCaller<CSimpleMeasure_Test> ( 
                    "SimpleMeasure: SetByShort, operator = , and operator== °C",
                    &CSimpleMeasure_Test::SetByShortOperatorAssignAndqEualDegCelsius,
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
                        "ComplexMeasure: complex expression operator ==",
                        &CComplexMeasure_Test::OperatorAssignAndEqualComplexExpression,
                        &ComplexMeasureTest
                        )
                  );      
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: simplify",
                        &CComplexMeasure_Test::Simplify,
                        &ComplexMeasureTest
                        )
                  );    
    runner.addTest( new CppUnit::TestCaller<CComplexMeasure_Test> ( 
                        "ComplexMeasure: old test ... still to be structured",
                        &CComplexMeasure_Test::ComplexMeasureTest,
                        &ComplexMeasureTest
                        )
                  );
    
    ///////////////////////////////////////////////
    // add all tests of CDigFloat_Test
    ///////////////////////////////////////////////
    runner.addTest( new CppUnit::TestCaller<CDigFloat_Test> ( 
                        "DigFloat: construction",
                        &CDigFloat_Test::Construction,
                        &DigFloatTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CDigFloat_Test> ( 
                        "DigFloat: precision",
                        &CDigFloat_Test::Precision,
                        &DigFloatTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CDigFloat_Test> ( 
                        "DigFloat: valid",
                        &CDigFloat_Test::Valid,
                        &DigFloatTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CDigFloat_Test> ( 
                        "DigFloat: operators",
                        &CDigFloat_Test::Operators,
                        &DigFloatTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CDigFloat_Test> ( 
                        "DigFloat: log function",
                        &CDigFloat_Test::FunctionLog,
                        &DigFloatTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CDigFloat_Test> ( 
                        "DigFloat: pow function",
                        &CDigFloat_Test::FunctionPow,
                        &DigFloatTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CDigFloat_Test> ( 
                        "DigFloat: error propagation",
                        &CDigFloat_Test::ErrorPropagation,
                        &DigFloatTest
                        )
                  );
    
    ///////////////////////////////////////////////
    // add all tests of CFloatingMeasure_Test
    ///////////////////////////////////////////////
    runner.addTest( new CppUnit::TestCaller<CFloatingMeasure_Test> ( 
                        "FloatingMeasure: operator=",
                        &CFloatingMeasure_Test::OperatorEqual,
                        &FloatingMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CFloatingMeasure_Test> ( 
                        "FloatingMeasure: normlaize",
                        &CFloatingMeasure_Test::Normalize,
                        &FloatingMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CFloatingMeasure_Test> ( 
                        "FloatingMeasure: scale to for temperature",
                        &CFloatingMeasure_Test::ScaleToTemperature,
                        &FloatingMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CFloatingMeasure_Test> ( 
                        "FloatingMeasure: normalize temperature",
                        &CFloatingMeasure_Test::NormalizeTemperature,
                        &FloatingMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CFloatingMeasure_Test> ( 
                        "FloatingMeasure: Simplify",
                        &CFloatingMeasure_Test::Simplify,
                        &FloatingMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CFloatingMeasure_Test> ( 
                        "FloatingMeasure: Valid",
                        &CFloatingMeasure_Test::Valid,
                        &FloatingMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CFloatingMeasure_Test> ( 
                        "FloatingMeasure: ScaleTo",
                        &CFloatingMeasure_Test::ScaleTo,
                        &FloatingMeasureTest
                        )
                  );
    runner.addTest( new CppUnit::TestCaller<CFloatingMeasure_Test> ( 
                        "FloatingMeasure: Precision",
                        &CFloatingMeasure_Test::Precision,
                        &FloatingMeasureTest
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

