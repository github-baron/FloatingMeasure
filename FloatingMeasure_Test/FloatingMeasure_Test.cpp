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

#include "../FloatingMeasure/Utils/Utils.h"
#include "../FloatingMeasure/Measure/ComplexMeasureMacros.h"
#include "../FloatingMeasure/FloatingMeasure/FloatingMeasure.h"

class CFloatingMeasure_Test : public CppUnit::TestFixture  {

private:
    CFloatingMeasure cfTest1, cfTest2, cfTest3;
    
public:
    void setUp()
    {
        
    }

    void tearDown() 
    {
    }
    void OperatorEqual()
    {
        cfTest1 = 10*mC/kK;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 10);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.Measure().DebugOut(), cfTest1.Measure() == mC/kK);
    }

    void Normalize()
    {
        cfTest1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 10./1000./1000.);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == C/K);

    }
    
    void ScaleToTemperature()
    {
        cfTest1 = 185*K;
        cfTest1.ScaleTo(C);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 185.-273.15);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == C);
        cfTest1.ScaleTo(F);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 9./5.*(153.-5./9.*273.15));
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == F);
        cfTest1.ScaleTo(K);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 185);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == K);
        
        
    }
     void FloatingMeasureTest()
    {
        CFloatingMeasure cfTest1;
        // scale to temperature
        cfTest1 = 10*mC;
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 10);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == mC );

        cfTest1 = 10*mC;
        cfTest1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 273.15+0.01);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == K );
         
        
        cfTest1 = 10*mC;
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
    
 };
