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

#include "ComplexMeasure.h"

CComplexMeasure::CComplexMeasure()
{
    _Init();
}

CComplexMeasure::CComplexMeasure(const CComplexMeasure& other)
{
    // init without allocation of pMeasureLeft
    _Init(false);
    
    // get the simple measure by copy construction 
    pMeasureLeft = new CSimpleMeasure(other.pMeasureLeft);
    opEnum = other.opEnum;
    nCMExp10 = other.nCMExp10;
    dfCMFactor = other.dfCMFactor;
    
    // set MeasureRight ... if needed
    // recursive call of this constructor via CComplexMeasure(const CComplexMeasure* other)
    if( other.pMeasureRight != nullptr )
        pMeasureRight = new CComplexMeasure(other.pMeasureRight);
    
}

CComplexMeasure::CComplexMeasure(const CComplexMeasure* other)
{
    // init without allocation of pMeasureLeft
    _Init(false);
    
    // get the simple measure by copy construction 
    pMeasureLeft = new CSimpleMeasure(other->pMeasureLeft);
    opEnum = other->opEnum;
    nCMExp10 = other->nCMExp10;
    dfCMFactor = other->dfCMFactor;
    
    // set MeasureRight ... if needed
    // recursive call of this constructor via CComplexMeasure(const CComplexMeasure* other)
    if( other->pMeasureRight != nullptr )
        pMeasureRight = new CComplexMeasure(other->pMeasureRight);
}
CComplexMeasure::CComplexMeasure(const ePreMeasure PreMeasureEnum, const eBaseMeasure BaseMeasureEnum)
{
    _Init();
    pMeasureLeft->SetByID(PreMeasureEnum, BaseMeasureEnum);
}

CComplexMeasure::~CComplexMeasure()
{
    // recursive call 
    if( pMeasureRight != nullptr)
    {
        pMeasureRight->~CComplexMeasure();
        pMeasureRight = nullptr;
    }
    
    opEnum = opUnknown;
    pMeasureLeft->~CSimpleMeasure();
    
}

CComplexMeasure& CComplexMeasure::operator*=(const CComplexMeasure& other)
{
    _AllocateLastUnsetMeasureRight(*this,other,opMult);
    
    return *this;
    
}

CComplexMeasure & CComplexMeasure::operator/=(const CComplexMeasure& other)
{
    _AllocateLastUnsetMeasureRight(*this, other, opDivide);
    
    return * this;
}
CComplexMeasure CComplexMeasure::operator*(const CComplexMeasure& other)
{
    CComplexMeasure Result(*this);
    Result *= other;
    return Result;
}
CComplexMeasure CComplexMeasure::operator/(const CComplexMeasure& other)
{
    CComplexMeasure Result(*this);
    Result /= other;
    return Result;
}

CComplexMeasure& CComplexMeasure::operator=(const CComplexMeasure& other)
{
    pMeasureLeft->operator=(other.pMeasureLeft);
    opEnum = other.opEnum;
    nCMExp10 = other.nCMExp10;
    dfCMFactor = other.dfCMFactor;
    
    // delete right operand
    SecureDeleteObjectPointer(pMeasureRight);
    
    // set again, if necessary
    if(other.pMeasureRight != nullptr)
        pMeasureRight = new CComplexMeasure(other.pMeasureRight);
    
    return *this;
}

bool CComplexMeasure::operator==(const CComplexMeasure& other) const
{
    
    CComplexMeasure CheckThis(*this);
    CComplexMeasure CheckOther(other);
    CheckThis.Normalize();
    CheckOther.Normalize();
    
    // first handle the simple case: pMeasureRight == nullptr
    // compare the simple measures only: pMeasureLeft == other.pMeasureLeft
    if( CheckThis.pMeasureRight == nullptr && CheckOther.pMeasureRight == nullptr)
    {
        return CheckThis.pMeasureLeft == CheckOther.pMeasureLeft;
    }

    // for the more complex case:
    // equality is achieved if meaure1 / measure2 = 1
    // make all calculations with the precision of *this
    CheckThis /= other;
    
    // do a simplification
    CheckThis.Simplify();
    CheckThis.Normalize();
    return CheckThis.CMFactor() == 1 &&
           CheckThis.CMExp10() == 0 &&
           CheckThis.pMeasureRight == nullptr &&
           CheckThis.pMeasureLeft->BaseID() == bmNumber;
    
}

