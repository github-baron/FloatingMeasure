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

class CUtils_Test : public CppUnit::TestFixture  {

private:
    
public:
    void setUp()
    {
        
    }

    void tearDown() 
    {
    }
    
   void Utils_DoubleMachineEpsilon()
    {
        
        dbl_64 s, sc;
        
        for( int iexp = -307; iexp < 308 ; iexp++)
        {
            double dValue = pow(10,iexp); 
            s.d64 = dValue;
            sc.d64 = s.d64;
            
            sc.i64++;
            
            ostringstream oss, ossc, osse;
            
            // ostringstream cant handle negative precision
            oss << scientific << setprecision(20) << s.d64;
            ossc << scientific << setprecision(20) << sc.d64;
            osse << scientific << setprecision(20) << DoubleMachineEpsilon(dValue);
            
            CPPUNIT_ASSERT_MESSAGE( "numerical error exceeds expected value (" + to_string(iexp) + ")\ndouble machine epsilon=" + osse.str() + "\nread double = " + oss.str() + "\nread long long = " + to_string(s.i64) + "\ncorrected integer = " + to_string(sc.i64)+ "\ncorrected double = " + ossc.str(), DoubleMachineEpsilon(dValue)/dValue < 2.3e-16);
        }
    }
};
