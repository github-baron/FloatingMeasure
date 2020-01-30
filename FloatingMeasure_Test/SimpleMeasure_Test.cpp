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

#include "Utils/Utils.h"
#include "Measure/SimpleMeasure.h"

class CSimpleMeasure_Test : public CppUnit::TestFixture  {

private:
    CSimpleMeasure Measure1, Measure2, Measure4;
    
public:
    void setUp()
    {
    }

    void tearDown() 
    {
    }

    void CopyConstructor()
    {

        Measure1.SetByShort("f","V");
        
        // copy constructor
        CSimpleMeasure Measure4( Measure1);
        CPPUNIT_ASSERT_MESSAGE( Measure4.DebugOut() + "\n"+ Measure1.DebugOut() , Measure4.DebugOut() == Measure1.DebugOut());

    }
    
    void SetByShortOperatorAssignAndqEualVoltage()
    {           
        // = operator 
        Measure2.SetByShort( "f","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "fV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "p","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "pV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "n","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "nV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( mu ,"V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==mu+"V"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "m","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "mV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "c","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "cV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "d","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "dV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort(  "","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==   "V"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort("da","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() == "daV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "H","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "HV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "k","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "kV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "M","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "MV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "G","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "GV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "T","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "TV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "P","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "PV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "E","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "EV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Z","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "ZV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Y","V");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "YV"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
    }
    
    void SetByShortOperatorAssignAndqEualCurrent()
    {           
        // = operator 
        Measure2.SetByShort( "f","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "fA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "p","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "pA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "n","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "nA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( mu ,"A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==mu+"A"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "m","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "mA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "c","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "cA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "d","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "dA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort(  "","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==   "A"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort("da","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() == "daA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "H","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "HA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "k","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "kA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "M","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "MA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "G","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "GA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "T","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "TA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "P","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "PA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "E","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "EA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Z","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "ZA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Y","A");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "YA"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
    }
    
    
    void SetByShortOperatorAssignAndqEualFrequency()
    {           
        // = operator 
        Measure2.SetByShort( "f","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "fHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "p","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "pHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "n","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "nHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( mu ,"Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==mu+"Hz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "m","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "mHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "c","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "cHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "d","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "dHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort(  "","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==   "Hz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort("da","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() == "daHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "H","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "HHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "k","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "kHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "M","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "MHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "G","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "GHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "T","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "THz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "P","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "PHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "E","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "EHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Z","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "ZHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Y","Hz");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "YHz"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
    }
        
    void SetByShortOperatorAssignAndqEualSeconds()
    {  
    
        Measure2.SetByShort( "f","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "fs"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "p","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "ps"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "n","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "ns"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( mu ,"s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==mu+"s"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "m","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "ms"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "c","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "cs"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "d","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "ds"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort(  "","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==   "s"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort("da","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() == "das"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "H","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Hs"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "k","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "ks"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "M","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Ms"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "G","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Gs"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "T","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Ts"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "P","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Ps"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "E","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Es"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Z","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Zs"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Y","s");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Ys"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
    }
    
    void SetByShortOperatorAssignAndqEualResistor()
    {           
        // = operator 
        Measure2.SetByShort( "f",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "f"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "p",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "p"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "n",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "n"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( mu ,Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==mu+""+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "m",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "m"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "c",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "c"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "d",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "d"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort(  "",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==   ""+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort("da",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() == "da"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "H",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "H"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "k",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "k"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "M",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "M"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "G",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "G"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "T",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "T"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "P",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "P"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "E",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "E"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Z",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Z"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Y",Omega);CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Y"+Omega); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
    }

    void SetByShortOperatorAssignAndqEualMeter()
    {  
    
        Measure2.SetByShort( "f","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "fm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "p","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "pm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "n","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "nm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( mu ,"m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==mu+"m"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "m","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "mm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "c","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "cm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "d","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "dm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort(  "","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==   "m"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort("da","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() == "dam"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "H","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Hm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "k","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "km"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "M","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Mm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "G","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Gm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "T","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Tm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "P","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Pm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "E","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Em"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Z","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Zm"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Y","m");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Ym"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
    }

    void SetByShortOperatorAssignAndqEualDegKelvin()
    {  
    
        Measure2.SetByShort( "f","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "f°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "p","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "p°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "n","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "n°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( mu ,"°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==mu+"°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "m","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "m°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "c","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "c°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "d","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "d°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort(  "","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==   "°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort("da","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() == "da°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "H","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "H°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "k","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "k°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "M","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "M°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "G","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "G°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "T","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "T°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "P","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "P°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "E","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "E°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Z","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Z°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Y","°K");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Y°K"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
    }

    void SetByShortOperatorAssignAndqEualDegFahrenheit()
    {  
    
        Measure2.SetByShort( "f","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "f°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "p","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "p°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "n","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "n°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( mu ,"°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==mu+"°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "m","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "m°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "c","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "c°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "d","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "d°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort(  "","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==   "°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort("da","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() == "da°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "H","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "H°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "k","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "k°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "M","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "M°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "G","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "G°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "T","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "T°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "P","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "P°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "E","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "E°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Z","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Z°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Y","°F");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Y°F"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
    }

    void SetByShortOperatorAssignAndqEualDegCelsius()
    {  
    
        Measure2.SetByShort( "f","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "f°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "p","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "p°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "n","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "n°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( mu ,"°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==mu+"°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "m","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "m°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "c","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "c°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "d","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "d°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort(  "","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==   "°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort("da","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() == "da°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "H","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "H°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "k","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "k°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "M","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "M°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "G","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "G°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "T","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "T°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "P","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "P°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "E","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "E°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Z","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Z°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
        Measure2.SetByShort( "Y","°C");CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() , Measure2.Short() ==  "Y°C"); Measure2 = Measure1; CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
    }
    
    void SetByIDOther()
    {       
        // SetByID
        Measure2.SetByID( Measure1.PreID(), Measure1.BaseID());
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut());
    }
    
    void SetByShortVoltage()
    {
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

    }

    void SetByShortResistor()
    {        
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
    }
    
    void SetByShortTemperature()
    {      
        Measure1.SetByShort("f","°F");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 5./9.*0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "f°F");
        
        Measure1.SetByShort("","°F");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 5./9.);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIOffset() == 32-5./9.*273.15);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "°F");
        
        Measure1.SetByShort("m","°F");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 5./9.*0.001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIOffset() == (32-5./9.*273.15));
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "m°F");
        
        Measure1.SetByShort("","°C");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1.);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIOffset() == 273.15);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "°C");
        
        Measure1.SetByShort("k","°C");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 1000.);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIOffset() == (273.15));
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "k°C");
 
    }
    void SetByShortTime()
    {
        Measure1.SetByShort("f","h");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 3600.*0.000000000000001);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "fh");
                
        Measure1.SetByShort("k","d");
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.SIFactor() == 3600.*24.*1000);
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut()  , Measure1.Short() == "kd");
        
    }
     
 };
