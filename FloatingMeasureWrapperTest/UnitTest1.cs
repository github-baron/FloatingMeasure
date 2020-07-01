using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace FloatingMeasureWrapperTest
{
    using FloatingMeasureManaged;

    [TestClass]
    public class FloatingMeasureWrapperTest

    {
        [TestMethod]
        public void ConstructorComplexMeasure()
        {
            ComplexMeasureWrapper test = new ComplexMeasureWrapper();

            ComplexMeasureWrapper test1 = new ComplexMeasureWrapper(ePreMeasureManaged.pmMilli, eBaseMeasureManaged.bmVolt);

            Assert.AreEqual(test1.Short(), "mV");
        }

        [TestMethod]
        public void SetByID()
        {
            ComplexMeasureWrapper test = new ComplexMeasureWrapper();

            ComplexMeasureWrapper test1 = new ComplexMeasureWrapper(ePreMeasureManaged.pmMilli, eBaseMeasureManaged.bmVolt);

            test1.SetByID(ePreMeasureManaged.pmCenti, eBaseMeasureManaged.bmAmpere);

            Assert.AreEqual(test1.Short(), "cA");
        }

        [TestMethod]
        public void ConstructorFloatingMeasure()
        {
            FloatingMeasureWrapper test = new FloatingMeasureWrapper();
        }
    }

}
