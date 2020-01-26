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
    /////////////////////////////////////////////////////
    // check the measurement device 
    // assuming a measurement setup: 
    // - dc-voltage signal generator outputting demand value
    // - dc-voltage measurement device with a given
    //   tolerance and resolution measuring the generated 
    //   demand value --> measurement value
    // check:
    // - calculate the absolute value of the difference
    //   of demand and measurement value
    // - compare the difference to the tolerance of
    //   the measurement device
    /////////////////////////////////////////////////////

    // declare the demand value ouput by the signal generator
    CFloatingMeasure Demand = 10*mV;    
    
    // declare the measurement value of the measurement device being tested 
    CFloatingMeasure MeasVal = 10.0052*mV;
    CFloatingMeasure Resolution = 1*uV;
    
    // declare the measurement value of the measurement device being tested 
    CFloatingMeasure Tolerance = 5*uV; 
    
    // start our check without activating the resolution for the measurement device
    cout << "check the measurement device without considering its resolution ...." << endl
         << "... Demand value = "  << Demand.PrintShort() << endl
         << "... Meas value = "  << MeasVal.PrintShort() << endl
         << "... Tolerance = "  << Tolerance.PrintShort() << endl
         << "... deviation [mV]= "  << (abs(MeasVal-Demand)).PrintShort() << endl;
    
    cout << ".... " <<  (abs(MeasVal-Demand)).PrintShort() << " > " << Tolerance.PrintShort() << "--> out of tolerance : bummer, what a XXX device!!" << endl;        
    
    cout << " Now consider the resolution :" << endl;
    
    cout << "That is our meas. value without considering the resolution: " << endl << MeasVal.PrintShort() << endl;
    
    MeasVal.Precision(Resolution);
    
    cout << "and now with consideration of the resolution: " << endl << MeasVal.PrintShort() << endl;

    cout << endl << " check again: " << endl << " .... " <<  (abs(MeasVal-Demand)).PrintShort() << " <= " << Tolerance.PrintShort() << "--> in tolerance : best device ever!" << endl;   
    
    cout << endl << " but take care depending on the order of your calculations the result may change again " << endl << " .... " <<  (abs(Demand-MeasVal)).PrintShort() << " > " << Tolerance.PrintShort() << "--> out fof tolerance : what a XXX ... again!" << endl << endl;   
    
    cout << "the reason is: the precision of the left calculation partner rules the precision of the whole expression." << endl << endl;
    
    cout << "to be sure set the precision for all calculation partners ... and you are safe." << endl;
    
    Tolerance.Precision(Resolution);
    Demand.Precision(Resolution);

       cout << " now the precision is set for every value ...." << endl
         << "... Demand value = "  << Demand.PrintShort() << endl
         << "... Meas value = "  << MeasVal.PrintShort() << endl
         << "... Tolerance = "  << Tolerance.PrintShort() << endl
         << "... deviation [mV]= "  << (abs(MeasVal-Demand)).PrintShort() << endl;
 
}
