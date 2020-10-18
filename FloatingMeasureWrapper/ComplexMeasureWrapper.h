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

#include "ManagedObject.h"
#include "UtilsManaged.h"
#include "Measure/ComplexMeasure.h"
//#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace ManagedObjectCLI;
using namespace SimpleMeasureCLI;


namespace ComplexMeasureCLI
{

    public ref class ComplexMeasureWrapper : public ManagedObject<CComplexMeasure>
    {
    public:

        /**
         * Default constructor: calls CComplexMeasure::_Init()
         */
        ComplexMeasureWrapper() : ManagedObject<CComplexMeasure>(new CComplexMeasure())
        {
        }

        /**
         * @brief Copy constructor with  pointer arg. :  <br>
         *
         * @param other p_other:...
         */
        ComplexMeasureWrapper(ComplexMeasureWrapper^ other) :
            ManagedObject<CComplexMeasure>(new CComplexMeasure(other->GetInstance()))
        {
        }

        /**
         * @brief Copy constructor with  reference arg. :  <br>
         *
         * @param other p_other:...
         */
        ComplexMeasureWrapper(ComplexMeasureWrapper% other) :
            ManagedObject<CComplexMeasure>(new CComplexMeasure(other.GetInstance()))
        {
        }
        /**
         * @brief operator ==:
         */
        static bool operator==(ComplexMeasureWrapper^ one, ComplexMeasureWrapper^ other)
        {
            return one->GetInstance()->operator==(other->GetInstance());
        }
        /**
         * @brief operator !=:
         */
        static bool operator!=(ComplexMeasureWrapper^ one, ComplexMeasureWrapper^ other)
        {
            return one->GetInstance()->operator!=(other->GetInstance());
        }

        /**
         * @brief Constructor by #ePreMeasure index and #eBaseMeasure index:<br>
         * only sets ::pMeasureLeft and deletes ::pMeasureRight
         *
         * @param PreMeasureEnum: pre-measure index
         * @param BaseMeasureEnum: base-measure index
         */
        ComplexMeasureWrapper(const ePreMeasureManaged PreMeasureEnum, const eBaseMeasureManaged BaseMeasureEnum) :
            ManagedObject<CComplexMeasure>(new CComplexMeasure((ePreMeasure)PreMeasureEnum, (eBaseMeasure) BaseMeasureEnum))
        {
        }
        /**
        * @brief operator *: implements implicitely *= ,too
        */
        static ComplexMeasureWrapper^ operator*(ComplexMeasureWrapper^ one, ComplexMeasureWrapper^ other)
        {

            ComplexMeasureWrapper^ cmwResult = gcnew ComplexMeasureWrapper(one);
            cmwResult->GetInstance()->operator*=(other->GetInstance());
            return cmwResult;

        }

        /**
         * @brief operator /: implements implicitely /= ,too
         */
        static ComplexMeasureWrapper^ operator/(ComplexMeasureWrapper^ one, ComplexMeasureWrapper^ other)
        {

            ComplexMeasureWrapper^ cmwResult = gcnew ComplexMeasureWrapper(one);
            cmwResult->GetInstance()->operator/=(other->GetInstance());
            return cmwResult;

        }
        /**
         * @brief sets the pMeasureLeft calling CSimpleMeasure::SetByID
         *
         * @param PreMeasureEnum p_PreMeasureEnum: index of premeasure...
         * @param BaseMeasureEnum p_BaseMeasureEnum: index of base measure
         */
        void SetByID(const ePreMeasureManaged PreMeasureEnum, const eBaseMeasureManaged BaseMeasureEnum)
        {
            GetInstance()->SetByID((ePreMeasure)PreMeasureEnum, (eBaseMeasure)BaseMeasureEnum);
        }
        /**
         * @brief check for valid measures: if one invalid measure is found --> everything is invalid
         *
         * @return bool
         */
        bool Valid()
        {
            return GetInstance()->Valid();
        }

        /**
         * @brief prints the premeasure and the base measure short labels
         *
         * @return string
         */
        String^ Short()
        {
            return gcnew String( GetInstance()->Short().c_str());
        }



    };


}