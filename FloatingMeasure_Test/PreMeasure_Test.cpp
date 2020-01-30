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
#include "../FloatingMeasure/Measure/PreMeasure.h"
#include "../FloatingMeasure/Measure/BaseMeasure.h"

class CPreMeasure_Test : public CppUnit::TestFixture  {

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

    void CheckFactors()
    {
        // check factors
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmFemto) , PRE->Factor(pmFemto)== 0.000000000000001 )        ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPiko)  , PRE->Factor(pmPiko) == 0.000000000001 )           ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmNano)  , PRE->Factor(pmNano) == 0.000000001 )              ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMicro) , PRE->Factor(pmMicro)== 0.000001 )                 ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMilli) , PRE->Factor(pmMilli)== 0.001 )                    ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmCenti) , PRE->Factor(pmCenti)== 0.01 )                     ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeci)  , PRE->Factor(pmDeci) == 0.1 )                      ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmIdent) , PRE->Factor(pmIdent)== 1.0 )                      ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeca)  , PRE->Factor(pmDeca) == 10.)                        ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmHecto) , PRE->Factor(pmHecto)== 100.)                       ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmKilo)  , PRE->Factor(pmKilo) == 1000.)                      ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMega)  , PRE->Factor(pmMega) == 1000000.)                   ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmGiga)  , PRE->Factor(pmGiga) == 1000000000.)                ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmTera)  , PRE->Factor(pmTera) == 1000000000000.)             ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPeta)  , PRE->Factor(pmPeta) == 1000000000000000.)          ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmExa)   , PRE->Factor(pmExa)  == 1000000000000000000.)       ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmZetta) , PRE->Factor(pmZetta)== 1000000000000000000000.)    ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmYotta) , PRE->Factor(pmYotta)== 1000000000000000000000000.) ;
    }
    
    void CheckExponents()
    {          
        // simply check expected exponents
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmFemto) + " : " + to_string(PRE->Exp10(pmFemto))  , PRE->Exp10(pmFemto)== -15) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPiko)  + " : " + to_string(PRE->Exp10(pmPiko) )  , PRE->Exp10(pmPiko) == -12) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmNano)  + " : " + to_string(PRE->Exp10(pmNano) )  , PRE->Exp10(pmNano) == -9 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMicro) + " : " + to_string(PRE->Exp10(pmMicro))  , PRE->Exp10(pmMicro)== -6 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMilli) + " : " + to_string(PRE->Exp10(pmMilli))  , PRE->Exp10(pmMilli)== -3 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmCenti) + " : " + to_string(PRE->Exp10(pmCenti))  , PRE->Exp10(pmCenti)== -2 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeci)  + " : " + to_string(PRE->Exp10(pmDeci) )  , PRE->Exp10(pmDeci) == -1 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmIdent) + " : " + to_string(PRE->Exp10(pmIdent))  , PRE->Exp10(pmIdent)==  0 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmDeca)  + " : " + to_string(PRE->Exp10(pmDeca) )  , PRE->Exp10(pmDeca) == +1 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmHecto) + " : " + to_string(PRE->Exp10(pmHecto))  , PRE->Exp10(pmHecto)== +2 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmKilo)  + " : " + to_string(PRE->Exp10(pmKilo) )  , PRE->Exp10(pmKilo) == +3 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmMega)  + " : " + to_string(PRE->Exp10(pmMega) )  , PRE->Exp10(pmMega) == +6 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmGiga)  + " : " + to_string(PRE->Exp10(pmGiga) )  , PRE->Exp10(pmGiga) == +9 ) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmTera)  + " : " + to_string(PRE->Exp10(pmTera) )  , PRE->Exp10(pmTera) == +12) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmPeta)  + " : " + to_string(PRE->Exp10(pmPeta) )  , PRE->Exp10(pmPeta) == +15) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmExa)   + " : " + to_string(PRE->Exp10(pmExa)  )  , PRE->Exp10(pmExa)  == +18) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmZetta) + " : " + to_string(PRE->Exp10(pmZetta))  , PRE->Exp10(pmZetta)== +21) ;
        CPPUNIT_ASSERT_MESSAGE( PRE->Short(pmYotta) + " : " + to_string(PRE->Exp10(pmYotta))  , PRE->Exp10(pmYotta)== +24) ;
    }
    
    void CheckGetIDByFactor()
    {
        // getting PreMeasure ID by factor                                  
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000000000000001 )) + "' : " + to_string(PRE->GetIDByFactor(0.000000000000001 ) )  , PRE->GetIDByFactor(0.000000000000001 ) == (pmFemto));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000000000001 )   ) + "' : " + to_string(PRE->GetIDByFactor(0.000000000001 )    )  , PRE->GetIDByFactor(0.000000000001 )    == (pmPiko) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000000001 )      ) + "' : " + to_string(PRE->GetIDByFactor(0.000000001 )       )  , PRE->GetIDByFactor(0.000000001 )       == (pmNano) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.000001 )         ) + "' : " + to_string(PRE->GetIDByFactor(0.000001 )          )  , PRE->GetIDByFactor(0.000001 )          == (pmMicro));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.001 )            ) + "' : " + to_string(PRE->GetIDByFactor(0.001 )             )  , PRE->GetIDByFactor(0.001 )             == (pmMilli));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.01 )             ) + "' : " + to_string(PRE->GetIDByFactor(0.01 )              )  , PRE->GetIDByFactor(0.01 )              == (pmCenti));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(0.1 )              ) + "' : " + to_string(PRE->GetIDByFactor(0.1 )               )  , PRE->GetIDByFactor(0.1 )               == (pmDeci) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1.0 )              ) + "' : " + to_string(PRE->GetIDByFactor(1.0 )               )  , PRE->GetIDByFactor(1.0 )               == (pmIdent));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(10)                ) + "' : " + to_string(PRE->GetIDByFactor(10)                 )  , PRE->GetIDByFactor(10)                 == (pmDeca) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(100)               ) + "' : " + to_string(PRE->GetIDByFactor(100)                )  , PRE->GetIDByFactor(100)                == (pmHecto));
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000)              ) + "' : " + to_string(PRE->GetIDByFactor(1000)               )  , PRE->GetIDByFactor(1000)               == (pmKilo) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000000)           ) + "' : " + to_string(PRE->GetIDByFactor(1000000)            )  , PRE->GetIDByFactor(1000000)            == (pmMega) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000000000)        ) + "' : " + to_string(PRE->GetIDByFactor(1000000000)         )  , PRE->GetIDByFactor(1000000000)         == (pmGiga) );
        CPPUNIT_ASSERT_MESSAGE( "'" + PRE->Short(PRE->GetIDByFactor(1000000000000)     ) + "' : " + to_string(PRE->GetIDByFactor(1000000000000)      )  , PRE->GetIDByFactor(1000000000000)      == (pmTera) );
    }
    
    void CheckGetIDByExp10()
    {
        
        // check for GetIDByExp10:
        // this function gets an exponent and takes the closest preMeasure index
        int nExp10 = -15;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmFemto) );
         nExp10 = -14;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmFemto) );
         nExp10 = -13;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPiko) );
         nExp10 = -12;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPiko) );
         nExp10 = -11;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPiko) );
         nExp10 = -10;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmNano) );
         nExp10 = -9;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmNano) );
         nExp10 = -8;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmNano) );
         nExp10 = -7;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMicro) );
         nExp10 = -6;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMicro) );
         nExp10 = -5;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMicro) );
         nExp10 = -4;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMilli) );
         nExp10 = -3;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMilli) );
         nExp10 = -2;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmCenti));
         nExp10 = -1;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmDeci)  );
         nExp10 = 0;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmIdent) );
         nExp10 = 1;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmDeca) );
         nExp10 = 2;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmHecto) );
         nExp10 = 3;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmKilo) );
         nExp10 = 4;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmKilo) );
        nExp10 = 5;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMega) );
        nExp10 = 6;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMega) );
        nExp10 = 7;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmMega) );
        nExp10 = 8;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmGiga) );
        nExp10 = 9;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmGiga) );
        nExp10 = 10;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmGiga) );
        nExp10 = 11;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmTera) );
        nExp10 = 12;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmTera) );
        nExp10 = 13;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmTera) );
        nExp10 = 14;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPeta) );
        nExp10 = 15;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPeta) );
        nExp10 = 16;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmPeta) );
        nExp10 = 17;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmExa) );
        nExp10 = 18;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmExa) );
        nExp10 = 19;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmExa) );
        nExp10 = 20;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmZetta) );
        nExp10 = 21;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmZetta) );
        nExp10 = 22;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmZetta) );
        nExp10 = 23;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmYotta) );
        nExp10 = 24;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmYotta) );
        nExp10 = 25;
        CPPUNIT_ASSERT_MESSAGE( "'"+PRE->Short(PRE->GetIDByExp10(nExp10))+"':"+to_string(PRE->GetIDByExp10(nExp10)), PRE->GetIDByExp10(nExp10) == (pmYotta) );
        

    }
};
