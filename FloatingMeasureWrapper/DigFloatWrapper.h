#pragma once

#include "ManagedObject.h"
#include "DigFloat/DigFloat.h"

using namespace ManagedObjectCLI;

namespace DigFloatCLI
{
    public ref class DigFloatWrapper : public ManagedObject<CDigFloat>
    {
    public:
        /**
         * Default constructor
         */
        DigFloatWrapper() : ManagedObject<CDigFloat>(new CDigFloat())
        {
        }

        /**
         * @brief constructor with  float : 
         * 
         * @param value: double
         */
        DigFloatWrapper(double value) :
            ManagedObject<CDigFloat>(new CDigFloat(value))
        {
        }
    };
}
