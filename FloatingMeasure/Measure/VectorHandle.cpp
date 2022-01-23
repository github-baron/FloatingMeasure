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

#include "VectorHandle.h"
#include <iostream>



CVectorHandle::CVectorHandle()
{
    vdFactor = new vector<double>;
    vstrShort = new vector<string>;
    vstrLong = new vector<string>;
}


CVectorHandle::~CVectorHandle()
{
    vdFactor->clear();
    vstrLong->clear();
    vstrShort->clear();

    SecureDeleteObjectPointer(vdFactor);
    SecureDeleteObjectPointer(vstrShort);
    SecureDeleteObjectPointer(vstrLong);
}
unsigned int CVectorHandle::Parse(const string& String2Parse, unsigned int& uiStartingPosition, bool bShort, int DefaultIndex)
{   
    // in case there is nothing more to parse: return default:
    if(uiStartingPosition >= String2Parse.length())
        return DefaultIndex;
    
//     std::cout << "uiStartingPosition = " << uiStartingPosition << std::endl;
//     std::cout << "string = " << String2Parse << std::endl;
    
    // initialize with invalid result
    unsigned int uiResultIndex = DefaultIndex;
    
    // set the correct vector pointer 
    vector<string>* pvLabels = bShort ? vstrShort : vstrLong;
    unsigned int uiMaxSizeParsed = 0;
    
    for(unsigned int i = 0; i < pvLabels->size(); i++)
    {
//         std::cout << "label = " << (*pvLabels)[i] << "(index = " << i <<  ", size = " << (*pvLabels)[i].length() << ")" << std::endl;
        
        // ignore labels with zero size 
        if((*pvLabels)[i].length() == 0)
            continue;
        
    
        // the length must fit exactly of the starting position and the found position
        // no other characters are allowed in between
        // this function is used for parsing from left to right by iterative use
        if(String2Parse.find((*pvLabels)[i],uiStartingPosition) == uiStartingPosition && (*pvLabels)[i].length() > uiMaxSizeParsed)
        {
            uiMaxSizeParsed = (*pvLabels)[i].length();
            
//             std::cout << "label found : " << (*pvLabels)[i] << "(size = " << uiMaxSizeParsed << ")" << std::endl;
            
            uiResultIndex = i;
            
        }
    }    

        // set the new position after the found label and do not search anymore
        uiStartingPosition += uiMaxSizeParsed;
//         std::cout << "uiStartingPosition after = " << uiStartingPosition << std::endl;
    return uiResultIndex; 
}


unsigned int CVectorHandle::ParseReverse(const string& String2Parse, unsigned int& uiEndingPosition, bool bShort, int DefaultIndex)
{
    
    // in case there is nothing more to parse: return default:
    if(uiEndingPosition <= 0)
        return DefaultIndex;
    
//     std::cout << "uiEndingPosition = " << uiEndingPosition << std::endl;
//     std::cout << "string = " << String2Parse << std::endl;
    
    
    // set the correct vector pointer 
    vector<string>* pvLabels = bShort ? vstrShort : vstrLong;
    
    // initialize with invalid result
    unsigned int uiResultIndex = DefaultIndex;
    
    // is needed to find the label with maximal size for maximal match
    unsigned int uiMaxSizeParsed = 0;
    
    for(unsigned int i = 0; i < pvLabels->size(); i++)
    {
//         std::cout << "label = " << (*pvLabels)[i] << "(index = " << i <<  ", size = " << (*pvLabels)[i].length() << ")" << std::endl;
        
        // ignore labels with zero size 
        if((*pvLabels)[i].length() == 0)
            continue;
        
        // label size 
        unsigned int uiLabelSize = (*pvLabels)[i].length();
    
        // the length must fit exactly of the starting position and the found position
        // no other characters are allowed in between
        // this function is used for parsing from left to right by iterative use
        if(String2Parse.find((*pvLabels)[i],uiEndingPosition-uiLabelSize) == (uiEndingPosition-uiLabelSize) && uiLabelSize > uiMaxSizeParsed)
        {
            uiMaxSizeParsed = uiLabelSize;
            
//             std::cout << "label found : " << uiLabelSize << "(size = " << uiMaxSizeParsed << ")" << std::endl;
            
            uiResultIndex = i;
            
        }
    }    

        // set the new position after the found label and do not search anymore
        uiEndingPosition -= uiMaxSizeParsed;
//         std::cout << "uiEndingPosition after = " << uiEndingPosition << std::endl;
        
    return uiResultIndex; 
    
}
