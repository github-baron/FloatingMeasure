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
        LOGTRACE("ErrorLogger","OperatorEqual");
        
        
        // operator == ...
        cfTest1 = 0.00000001*uV;
        cfTest2 = 0.01*pV;
        cfTest1.PrecisionActive(false);
        cfTest2.PrecisionActive(false);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut() + "\n" + cfTest2.DebugOut() + "\n" +
        cfTest1.PrintShort() + "\n" + cfTest2.PrintShort(), cfTest1 == cfTest2 );
    
    }

    void Normalize()
    {
        cfTest1 = 10*mC/kK;
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
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 9./5.*(185.-273.15) + 32);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == F);
        cfTest1.ScaleTo(K);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 185);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == K);
        
        
    }
     void NormalizeTemperature()
    {
        // °F --> °K
        cfTest1 = 10*kF;        
        cfTest1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 10*1000*5/9.+273.15-5./9*32.);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == K );

        // °C --> °K
        cfTest1 = 10*mC;
        cfTest1.Normalize();
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 273.15+0.01);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == K );
         
    }
    
    void Simplify()
    {
        cfTest1 = 23403*uK/cC*V*uA/K*kF*MC;
        cfTest1.Simplify();
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 23403*0.000001*100*1000000 );
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut() + "\n" + cfTest1.PrintShort(), cfTest1.Measure() == V*uA*kF );
    }
    
    void ScaleTo()
    {
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
        
        cfTest1 = 10*V;
        cfTest2 = 1000*h;
        cfTest3 = 0.134342*uA;
        cfTest3 *= cfTest2*cfTest1;
        cfTest3.ScaleTo(V*A*h);
        CPPUNIT_ASSERT_MESSAGE( cfTest3.DebugOut(), cfTest3.Floating() == 0.00134342 );
        CPPUNIT_ASSERT_MESSAGE( cfTest3.DebugOut(), cfTest3.Measure() == V*A*h );
    }
    
    void Precision()
    {
      
        // operator +=
        CFloatingMeasure cfTest2;
        cfTest2 = 220*V;
        cfTest1 = 10*mV;
        cfTest1.ScaleTo(kV);
        CFloatingMeasure cfTest3;
        cfTest1 += cfTest2;
        cfTest1.Precision(1*mV);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Floating() == 0.220010 );
        CPPUNIT_ASSERT_MESSAGE( cfTest1.DebugOut(), cfTest1.Measure() == kV );
        
        // check  for different precision : [0.1,1[ --> nDigits = 1        
        cfTest1.Precision(0.99*mV);
        CPPUNIT_ASSERT_MESSAGE( cfTest1.PrintShort(), cfTest1.PrintShort() == "0.2200100*kV" );
        
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
        
        // now check the limits:
        // 0.9999 dV --> 0.1 dV digits
        // 10 dV --> 10 dV digits
        cfTest2.Precision(0.999999999*dV);
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut(), cfTest2.Floating() == 312.34319977999 );
        cfTest2.Precision(1*dV);
        CPPUNIT_ASSERT_MESSAGE( cfTest2.DebugOut(), cfTest2.Floating() == 312.34319978000 );
        
    }
    void Valid()
    {
        
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
    }
    
    void FloatingMeasure_Parse()
    {
        CFloatingMeasure fm1;
        fm1.Parse("10*m/s");
        CPPUNIT_ASSERT_MESSAGE( fm1.DebugOut(), fm1 == 10*m/s);
        fm1.Parse("m/s*10");
        CPPUNIT_ASSERT_MESSAGE( fm1.DebugOut(), fm1 == 10*m/s);
        fm1.Parse("10*m/s/1/s");
        CPPUNIT_ASSERT_MESSAGE( fm1.DebugOut(), fm1 == 10*m/s/s);
    }
    
    void Velocity()
    {
        
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
          
        
    }
    
 };
