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
            s.dRep = dValue;
            sc.dRep = s.dRep;
            
            sc.intRep++;
            
            ostringstream oss, ossc, osse;
            
            // ostringstream cant handle negative precision
            oss << scientific << setprecision(20) << s.dRep;
            ossc << scientific << setprecision(20) << sc.dRep;
            osse << scientific << setprecision(20) << DoubleMachineEpsilon(dValue);
            
//             CPPUNIT_ASSERT_MESSAGE( "numerical error exceeds expected value (" + to_string(iexp) + ")\ndouble machine epsilon=" + osse.str() + "\nread double = " + oss.str() + "\nread long long = " + to_string(s.intRep) + "\ncorrected integer = " + to_string(sc.intRep)+ "\ncorrected double = " + ossc.str(), DoubleMachineEpsilon(dValue)/dValue < 2.3e-16);
        }
    }
    
    void Utils_DifferenceNthOrder()
    {
        double d1=1e15-1;
        double d2=1e15+1;
        vector<double> vDiff;
        double dDiff;
        double dTolerance;
        
        // expected differences fo  r order 2 --> 6
        vDiff.push_back(4e15);
        vDiff.push_back(6e30);
        vDiff.push_back(8e45);
        vDiff.push_back(10e60);
        vDiff.push_back(12e75);
        
        
        ostringstream oss, ossRes, ossExp;
        
        for(unsigned int uiOrder = 2; uiOrder < 7; uiOrder++)
        {
            // check 2nd Order
            double dDiffCompare = pow(d2,uiOrder) - pow(d1,uiOrder);
            dDiff = vDiff[uiOrder-2];            
            dTolerance = fabs(dDiff-dDiffCompare);
            double dTolCalc =  fabs(dDiff-DifferenceNthOrder(d1,d2,uiOrder)) ;
            oss << uiOrder << ". order difference: " << endl << "expected: " << endl <<  setprecision(20) << dDiff << endl << "but got" << endl << DifferenceNthOrder(d1,d2,uiOrder) << endl <<
            "usual calculation would have received the following: " << endl << dDiffCompare <<  endl <<  "deviation is: " << endl << setprecision(20) << dTolCalc << endl << "comparison: difference from standard calc. to ideal diff is " << endl << dTolerance << endl;
            
            LOGTRACE("Distribution_Test::Utils_DifferenceNthOrder", oss.str());
            
            CPPUNIT_ASSERT_MESSAGE( oss.str(), dTolCalc < dTolerance);
        }
    }
    
    void Utils_TrimLeft()
    {
        string str2Trim = "    3     ";
        string str2Compare = "3     ";
        string strResult = TrimLeft(str2Trim, " ");
        CPPUNIT_ASSERT_MESSAGE( string("str2Trim:\n\"") + (str2Trim) + "\"\nstrResult\"" + (strResult) + "\"", strResult == str2Compare);
    }
        
    void Utils_TrimRight()
    {
        string str2Trim = "    3     ";
        string str2Compare = "    3";
        string strResult = TrimRight(str2Trim, " ");
        CPPUNIT_ASSERT_MESSAGE( string("str2Trim:\n\"") + (str2Trim) + "\"\nstrResult\"" + (strResult) + "\"", strResult == str2Compare);
    }
        
    void Utils_Trim()
    {
        string str2Trim = "    3     ";
        string str2Compare = "3";
        string strResult = Trim(str2Trim, " ");
        CPPUNIT_ASSERT_MESSAGE( string("str2Trim:\n\"") + (str2Trim) + "\"\nstrResult\"" + (strResult) + "\"", strResult == str2Compare);
    }
    
    void Utils_Tokenize()
    {
     
        string str = "1 2 3 4 5 6  7 8 9 10 11   12";
        vector<string> vstr = Tokenize(str, " ");   
    
        CPPUNIT_ASSERT_MESSAGE( string("original string:\n") + str + "\ntokens:\n" + Concat(vstr, "\n"), vstr.size() == 12 );
        for(int i = 1; i<13;i++)        
            CPPUNIT_ASSERT_MESSAGE( string("original string (") + to_string(i) + "):\n" + str + "\ntokens:\n" + Concat(vstr, "\n"), i == atoi(vstr[i-1].c_str()) );
        
        str = "mm/ks";
        vstr = Tokenize(str,"/");
        CPPUNIT_ASSERT_MESSAGE( string("original string:\n") + str + "\ntokens:\n" + Concat(vstr, "\n"), vstr.size() == 2 );
        CPPUNIT_ASSERT_MESSAGE( string("original string:\n") + str + "\ntokens:\n" + Concat(vstr, "\n"), vstr[0] == "mm" && vstr[1] =="ks");
        
        str = "1/s*m";
        vstr = Tokenize(str, "*");
        CPPUNIT_ASSERT_MESSAGE( string("original string:\n") + str + "\ntokens:\n" + Concat(vstr, "\n"), vstr.size() == 2 );
        CPPUNIT_ASSERT_MESSAGE( string("original string:\n") + str + "\ntokens:\n" + Concat(vstr, "\n"), vstr[0] == "1/s" && vstr[1] =="m");
       
    }
    
    void Utils_Parse()
    {
        string str = "101/mV*s";
        size_t pos;
        DF_VALUE_TYPE val = STR2DBL(str,&pos);
        CPPUNIT_ASSERT_MESSAGE( string("value= ") + to_string(val ), val == 101 );
        CPPUNIT_ASSERT_MESSAGE( string("value= ") + to_string(val ), pos == 3 );
        
        // copy substring 
        str = str.substr(pos, str.length()-pos);
        CPPUNIT_ASSERT_MESSAGE( str, str == "/mV*s" );
        
        
        // no check  what happens without number
        str= "km/34023.e-4mV*s";
        try
        {
            val = STR2DBL(str,&pos);
        }
        catch(exception &e)
        {
            pos = 0;
            val = 1;
        }
        CPPUNIT_ASSERT_MESSAGE( string("value= ") + to_string(val ), val == 1 );
        CPPUNIT_ASSERT_MESSAGE( string("value= ") + to_string(val ), pos == 0 );
        
        
        // no check  what happens without number
        str= "/mV*s";
        try
        {
            val = STR2DBL(str,&pos);
        }
        catch(exception &e)
        {
            pos = 0;
            val = 1;
        }
        CPPUNIT_ASSERT_MESSAGE( string("value= ") + to_string(val ), val == 1 );
        CPPUNIT_ASSERT_MESSAGE( string("value= ") + to_string(val ), pos == 0 );
        str = str.substr(pos, str.length()-pos);
        CPPUNIT_ASSERT_MESSAGE( str, str == "/mV*s" );
        
    }
    
};