bool CComplexMeasure::operator!=(const CComplexMeasure& other) const
{
    return !(*this == other);
}
bool CComplexMeasure::Compatible(const CComplexMeasure& other) const
{
    // compatibility is if measure1 = f * measure2 (no offsets!!)
    CComplexMeasure Check(*this);
    Check /= other;
    
    // do a simplification
    Check.Simplify();
    Check.Normalize();
    return Check.pMeasureRight == nullptr &&
           Check.pMeasureLeft->BaseID() == bmNumber;
    
}

void CComplexMeasure::SetByID(const ePreMeasure PreMeasureEnum, const eBaseMeasure BaseMeasureEnum)
{

    SecureDeleteObjectPointer(pMeasureRight);
    _Init(false);
    pMeasureLeft->SetByID(PreMeasureEnum, BaseMeasureEnum);

}

void CComplexMeasure::_Init(bool bAllocateMeasureLeft /*= true*/)
{
    opEnum = opUnknown,
    pMeasureRight=nullptr;
    if(bAllocateMeasureLeft)
        pMeasureLeft = new CSimpleMeasure();
    
    // neutral setting for factor and nCMExp10
    dfCMFactor = 1;
    nCMExp10 = 0;
    
}
void CComplexMeasure::_AllocateLastUnsetMeasureRight(CComplexMeasure& cmOperandLeft, const CComplexMeasure& cmOperandRight, const eOperation OperationEnum)
{                                                   
    // go to the end of the line and add the new complex measure with multiplication
    CComplexMeasure* pCMLeftLast = cmOperandLeft.pMeasureRight;
    if( pCMLeftLast == nullptr )
        pCMLeftLast = &cmOperandLeft;

    // search for last set pMeasureRight: pCMLeftLast is set to this pointer
    while(pCMLeftLast->pMeasureRight != nullptr )
        pCMLeftLast = pCMLeftLast->pMeasureRight;
        
    // add the new complex number at the end ... and the corresponding operator
    pCMLeftLast->pMeasureRight = new CComplexMeasure(cmOperandRight);
    pCMLeftLast->opEnum = OperationEnum;
    if(OperationEnum == opDivide)
        pCMLeftLast->pMeasureRight->_InvertOP();
        
    // in case the cmOperandRight has factors and exp10  : 
    // collect the nCMExp10 and dfCMFactor to cmOperandLeft::nCMExp10 and cmOperandLeft::dfCMFactor
    cmOperandLeft._COllectCMExp10CMFactorWrapper();
}
  
void CComplexMeasure::_InvertOP()
{
    // invert own OP
    Invert(opEnum);
    
    // iterate over the consecutive complex measures
    CComplexMeasure* pCMLast = pMeasureRight;
    if( pCMLast != nullptr )
        while(pCMLast->pMeasureRight != nullptr )
        {
            Invert(pCMLast->opEnum);
            pCMLast = pCMLast->pMeasureRight;
        }
  
}
string CComplexMeasure::PrintAllShort()
{
    string strAllShort;
    strAllShort = pMeasureLeft->Short();
    
    // use recursive call to get the whole string
    if( pMeasureRight != nullptr )
        strAllShort+=  OPShort() + pMeasureRight->PrintAllShort();
    
    return strAllShort;
        
}
void CComplexMeasure::Normalize()
{
    // initialize the arguments for _Normalize with nullptr:
    // --> indicates the first call
    eOperation* pPreviousOP = nullptr;
    int* pdTempPreMeasureExp10Collector =nullptr;
    CDigFloat* pdfTempCMFactorCollector =nullptr;
    CComplexMeasure* pFirstComplexMeasure = nullptr;
    
    // send first call    
    _Normalize(pPreviousOP, pdTempPreMeasureExp10Collector, pdfTempCMFactorCollector, pFirstComplexMeasure);
    
}
    

