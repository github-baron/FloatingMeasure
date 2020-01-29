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

class CBaseMeasure_Test : public CppUnit::TestFixture  {

private:
    // helping variable 
    eBaseMeasure ActBM, SIBM ;

public:
    void setUp()
    {
    }

    void tearDown() 
    {
    }

    void SIReference()
    {
        
        
        // reference to SI for all
        for(int i = 0; i< bmLast; i++)
        {
            // check SI reference being consistent
            ActBM = (eBaseMeasure )(i);
            SIBM = BASE->SIID(ActBM);
            CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(SIBM) + "\n" + BASE->DebugOut(BASE->SIID(ActBM )),
                                    BASE->DebugOut(SIBM ) == BASE->DebugOut(BASE->SIID(ActBM )) );
        }
        
    }
    
    void UniqueShortLabel()
    {
        // reference to SI for all
        for(int i = 0; i< bmLast; i++)
        {
            ActBM = (eBaseMeasure )(i);
            // check for unique namings short and long
            for( int j = i+1; j < bmLast; j++)
            {
                // set base measure to compare with
                eBaseMeasure OtherActBM = (eBaseMeasure )(j);
                
                // check for unique short labels
                CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + "\n" + BASE->DebugOut(OtherActBM), BASE->Short(ActBM) != BASE->Short(OtherActBM) );
                
            }
                
        }
        
        
    }
    
    void UniqueLongLabel()
    {
        // reference to SI for all
        for(int i = 0; i< bmLast; i++)
        {
            ActBM = (eBaseMeasure )(i);
            // check for unique namings short and long
            for( int j = i+1; j < bmLast; j++)
            {
                // set base measure to compare with
                eBaseMeasure OtherActBM = (eBaseMeasure )(j);
                
                // check for unique long labels
                CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + "\n" + BASE->DebugOut(OtherActBM), 
                                        BASE->Long(ActBM) != BASE->Long(OtherActBM) );
                
            }
                
        }      
        
    }
    
    void UniqueSIFactor()
    {
        // reference to SI for all
        for(int i = 0; i< bmLast; i++)
        {
            ActBM = (eBaseMeasure )(i);
            // check for unique namings short and long
            for( int j = i+1; j < bmLast; j++)
            {
                // set base measure to compare with
                eBaseMeasure OtherActBM = (eBaseMeasure )(j);
                
                //check of unique SI recalculation
                if( BASE->SIID(ActBM) == BASE->SIID(OtherActBM) )
                    CPPUNIT_ASSERT_MESSAGE( BASE->DebugOut(ActBM) + "\n" + BASE->DebugOut(OtherActBM), 
                                            BASE->Factor(ActBM) != BASE->Factor(OtherActBM) || 
                                            BASE->Offset(ActBM) != BASE->Offset(OtherActBM));
        
                
            }
                
        }      
        
    }
    
 };
