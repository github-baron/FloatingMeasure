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

#include <FloatingMeasure/FloatingMeasure.h>
#include <Measure/ComplexMeasureMacros.h>
#include <iostream>

using namespace std;
int main(int argc, char* argv[])
{
    // declare distance and time variable as CFloatingMeasure 
    CFloatingMeasure distance = 10 * m;
    CFloatingMeasure time = 1.5*s;

    
    cout << "the distance of " << distance.PrintShort() << endl 
         <<  "is travelled within a time of " << time.PrintShort() << endl;
    
    // simple calculation of velocity
    CFloatingMeasure v = distance / time;
    cout << "this results in a velocity of " << v.PrintShort() << endl;

    // scale to km / h
    v.ScaleTo(km / h);
    cout << "or recalculated into km/h: " << v.PrintShort() << endl;
    
    // set the velocity of a snail
    CFloatingMeasure SnailVelocity = 10*cm/h;
    cout << "this is the speed of the snail: " << SnailVelocity.PrintShort() << endl;
 
    
    // let's find out how much faster are we 
    CFloatingMeasure SnailFactor = v / SnailVelocity;
    cout << "we are much faster than our snail " << SnailFactor.PrintShort() << endl;
 
    // simplify our snail SnailFactor
    SnailFactor.Simplify();
    cout << "that's more readable: that is our SnailFactor without measures" << SnailFactor.PrintShort() << endl;
 

}
