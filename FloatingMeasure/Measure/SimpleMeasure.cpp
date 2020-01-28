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

#include "SimpleMeasure.h"

CSimpleMeasure::CSimpleMeasure()
{
    _Init();
}

CSimpleMeasure::CSimpleMeasure(const CSimpleMeasure& other)
{
    _Init();
    SetByID(other.PreID(), other.BaseID());
}
CSimpleMeasure::CSimpleMeasure(const CSimpleMeasure* other)
{
    _Init();
    SetByID(other->PreID(),other->BaseID());
}
CSimpleMeasure::~CSimpleMeasure()
{
    SecureDeleteObjectPointer(strShort);
    SecureDeleteObjectPointer(strLong);
}

CSimpleMeasure& CSimpleMeasure::operator=(const CSimpleMeasure& other)
{

    SetByID(other.PreID(), other.BaseID());
    return *this;
}


bool const CSimpleMeasure::operator==(const CSimpleMeasure& other) const
{

    return BaseID()== other.BaseID() &&
           PreID() == other.PreID();
}

bool CSimpleMeasure::operator!=(const CSimpleMeasure& other) const
{
    return false;
    
}
void CSimpleMeasure::SetByID(const ePreMeasure PreMeasureEnum, const eBaseMeasure BaseMeasureEnum)
{
    BaseIndex = BaseMeasureEnum;
    PreIndex = PreMeasureEnum;
    
    dSIFactor = PRE->Factor(PreID()) * BASE->Factor(BaseID());
    dSIOffset = BASE->Offset(BaseID());
    *strLong   = PRE->Long(PreID()) + BASE->Long(BaseID()) ;
    *strShort  = PRE->Short(PreID()) + BASE->Short(BaseID()) ;
}
void CSimpleMeasure::SetByShort(const string& strPreLabelShort, const string& strBaseLabelShort)
{
    SetByID( PRE->GetIDByShortLabel(strPreLabelShort), BASE->GetIDByShortLabel(strBaseLabelShort));
}
void CSimpleMeasure::SetByLong(const string& strPreLabelLong, const string& strBaseLabelLong)
{
    SetByID( PRE->GetIDByLongLabel(strPreLabelLong), BASE->GetIDByLongLabel(strBaseLabelLong));
}

const string CSimpleMeasure::DebugOut() 
{
   return "Main (" + to_string(PreID()) + ", " + to_string(BaseID()) + "):\n" +
          "\tSIOffset = " + to_string(SIOffset()) + "\n" +
          "\tSIFactor = " + to_string(SIFactor()) + "\n" +
          "\tShort = " + Short() + "\n" +
          "\tLong = " + Long() + "\n\n" + 
          "Pre (" + to_string(PreID()) + "):\n" + PRE->DebugOut(PreID()) + "\n\n" +
          "Base (" + to_string(BaseID()) + "):\n" + BASE->DebugOut(BaseID());
          
}

void CSimpleMeasure::_Init()
{
    PreIndex=pmUnknown;
    BaseIndex=bmUnknown;
    strShort = new string;
    strLong = new string;
}
