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
#include "../FloatingMeasure/DigFloat/DigFloat.h"

class CDigFloat_Test : public CppUnit::TestFixture  {

private:
    CDigFloat dfFac1, dfFac3, dfFac2;
    
public:
    void setUp()
    {
        
    }

    void tearDown() 
    {
    }
   void Construction()
    {
        CDigFloat dfFac1(1);
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut(), dfFac1.RawValue() == 1 && dfFac1.RawError() == DoubleMachineEpsilon(1) );
        
    }
   void Precision()
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
        dfFac2= CDigFloat(0.99988);
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
    }
    
    void Valid()
    {
        // ::Valid
        dfFac1 = dfFac2;
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut() , dfFac1.Valid());
        dfFac1 = myNAN;
        CPPUNIT_ASSERT_MESSAGE( dfFac1.DebugOut() , !dfFac1.Valid());
    }
    
    void Operators()
    {
        // operator = double
        dfFac2 = 0.1;
        CPPUNIT_ASSERT_MESSAGE( dfFac2.Print() , dfFac2 == 0.1);
        CPPUNIT_ASSERT_MESSAGE( dfFac2.Print() , dfFac2.RawError() == DoubleMachineEpsilon(0.1));
        
        CDigFloat dfFac3(10);
        CPPUNIT_ASSERT_MESSAGE( dfFac3.Print() , dfFac3 == 10);
        CPPUNIT_ASSERT_MESSAGE( dfFac3.Print() , dfFac3.RawError() == DoubleMachineEpsilon(10));
        
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
    }
    
    void ErrorPropagation()
    {
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
                                  (dfFac1/dfFac2 ).Error() < 0.004);
            dfFac1 *=10;
            dfFac2 *=10;
            
        }
        
        // check function log
        // this is pretty constant and finishes at 307 times 
        for(int iexp = 1; iexp < 100; iexp++)
        {   
            double dBase = 1.1;
            dfFac1 = powl(dBase,iexp);

            dfFac1 = log(dfFac1, dBase);
            CPPUNIT_ASSERT_MESSAGE( "exponent = " + to_string(iexp) + "\ndeviation:" + CDigFloat(fabs(dfFac1.RawValue() - (double)iexp)).DebugOut() + "\nfrom raw value : " + to_string(dfFac1.RawValue()) + "\nand\nexponent: " + to_string((double)iexp )+ "\nlog result: " + dfFac1.DebugOut() , fabs(dfFac1.RawValue() - (double)iexp) <= dfFac1.RawError());
            CPPUNIT_ASSERT_MESSAGE( "exponent = " + to_string(iexp) + "\nrelation Value / error:" + CDigFloat(fabs(dfFac1.RawError()/dfFac1.RawValue())).DebugOut() + "\nlog result: " + dfFac1.DebugOut(), fabs(dfFac1.RawError()/dfFac1.RawValue()) <= 0.00001);
        
        }
    }
     
 };
