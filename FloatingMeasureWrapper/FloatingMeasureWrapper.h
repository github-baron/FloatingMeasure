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
#include "DigFloatWrapper.h"
#include "UtilsManaged.h"
#include "ManagedObject.h"

using namespace ComplexMeasureCLI;
using namespace SimpleMeasureCLI;
using namespace DigFloatCLI;

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
         * construction by value and measure
         *
         * @param value: double
         * @param measure: ComplexMeasureWrapper^
         */
        FloatingMeasureWrapper(double value, ComplexMeasureWrapper^ measure) : ManagedObject<CFloatingMeasure>(new CFloatingMeasure(value, measure->GetInstance()))
        {
        }

        /**
         * construction by value (measure is ident : no unit)
         *
         * @param value: double
         */
        FloatingMeasureWrapper(double value) : ManagedObject<CFloatingMeasure>(new CFloatingMeasure(value, new CComplexMeasure(ePreMeasure::pmIdent, eBaseMeasure::bmNumber)))
        {
        }

        /**
         * construction by measure: value = 1
         *
         * @param measure: ComplexMeasureWrapper^
         */
        FloatingMeasureWrapper(ComplexMeasureWrapper^ measure) : ManagedObject<CFloatingMeasure>(new CFloatingMeasure(1., measure->GetInstance()))
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
        ~FloatingMeasureWrapper() 
        {
        }

        /////////////////////////////////////////////////////
        // operators
        /////////////////////////////////////////////////////
        /**
         * operator *
         *
         * @param one: FloatingMeasureWrapper^
         * @param other: FloatingMeasureWrapper^ 
         */
        static FloatingMeasureWrapper^ operator*(FloatingMeasureWrapper^ one, FloatingMeasureWrapper^ other)
        {
            FloatingMeasureWrapper^ fmResult = gcnew FloatingMeasureWrapper(one);
            fmResult->GetInstance()->operator*=(*other->GetInstance());
            return fmResult;
        }
        /**
         * operator *
         *
         * @param one: FloatingMeasureWrapper^
         * @param value: double
         */
        static FloatingMeasureWrapper^ operator*(FloatingMeasureWrapper^ one, double value)
        {
            FloatingMeasureWrapper^ fmResult = gcnew FloatingMeasureWrapper(one);
            fmResult->GetInstance()->operator*=(value);
            return fmResult;
        }
        /**
         * operator *
         *
         * @param one: FloatingMeasureWrapper^
         * @param measure: ComplexMeasureWrapper^
         */
        static FloatingMeasureWrapper^ operator*(FloatingMeasureWrapper^ one, ComplexMeasureWrapper^ measure)
        {
            FloatingMeasureWrapper^ fmResult = gcnew FloatingMeasureWrapper(one);
            fmResult->GetInstance()->Measure().operator*=(measure->GetInstance());
            return fmResult;
        }
        /**
         * operator /
         *
         * @param one: FloatingMeasureWrapper^
         * @param other: FloatingMeasureWrapper^
         */
        static FloatingMeasureWrapper^ operator/(FloatingMeasureWrapper^ one, FloatingMeasureWrapper^ other)
        {
            FloatingMeasureWrapper^ fmResult = gcnew FloatingMeasureWrapper(one);
            fmResult->GetInstance()->operator/=(*other->GetInstance());
            return fmResult;
        }
        /**
         * operator /
         *
         * @param one: FloatingMeasureWrapper^
         * @param measure: ComplexMeasureWrapper^
         */
        static FloatingMeasureWrapper^ operator/(FloatingMeasureWrapper^ one, ComplexMeasureWrapper^ measure)
        {
            FloatingMeasureWrapper^ fmResult = gcnew FloatingMeasureWrapper(one);
            fmResult->GetInstance()->Measure().operator/=(*measure->GetInstance());
            return fmResult;
        }
        /**
         * operator /
         *
         * @param one: FloatingMeasureWrapper^
         * @param value: double
         */
        static FloatingMeasureWrapper^ operator/(FloatingMeasureWrapper^ one, double value)
        {
            FloatingMeasureWrapper^ fmResult = gcnew FloatingMeasureWrapper(one);
            fmResult->GetInstance()->operator/=(value);
            return fmResult;
        }
        /**
         * operator +
         *
         * @param one: FloatingMeasureWrapper^
         * @param other: FloatingMeasureWrapper^
         */
        static FloatingMeasureWrapper^ operator+(FloatingMeasureWrapper^ one, FloatingMeasureWrapper^ other)
        {
            FloatingMeasureWrapper^ fmwResult = gcnew FloatingMeasureWrapper(other);
            fmwResult->GetInstance()->operator+=(*other->GetInstance());
            return fmwResult;
        }
        /**
         * operator -
         *
         * @param one: FloatingMeasureWrapper^
         * @param other: FloatingMeasureWrapper^
         */
        static FloatingMeasureWrapper^ operator-(FloatingMeasureWrapper^ one, FloatingMeasureWrapper^ other)
        {
            FloatingMeasureWrapper^ fmwResult = gcnew FloatingMeasureWrapper(other);
            fmwResult->GetInstance()->operator-=(*other->GetInstance());
            return fmwResult;
        }
        /**
         * operator ==
         *
         * @param other: FloatingMeasureWrapper^
         */
        bool operator==(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator==(*other.GetInstance());
        }
        /**
         * operator !=
         *
         * @param other: FloatingMeasureWrapper^
         */
        bool operator!=(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator!=(*other.GetInstance());
        }
        /**
         * operator <
         *
         * @param other: FloatingMeasureWrapper^
         */
        bool operator<(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator<(*other.GetInstance());
        }
        /**
         * operator <=
         *
         * @param other: FloatingMeasureWrapper^
         */
        bool operator<=(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator<=(*other.GetInstance());
        }
        /**
         * operator >=
         *
         * @param other: FloatingMeasureWrapper^
         */
        bool operator>=(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator>=(*other.GetInstance());
        }
        /**
         * operator >
         *
         * @param other: FloatingMeasureWrapper^
         */
        bool operator>(FloatingMeasureWrapper other)
        {
            return GetInstance()->operator>(*other.GetInstance());
        }
        //////////////////////////////////////
        // other functions
        //////////////////////////////////////
        /**
         * @brief prints the value, operator, and the premeasure and the base measure short labels
         *
         * @return string
         */
        String^ PrintShort()
        {
            return gcnew String(GetInstance()->PrintShort().c_str());
        }
        /**
         * @brief sets the precision of the floating measure
         *
         * @param precision: FloatingMeasureWrapper^
         */
        void Precision(FloatingMeasureWrapper^ precision)
        {
            GetInstance()->Precision(*precision->GetInstance());
            GetInstance()->PrecisionActive(true);
        }
        /**
         * @brief gets the precision of the floating measure
         *
         */
        FloatingMeasureWrapper^ Precision()
        {
            FloatingMeasureWrapper^ fmwResult = gcnew FloatingMeasureWrapper();
            fmwResult->GetInstance()->operator=( GetInstance()->Precision() );
            return fmwResult;
        }
        /**
         * @brief sets the precision active of the floating measure
         *
         * @param bActivate: bool
         */
        void PrecisionActive(bool bActivate)
        {
            GetInstance()->PrecisionActive(bActivate);
        }
        /**
         * @brief sets the precision active of the floating measure
         *
         * @param bActivate: bool
         */
        bool PrecisionActive()
        {
            return GetInstance()->Floating().PrecisionActive();
        }
    };

}
