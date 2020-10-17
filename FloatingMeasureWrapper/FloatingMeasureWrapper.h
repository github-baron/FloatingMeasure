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
#pragma once


using namespace System;
#include "FloatingMeasure/FloatingMeasure.h"
#include "ComplexMeasureWrapper.h"
#include "UtilsManaged.h"
#include "ManagedObject.h"

using namespace ComplexMeasureCLI;

namespace FloatingMeasureCLI
{
    public ref class FloatingMeasureWrapper : public ManagedObject<CFloatingMeasure>
    {
    public:
        /**
         * Default constructor
         */
        FloatingMeasureWrapper() : ManagedObject<CFloatingMeasure>(new CFloatingMeasure())
        {
        }

        /**
         * Copy constructor
         *
         * @param other FloatingMeasureWrapper
         */
        FloatingMeasureWrapper(FloatingMeasureWrapper^ other) : ManagedObject<CFloatingMeasure>(other->GetInstance())
        {

        }
        /**
         * Destructor
         */
        ~FloatingMeasureWrapper() {

        }
        /////////////////////////////////////////////////////
        // operators
        /////////////////////////////////////////////////////

        bool operator==(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator==(*other.GetInstance());
        }

        bool operator!=(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator!=(*other.GetInstance());
        }
        bool operator<(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator<(*other.GetInstance());
        }
        bool operator<=(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator<=(*other.GetInstance());
        }
        bool operator>=(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator>=(*other.GetInstance());
        }
        bool operator>(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator>(*other.GetInstance());
        }

    };
    static FloatingMeasureWrapper^ operator+(FloatingMeasureWrapper^ one, FloatingMeasureWrapper^ other)
    {
        FloatingMeasureWrapper^ fmwResult = gcnew FloatingMeasureWrapper(other);
        fmwResult->GetInstance()->operator+=(*(other->GetInstance()));
        return fmwResult;
    }
    //FloatingMeasureWrapper operator-(FloatingMeasureWrapper other);
    //FloatingMeasureWrapper operator*(FloatingMeasureWrapper other);
    //FloatingMeasureWrapper operator/(FloatingMeasureWrapper other);
    //FloatingMeasureWrapper& operator*=(const double& other);
    //FloatingMeasureWrapper& operator/=(const double& other);
    //FloatingMeasureWrapper operator*(const double& other);
    //FloatingMeasureWrapper operator/(const double& other);

}
