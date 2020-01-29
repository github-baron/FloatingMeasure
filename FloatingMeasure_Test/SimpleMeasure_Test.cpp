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
    
    void OperatorEqual()
    {           
        // = operator 
        Measure2.SetByShort("m","A");
        Measure2 = Measure1;
        CPPUNIT_ASSERT_MESSAGE( Measure1.DebugOut() + "\n"+ Measure2.DebugOut() , Measure1.DebugOut() == Measure2.DebugOut()); 
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