void CComplexMeasure::_Normalize(eOperation* &pPreviousOP, int* &pdTempPreMeasureExp10Collector , CDigFloat* &pdTempCMFactorCollector, CComplexMeasure* &pFirstComplexMeasure)
{   
    // set the flag for being called the first time
    bool bCalledTheFirstTime = (pPreviousOP == nullptr);
    
    // set the collector pointers if not set : this happens when this function is called the first time
    if( bCalledTheFirstTime ){
        
        // init all factor collectors with 1
        pdTempPreMeasureExp10Collector = new int[1];
        pdTempCMFactorCollector = new CDigFloat(1);
        pdTempPreMeasureExp10Collector[0] = 0;
        
        // first operand is always on the multiplication side
        pPreviousOP = new eOperation[1];
        pPreviousOP[0] = (opMult);
        
        // ... and for the final results: these will be set at the end of the consecutive recursive calls
        pFirstComplexMeasure = this;
        
    }   

    // set the pre factor and SI factor applying the corresponding operator 
    switch(pPreviousOP[0])
    {
        case opMult:
            
            // pre measures can be added any time: no offsets to "fear" --> set PreMeaures to identity
            pdTempPreMeasureExp10Collector[0]  += PRE->Exp10( pMeasureLeft->PreID() ) + CMExp10();
        
            // CMExp10 can be set to identity right now
            CMExp10(0);
            
            // get CMFactor, too
            *pdTempCMFactorCollector *= CMFactor();
            
            // reset the CMFactor to 1
            CMFactor(1);
        
            // base units with offset will be neglected --> this is trouble in complex measures
            // REM: only in case this function is called the first and will not be called
            //      again (i.e. pMeasureRight == nullptr) we can handle offsets 
            //      (e.g. for recalculation of °C --> °K) : handling will be done below
            //      "if( pMeasureRight == nullptr)
            if( BASE->Offset( pMeasureLeft->BaseID() ) == 0 )
            {
                // get the base SIfactor 
                *pdTempCMFactorCollector *= BASE->Factor( pMeasureLeft->BaseID() );
                
                // reset pMeasureLeft to SI
                pMeasureLeft->SetByID(pmIdent, BASE->SIID(pMeasureLeft->BaseID()) );
            }
            else
            {
                // reset only the PreMeasurefactor of pMeasureLeft to identity
                pMeasureLeft->SetByID(pmIdent, pMeasureLeft->BaseID());
            }
            
            
            break;
            
        case opDivide:
            
            // pre measures can be added any time: no offsets to "fear"
            pdTempPreMeasureExp10Collector[0]  -= PRE->Exp10( pMeasureLeft->PreID() ) + nCMExp10;
            
            // CMExp10 can be set to 0 right now
            CMExp10(0);
            
            // get CMFactor, too
            *pdTempCMFactorCollector /= CMFactor();
            
            // reset the CMFactor to 1
            CMFactor(1);
            
            // base units with offset will be neglected --> this is trouble in complex measures
            if( BASE->Offset( pMeasureLeft->BaseID() ) == 0 )
            {
                // get the base SIfactor 
                *pdTempCMFactorCollector /= BASE->Factor( pMeasureLeft->BaseID() );
                
                // reset pMeasureLeft to SI
                pMeasureLeft->SetByID(pmIdent, BASE->SIID(pMeasureLeft->BaseID()) );
            }
            else
            {
                // reset only the PreMeasurefactor of pMeasureLeft to identity
                pMeasureLeft->SetByID(pmIdent, pMeasureLeft->BaseID());
            }
            
            break;
            
        default:         
            
            break;
        
    }   // endswitch(pPreviousOP[0])
    
 
    // if pMeasureRight is a nullptr --> recursion stops here:
    // finally calculate dfCMFactor and nCMExp10
    if( pMeasureRight == nullptr )
    {
        // setting the factor completely new
        pFirstComplexMeasure->dfCMFactor = *pdTempCMFactorCollector;
        
        // subtract the first exponent ... otherwise it will be counted twice
        pFirstComplexMeasure->CMExp10(pdTempPreMeasureExp10Collector[0]-pFirstComplexMeasure->CMExp10());
        
        // tidy up
        SecureDeleteObjectPointer(pdTempPreMeasureExp10Collector);
        SecureDeleteObjectPointer(pdTempCMFactorCollector);
        SecureDeleteVectorPointer(pPreviousOP);
                
    }   // endif( pMeasureRight == nullptr )
    else
    {
        // ... otherwise go on:
        // set operator correctly
        pPreviousOP[0] = opEnum;
        
        // and call recursively
        pMeasureRight->_Normalize(pPreviousOP, pdTempPreMeasureExp10Collector, pdTempCMFactorCollector, pFirstComplexMeasure );
        
    }
    
}


