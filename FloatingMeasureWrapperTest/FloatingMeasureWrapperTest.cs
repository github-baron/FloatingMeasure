using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using FloatingMeasureCLI;
using ComplexMeasureCLI;
using static ComplexMeasureWrapperMacros.ComplexMeasureWrapperMacros;
using static SimpleMeasureCLI.eBaseMeasureManaged;
using static SimpleMeasureCLI.ePreMeasureManaged;

namespace FloatingMeasureWrapperTest
{
    [TestClass]
    public class FloatingMeasureWrapperTest
    {
        [TestMethod]
        public void ConstructionAssignmentPrecision()
        {
            FloatingMeasureWrapper fmw1 = new FloatingMeasureWrapper(10, fV);
            fmw1 *= 2;
            fmw1.Precision(new FloatingMeasureWrapper(1, fV));
            Assert.AreEqual(fmw1.PrintShort(), "20*fV");
            fmw1.PrecisionActive(false);
            Assert.AreNotEqual(fmw1.PrintShort(), "20*fV");
            fmw1.Precision(new FloatingMeasureWrapper(0.1, fV));
            Assert.AreEqual(fmw1.PrintShort(), "20.0*fV");
            fmw1.Precision(new FloatingMeasureWrapper(0.01, fV));
            Assert.AreEqual(fmw1.PrintShort(), "20.00*fV");

        }
        [TestMethod]
        public void ConstructionAssignmentPrecision()
        {
            FloatingMeasureWrapper fmw1 = new FloatingMeasureWrapper(10, fV);
            fmw1 *= 2;
            fmw1.Precision(new FloatingMeasureWrapper(1, fV));
            Assert.AreEqual(fmw1.PrintShort(), "20*fV");
            fmw1.PrecisionActive(false);
            Assert.AreNotEqual(fmw1.PrintShort(), "20*fV");
            fmw1.Precision(new FloatingMeasureWrapper(0.1, fV));
            Assert.AreEqual(fmw1.PrintShort(), "20.0*fV");
            fmw1.Precision(new FloatingMeasureWrapper(0.01, fV));
            Assert.AreEqual(fmw1.PrintShort(), "20.00*fV");

        }
        [TestMethod]
        public void Simplify()
        {
            FloatingMeasureWrapper fmw1 = new FloatingMeasureWrapper(10, fV);
            
        }
    }
}
