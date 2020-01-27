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

#ifndef CMEASUREOPERATOR_H
#define CMEASUREOPERATOR_H

#include "VectorHandle.h"

typedef enum{          
    opMult = 0,        /*!<0  : multiplication is the starting element*/
    opDivide,          /*!<1  : division */
    opLast,            /*!<2  : last operation ... invalid (for iteration)*/
    opUnknown = opLast /*!<3  : invalid operation = last operation*/
} eOperation;          
                       

/**
 * @brief CMeasureOperator: this class is actually unused ...
 * 
 */
class 
#ifdef _WIN32
DLLEXPORT_CMD
#endif
 CMeasureOperator :  public CVectorHandle
{
public:
    /**
     * Default constructor: calls _Init()
     */
    CMeasureOperator();
 
    /**
     * Destructor
     */
    ~CMeasureOperator();

protected:
    
    /**
     * @brief initialises long and short label by enum index eOperation
     * 
     */
    virtual void _Init();

};

typedef CSingleton<CMeasureOperator> CMeasureOperatorSingleton;

/**
 * @brief inverts given operation (e.g. "*" --> "/")
 * 
 * @param Op2Invert: eOperation to invert
 */
void Invert(eOperation& Op2Invert);

#endif // CMEASUREOPERATOR_H