void CComplexMeasure::_COllectCMExp10CMFactorWrapper()
{
    // initialize the arguments for _Normalize with nullptr:
    // --> indicates the first call (honestly: setting pOP = nullptr would be enough)
    eOperation* pPreviousOP = nullptr;
    int* pdTempPreMeasureExp10Collector =nullptr;
    CDigFloat* pdfTempCMFactorCollector =nullptr;
    CComplexMeasure* pFirstComplexMeasure =nullptr;
    
    // send first call    
//     _COllectCMExp10CMFactor(pPreviousOP,peSIPreMeasure,pdTempPreMeasureExp10Collector,pdfCMFactor,pdfTempCMFactorCollector);
    _COllectCMExp10CMFactor(pPreviousOP,pdTempPreMeasureExp10Collector,pdfTempCMFactorCollector,pFirstComplexMeasure);
}
void CComplexMeasure::_COllectCMExp10CMFactor(eOperation *& pPreviousOP, int *& pdTempPreMeasureExp10Collector, CDigFloat*& pdTempCMFactorCollector, CComplexMeasure* &pFirstComplexMeasure)
{
     
    // set the collector pointers if not set : 
    // this happens when the primary CComplexMeasure::Normalize is called
    if( pPreviousOP == nullptr){
        
        // init all factor collectors with 1
        pdTempPreMeasureExp10Collector = new int[1];
        pdTempCMFactorCollector = new CDigFloat(1);
        pdTempPreMeasureExp10Collector[0] = 0;
        
        
        // first operand is always mult
        pPreviousOP = new eOperation[1];
        pPreviousOP[0] = (opMult);
        
        // ... and for the final results: these will be set at the end of the consecutive recursive calls
//         pnCMExp10 = &nCMExp10;
//         pdfCMFactor  = &dfCMFactor;
        pFirstComplexMeasure = this;
        
    }   

    // set the pre factor and SI factor applying the corresponding operator 
    switch(pPreviousOP[0])
    {
        case opMult:
            
            // CM pre measures exponents can be added 
            pdTempPreMeasureExp10Collector[0]  += CMExp10();
            
            // reset to identity for this
            CMExp10(0);
            
            // get the base SIfactor 
            *pdTempCMFactorCollector *= CMFactor();
            
            //reset the CMFactor for this
            CMFactor(1);
            
            break;
            
        case opDivide:
            
            
            // CM pre measures exponents can be added 
            pdTempPreMeasureExp10Collector[0]  -= CMExp10();
            
            // reset to identity
            CMExp10(0);
            
            // get the base SIfactor 
            *pdTempCMFactorCollector /= CMFactor();
            
            //reset the CMFactor for this
            CMFactor(1);
            
            break;
            
        default:         
            
            break;
        
    }   // endswitch(actOP)
    
 
    // if pMeasureRight is a nullptr --> recursion stops here:
    // finally calculate dSIFactor and eSIPreMeasure
    if( pMeasureRight == nullptr )
    {
        
        pFirstComplexMeasure->dfCMFactor = *pdTempCMFactorCollector;
        pFirstComplexMeasure->CMExp10(pdTempPreMeasureExp10Collector[0]);
        
        // tidy up
        SecureDeleteObjectPointer(pdTempPreMeasureExp10Collector);
        SecureDeleteObjectPointer(pdTempCMFactorCollector);
        SecureDeleteVectorPointer(pPreviousOP);
                
    }   // endif( pMeasureRight == nullptr )
    else
    {
        // ... otherwise go on:
        // set operator correctly
        pPreviousOP[0] = opEnum;
        
        // and call recursively
        pMeasureRight->_COllectCMExp10CMFactor(pPreviousOP,pdTempPreMeasureExp10Collector , pdTempCMFactorCollector, pFirstComplexMeasure);
        
    }
   
    
}
void CComplexMeasure::Simplify()
{
    // search for the next CSimpleMeasure in the chain with the same SI unit index
    // hand over the starting pointer CComplexMeasure*, the corresponding CMExp10 and CMFactor pointers
    // which will be filled
    eOperation eFirstOP = opMult;    
    _Simplify(eFirstOP);    
       
    // at this point tidy up:
    // collect all CMExp10 and CMFactor
    _COllectCMExp10CMFactorWrapper();
    
    // clear all  measureless neutral elements (pmIdent, bmNumber)(except at the very start)
    // generated by _SearchAndShortenSameSIIndex
    if(pMeasureRight != nullptr)
       pMeasureRight->_RemoveNeutralNumbers(*this);
        
    // in case the operator is opMult and the first measure is a bmNumber --> remove this pointer, too
    // replace it by the pMeasureRight: e.g. 1*s --> s
    if(opEnum == opMult && pMeasureLeft->BaseID() == bmNumber && pMeasureRight != nullptr)
    {
        // 1. set the pMeasureLeft to pMeasureLeft of the consecutive ComplexMeasure
        // 2. set the op to op of the consecutive ComplexMeasure
        pMeasureLeft->operator=(pMeasureRight->pMeasureLeft);
        opEnum = pMeasureRight->opEnum;
        
        //  3. tidy up pMeasureLeft and set op of consecutive ComplexMeasure
        SecureDeleteObjectPointer(pMeasureRight->pMeasureLeft);
        pMeasureRight->opEnum = opUnknown;
        
        // 4. set pMeasureRight of this to pMeasureRight of consecutive ComplexMeasure
        pMeasureRight = pMeasureRight->pMeasureRight;
        
    }
 
}
void CComplexMeasure::_Simplify(eOperation& PreviousOP)
{
    
    // search for a SI partner with inverted OP for cancellation
    // hand over 
    // 1. the pointer of calling instance
    // 2. the operator of this calling instance
    // 3. the operator preceeding pMeasureRight
    // for the first call the calling instance is this
    // and the operator of the preceeding pMeasureRight is the opEnum of this
    if( pMeasureRight != nullptr)
        pMeasureRight->_SearchAndShortenSameSIIndex(this, PreviousOP, opEnum);
    
    // recursive call of all consecutive ComplexMeasures which search
    // for SI partners and cancel with them setting both to measureless number
    if(pMeasureRight != nullptr)
        pMeasureRight->_Simplify(opEnum);
}


