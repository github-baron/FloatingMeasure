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
#include <math.h>

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
     
        // check for -1
        dfFac2 = -1;
        CPPUNIT_ASSERT_MESSAGE( dfFac2.Print() , dfFac2 == -1);
        CPPUNIT_ASSERT_MESSAGE( dfFac2.Print() , dfFac2.RawError() == DoubleMachineEpsilon(-1));
        
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
    
    void FunctionLog()
    {
        // check function log
        int nMaxLogArgs = 100;
        double dLogArgStep = 1.23423;    // step above 1
        int nMaxBase = 1000;
        double dBaseStep = 10;
        for(int ibase = 0; ibase < nMaxBase; ibase++)
        for(int iarg = 0; iarg < nMaxLogArgs; iarg++)
        {   
            double dBase = ((ibase < (nMaxBase / 2 - 1)) ? 2./(double)nMaxBase :  (1 + dBaseStep)) * (ibase+1);
            double dLogArg = ((iarg < (nMaxLogArgs / 2 -1)) ?  (2./(double)nMaxLogArgs) : (1.+ dLogArgStep) ) * (iarg + 1);
            CDigFloat dfExpected = log(dLogArg)/log(dBase);
            dfExpected.Precision(25);
            
            dfFac1 = log(dLogArg, dBase);
            CPPUNIT_ASSERT_MESSAGE( "Logarg = " + to_string(dLogArg) + "\nbase:" + to_string(dBase) + "\ncalculated : " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), fabs(dfFac1.RawValue() - dfExpected.RawValue()) <= dfFac1.RawError());
            
            CPPUNIT_ASSERT_MESSAGE("Logarg = " + to_string(dLogArg) + "\nbase:" + to_string(dBase) + "\nrelation Value / error:" + CDigFloat(fabs(dfFac1.RawError()/ dfFac1.RawValue())).DebugOut() + "\nlog result: " + dfFac1.DebugOut(), fabs(dfFac1.RawError()/dfFac1.RawValue()) <= 0.00001);
        
        }
    }
    
    
    void FunctionPow()
    {
        // check function pow:
        // iterating for total exponent from -308 to 308
        int nTotExpStep = 10;
        int nMaxExpArgs = 10;
        double dExpArgStep = 0.1;    // step above 1
        int nMaxBase = 10;
        double dBaseStep = 0.1;
        
        for(int ibase = 0; ibase < nMaxBase; ibase++)
        for(int iarg = (int)(-307/dExpArgStep); iarg < (int)(+307/dExpArgStep); iarg++)
        {   
            
            
            // now calculate the base and exponential part  
            double dBase = (dBaseStep)* ((double)(ibase)+1.);
            double dExpArg = (dExpArgStep)* (iarg);
            
            
            // take care to be within the exponential range of -308 and +308
            double dTotalExp = dExpArg*(log(dBase)/log(10));
            if(dTotalExp < -307 || dTotalExp > 307 ){
            
                cout << "FunctionPow-Test ("<< ibase << ", " << iarg << "): exceeded exponent with " << setprecision(30) << dExpArg*log(dBase) << " (base= "  <<  dBase << ", exp = " << dExpArg << ")" <<  endl;
                continue;
            }
            
            CDigFloat dfExpected = pow(dBase, dExpArg);
            dfExpected.Precision(25);
            
            dfFac1 = pow(dBase,dExpArg);
            // check for: "error must not be zero"
            CPPUNIT_ASSERT_MESSAGE( "Exp.arg = " + to_string(dExpArg) + "\nbase:" + to_string(dBase) + "\ncalculated : " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), dfFac1.RawError() > 0);
            // check for : "deviation must be less than error"
            CPPUNIT_ASSERT_MESSAGE( "Exp.arg = " + to_string(dExpArg) + "\nbase:" + to_string(dBase) + "\ncalculated : " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), fabs(dfFac1.RawValue() - dfExpected.RawValue()) <= dfFac1.RawError());
            
            // check for: "error must be less than 10 ppm"
            CPPUNIT_ASSERT_MESSAGE("Exp.arg = " + to_string(dExpArg) + "\nbase:" + to_string(dBase)  + "\ncalculated : " + dfFac1.DebugOut() + "\nrelation Value / error:" + CDigFloat(fabs(dfFac1.RawError()/ dfFac1.RawValue())).DebugOut() + "\nlog result: " + dfFac1.DebugOut(), fabs(dfFac1.RawError()/dfFac1.RawValue()) <= 0.00001);
        
        }
    }
    
    void ErrorPropagation()
    {
        //check operator /=
        //this is pretty constant and finishes at 615 times : min double: 1e-308 max : 1e+308
        //dfFac1 = 1e+307;
        int nExp = 308;
        dfFac1 = pow(10,nExp);
        dfFac2 = dfFac1/10;
        dfFac3 = dfFac1 / dfFac2;
        dfFac1.Precision(10);
        dfFac2.Precision(10);
        dfFac3.Precision(10);
        for(int iexp = 0; iexp < 2*nExp; iexp++)
        {   
            CPPUNIT_ASSERT_MESSAGE( "exp = " + to_string(iexp) + "\n" + dfFac1.DebugOut() + "\n" + dfFac2.DebugOut()+ "\n" + (dfFac1/dfFac2).DebugOut(),
                                        (dfFac1/dfFac2) ==10 &&(dfFac1/dfFac2 ).Error() < 0.00004);
            dfFac1 /=10;
            dfFac2 /=10;
            
            
        }
        
        // check operator *=
        //  615 times (double value ranges from 1e-308 to 1e+308 
        for(int iexp = 0; iexp < nExp; iexp++)
        {   
            CPPUNIT_ASSERT_MESSAGE( "exp = " + to_string(iexp) + "\n" + dfFac1.Print() + "\n" + dfFac2.Print()+ "\n" + (dfFac1/dfFac2).Print(),
                                        (dfFac1/dfFac2) == 10 &&
                                  (dfFac1/dfFac2 ).Error() < 0.004);
            dfFac1 *=10;
            dfFac2 *=10;
            
        }
        
        // check for pow / log 
        double dBase = M_PI;
        double dLogArg = 1.23435e+10;
        CDigFloat dfOldError;
        for(int iexp = 0; iexp < 1000; iexp++)
        {   
            // do log calculations
            dfFac1 = log(dLogArg,dBase);
            CDigFloat dfExpected = log(dLogArg) / log(dBase);
            
            // remember old error
            dfOldError = dfFac1.RawError();
            
            CPPUNIT_ASSERT_MESSAGE( "Logarg = " + to_string(dLogArg) + "\nbase:" + to_string(dBase) + "\ncalculated : " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), fabs(dfFac1.RawValue() - dfExpected.RawValue()) <= dfFac1.RawError());
            CPPUNIT_ASSERT_MESSAGE("Logarg = " + to_string(dLogArg) + "\nbase:" + to_string(dBase) + "\nrelation Value / error:" + CDigFloat(fabs(dfFac1.RawError()/ dfFac1.RawValue())).DebugOut() + "\nlog result: " + dfFac1.DebugOut(), fabs(dfFac1.RawError()/dfFac1.RawValue()) <= 0.00001);

            // do pow calculations
            dfExpected = pow(dBase, dfFac1.RawValue());
            dfFac1 = pow(dBase, dfFac1);
            
            // check for: "error must not be zero"
            CPPUNIT_ASSERT_MESSAGE(  "\nbase:" + to_string(dBase) + "\ncalculated : " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), dfFac1.RawError() > 0);
            // check for : "deviation must be less than error"
            CPPUNIT_ASSERT_MESSAGE("\nbase:" + to_string(dBase) + "\ncalculated : " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), fabs(dfFac1.RawValue() - dfExpected.RawValue()) <= dfFac1.RawError());

            // check for : "old error must be less than actual error"
            CPPUNIT_ASSERT_MESSAGE("\nbase:" + to_string(dBase) + "\nold Error: " + dfOldError.RawPrint(30) + "\nnew error: " + dfFac1.RawPrint(30), dfOldError <= dfFac1.RawError());
  
            // check for: "error must be less than 10 ppm"
            CPPUNIT_ASSERT_MESSAGE("\nbase:" + to_string(dBase)  + "\ncalculated : " + dfFac1.DebugOut() + "\nrelation Value / error:" + CDigFloat(fabs(dfFac1.RawError()/ dfFac1.RawValue())).DebugOut() + "\nlog result: " + dfFac1.DebugOut(), fabs(dfFac1.RawError()/dfFac1.RawValue()) <= 0.00001);
        }
        
    }
    
    void ErrorPropagation_sqrt()
    {
        // init first error with 0
        CDigFloat dfOldError ;
        CDigFloat dfNewError;
        
 
        dfFac1 = 1e+308;
        CDigFloat dfExpected = sqrt(dfFac1.RawValue());
        dfOldError = dfExpected.RawError() / dfExpected.RawValue();
        for(int iexp = 0; iexp < 50; iexp++)
        {   
            
            // calculate the expected value by setting by double calculation
            dfExpected = sqrt(dfFac1.RawValue());
            
            // do sqrt calculations
            CDigFloat dfTemp = dfFac1;
            dfFac1 = sqrt(dfTemp);
            
            // set the new relative error as DigFloat : use printing function
            // calculation of relative error is relevant because in case the value is diminished by the 
            // function sqrt (e.g. starting value > 1) then the error is diminished, too. But the relative
            // error should grow
            dfNewError = dfFac1.RawError() / dfFac1.RawValue();
            
            // check deviation of result and expected being less than the calculated error
            CPPUNIT_ASSERT_MESSAGE( "calculation(" + to_string(iexp) + "): " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), fabs(dfFac1.RawValue() - dfExpected.RawValue()) <= dfFac1.RawError());
            
            // check the relation of value and error being less than 0.00001
            CPPUNIT_ASSERT_MESSAGE("calculation(" + to_string(iexp) + "): " +"\nrelation Value / error:" + CDigFloat(fabs(dfFac1.RawError()/ dfFac1.RawValue())).DebugOut() + "\nlog result: " + dfFac1.DebugOut(), fabs(dfFac1.RawError()/dfFac1.RawValue()) <= 0.00001);
            
            // check for: "error must not be zero"
            CPPUNIT_ASSERT_MESSAGE(  "calculation(" + to_string(iexp) + "): " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), dfFac1.RawError() > 0);
            
            // check for : "deviation must be less than error"
            CPPUNIT_ASSERT_MESSAGE("calculation(" + to_string(iexp) + "): " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), fabs(dfFac1.RawValue() - dfExpected.RawValue()) <= dfFac1.RawError());
 
            // check for: "error must be less than 10 ppm"
            CPPUNIT_ASSERT_MESSAGE("calculation(" + to_string(iexp) + "): " + dfFac1.DebugOut() + "\nrelation Value / error:" + CDigFloat(fabs(dfFac1.RawError()/ dfFac1.RawValue())).DebugOut() + "\nlog result: " + dfFac1.DebugOut(), fabs(dfFac1.RawError()/dfFac1.RawValue()) <= 2.3e-16);
                        
            // remember old relative error
            dfOldError = dfNewError;
        }
        
        // now ascending from 1e-308
        
        dfFac1 = 1e-307;
        dfExpected = sqrt(dfFac1.RawValue());
        dfOldError = dfExpected.RawError() / dfExpected.RawValue();
        for(int iexp = 0; iexp < 50; iexp++)
        {   
            
            // calculate the expected value by setting by double calculation
            dfExpected = sqrt(dfFac1.RawValue());
            
            // do sqrt calculations
            CDigFloat dfTemp = dfFac1;
            dfFac1 = sqrt(dfTemp);
            
            // set the new relative error as DigFloat : use printing function
            // calculation of relative error is relevant because in case the value is diminished by the 
            // function sqrt (e.g. starting value > 1) then the error is diminished, too. But the relative
            // error should grow
            dfNewError = dfFac1.RawError() / dfFac1.RawValue();
            
            // check deviation of result and expected being less than the calculated error
            CPPUNIT_ASSERT_MESSAGE( "calculation(" + to_string(iexp) + "): " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), fabs(dfFac1.RawValue() - dfExpected.RawValue()) <= dfFac1.RawError());
            
            // check the relation of value and error being less than 0.00001
            CPPUNIT_ASSERT_MESSAGE("calculation(" + to_string(iexp) + "): " +"\nrelation Value / error:" + CDigFloat(fabs(dfFac1.RawError()/ dfFac1.RawValue())).DebugOut() + "\nlog result: " + dfFac1.DebugOut(), fabs(dfFac1.RawError()/dfFac1.RawValue()) <= 0.00001);
            
            // check for: "error must not be zero"
            CPPUNIT_ASSERT_MESSAGE(  "calculation(" + to_string(iexp) + "): " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), dfFac1.RawError() > 0);
            
            // check for : "deviation must be less than error"
            CPPUNIT_ASSERT_MESSAGE("calculation(" + to_string(iexp) + "): " + dfFac1.DebugOut() + "\nexpected: " + dfExpected.Print(), fabs(dfFac1.RawValue() - dfExpected.RawValue()) <= dfFac1.RawError());
 
            // check for: "error must be less than 10 ppm"
            CPPUNIT_ASSERT_MESSAGE("calculation(" + to_string(iexp) + "): " + dfFac1.DebugOut() + "\nrelation Value / error:" + CDigFloat(fabs(dfFac1.RawError()/ dfFac1.RawValue())).DebugOut() + "\nlog result: " + dfFac1.DebugOut(), fabs(dfFac1.RawError()/dfFac1.RawValue()) <= 2.3e-16);
                        
            // remember old relative error
            dfOldError = dfNewError;
        }
        
    }
    
 };
