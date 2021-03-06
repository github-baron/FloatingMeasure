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

#include <Utils/Utils.h>
/**
 * @brief estimate the numerical error for a 64bit double incrementing the LSB.
 *       The maximal relative error is about 2.3e-16. Hence, for a value of 1e+308
 *       the error is about 1e+292.
 */
double DoubleMachineEpsilon(double dValue)
{ 
    dbl_64 s;
    s.d64 = dValue;
    s.i64++;
        
    // logging
    LOGTRACE("FloatingMeasure::Utils::DoubleMachineEpsilon ","DoubleMachineEpsilon(" + to_string( dValue ) + ") = " + to_string(fabs(s.d64 - dValue)));
    
    return fabs(s.d64 - dValue);

}
double Round2Precision(const double dValue,const int nPrecision)
{
    double dFactor = pow(10.,nPrecision);
    bool bPos = dValue >0;
    return double ( (long)(dValue*dFactor + (bPos ? 1 : -1)*(0.5)) )/dFactor; 
}
string Bool2String(const bool bBool)
{
    return bBool ? "true" : "false";
}