void CComplexMeasure::_RemoveNeutralNumbers(CComplexMeasure &PreviousComplexMeasure)
{
    // this takes us to the end of the ComplexMeasure list
    if(pMeasureRight != nullptr)
        pMeasureRight->_RemoveNeutralNumbers(*this);
    
    // if we come here : the end was reached and we are going backward in the list
    // check if this simple measure is measureless 
    if( pMeasureLeft->PreID() == pmIdent && pMeasureLeft->BaseID() == bmNumber)
    {
        // set the reference here to the successor ... or nullptr
        PreviousComplexMeasure.pMeasureRight = pMeasureRight;
        
        // in case the successor is null --> opEnum = opUnknown
        if(pMeasureRight == nullptr)
            PreviousComplexMeasure.opEnum = opUnknown;         
        
        // delete pMeasureLeft, reset pMeasureRight
        pMeasureRight = nullptr;
        opEnum = opUnknown;
        SecureDeleteObjectPointer(pMeasureLeft);
    }
    
}

void CComplexMeasure::_SearchAndShortenSameSIIndex(CComplexMeasure* pShortenPartner,eOperation& eOPofShortenPartner, eOperation& eOPofConsecutiveShortenPartner)
{
    
    // in case SI Index of simple measure is not the same 
    // or 
    // one of the partners is already cancelled (i.e. BaseMeasureEnum == bmNumber)
    // or
    // the offsets for recalculation to SI are not zero (mathematical desaster in general which I will not solve here)
    // or
    // the operators are the same
    // --> go on
    if( BASE->SIID( pShortenPartner->pMeasureLeft->BaseID() ) != BASE->SIID( pMeasureLeft->BaseID()) ||
        BASE->SIID( pShortenPartner->pMeasureLeft->BaseID() ) == bmNumber ||
        BASE->SIID( pMeasureLeft->BaseID()) == bmNumber ||
        pShortenPartner->pMeasureLeft->SIOffset() != 0 ||  pMeasureLeft->SIOffset() != 0||
        eOPofShortenPartner == eOPofConsecutiveShortenPartner)
    {
        // recursive calll ... only if there is a successor
        if(pMeasureRight != nullptr)
            pMeasureRight->_SearchAndShortenSameSIIndex(pShortenPartner, eOPofShortenPartner, opEnum);
    }
    else
    {
        pShortenPartner->_ResolveMeasureLeft();
        _ResolveMeasureLeft();
    }
}

 
void CComplexMeasure::_ResolveMeasureLeft()
{
    // nexp10 =0 --> 
    // premeausre of pMeasureLeft is resolved in dfCMFactor
    nCMExp10 += PRE->Exp10( pMeasureLeft->PreID());
    dfCMFactor *= BASE->Factor( pMeasureLeft->BaseID());
        
    // now set measure left to neutral element without measure: 1
    pMeasureLeft->SetByID( pmIdent, bmNumber);
    
}
 
void CComplexMeasure::_CollectLeftSortByOp(map<eOperation, CComplexMeasure *>& mOpMeas)
{
    if( pMeasureRight != nullptr )
    {
        // collect for the actual operator the next operand 
        mOpMeas[opEnum]= this;
        
        // recursive call :
        pMeasureRight->_CollectLeftSortByOp(mOpMeas);
    }
}

void CComplexMeasure::ScaleTo(const CComplexMeasure& other)
{
    if(!Compatible(other))
    {
        // invalidate everything
        _Init();
    }
    else
    {
        // rescaling: do this->operator/( other )--> Simplify:
        // should result in a dimensionless number with the corresponding factors
        CComplexMeasure Check(*this);
        Check /= other;
        Check.Simplify();
        
        // now set factor and exp10 
        *this = other;
        dfCMFactor *= Check.CMFactor();
        nCMExp10 += Check.CMExp10();
    }
    
}
bool CComplexMeasure::Valid()
{
    // set bool from pMeasureLeft
    bool bValid = pMeasureLeft->Valid();
    
    // recursive call setting bValid 
    if( bValid && pMeasureRight != nullptr)
        pMeasureRight->_Valid(bValid);
    
    return bValid;
}

void CComplexMeasure::_Valid(bool& bValid)
{
    // we come here only if bValid is true
    // reset bValid from pMeasureLeft
    bValid = pMeasureLeft->Valid();
    
    // go on with recursive call 
    if( bValid && pMeasureRight != nullptr)
        pMeasureRight->_Valid(bValid);
    
}

const double CComplexMeasure::ReleaseExp10AndFactor()
{
    double Result = CMFactor().RawValue() * pow(10,CMExp10());
    
    // reset
    CMFactor(1);
    CMExp10(0);
    
    return Result;
}


string CComplexMeasure::DebugOut()
{
    ostringstream oss;
    
    oss << "CComplexMeasure valid: " << Bool2String(Valid()) << endl
        << "this: " << this << endl <<
           "pMeasureLeft:"  << pMeasureLeft->DebugOut() << endl <<
           "opEnum:"    << OPShort() << endl << 
           "CMFactor: " << CMFactor().Print() << endl <<
           "nCMExp10: " << CMExp10() << endl <<
           "pMeasureRight:" << pMeasureRight << endl;

    if( pMeasureRight != nullptr)
           oss << pMeasureRight->DebugOut();
    
    return oss.str();
    
}

