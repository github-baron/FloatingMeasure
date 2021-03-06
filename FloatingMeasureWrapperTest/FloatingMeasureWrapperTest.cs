﻿using System;
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
        private static FloatingMeasureWrapper fmw1, fmw2, fmw3;
        [ClassInitialize]
        public static void InitFloatingMeasureWrapperTest(TestContext context)
        {
            fmw1 = new FloatingMeasureWrapper();
            fmw2 = new FloatingMeasureWrapper();
            fmw3 = new FloatingMeasureWrapper();
        }
        
        [TestMethod]
        public void Assignment()
        {
            fmw1 = new FloatingMeasureWrapper(10, fV);
            fmw2.Copy(fmw1);
            fmw1 *= 2;
            Assert.IsTrue(fmw1 == new FloatingMeasureWrapper(20, fV));
            Assert.IsTrue(fmw2 == new FloatingMeasureWrapper(10, fV));

        }
        [TestMethod]
        public void Multiplication()
        {
            fmw1 = new FloatingMeasureWrapper(10, fV);

            // multiplication by number
            fmw1 *= 2;
            Assert.IsTrue(fmw1 == new FloatingMeasureWrapper(20, fV));

            // multiplication by measure
            fmw1 *= cV;
            Assert.AreEqual(fmw1.PrintShort(), (new FloatingMeasureWrapper(20, fV*cV)).PrintShort());
            
            // multiplication by floating measure
            fmw2 = new FloatingMeasureWrapper(30, km);
            fmw1 *= fmw2;
            Assert.IsTrue(fmw1 == new FloatingMeasureWrapper(20 * 30, km * fV * cV));
            Assert.IsTrue(fmw2 == new FloatingMeasureWrapper(30, km));

            // multiplication by floating measure and value
            fmw1 *= fmw2 * 10;
            Assert.IsTrue(fmw1 == new FloatingMeasureWrapper(20 * 30 * 30 * 10, km * km * fV * cV));
            Assert.IsTrue(fmw2 == new FloatingMeasureWrapper(30, km));

            // multiplication by floating measure and complex mixture of measure and values 
            fmw1 = fmw2 * km / h *2 / 3 * fV;
            Assert.AreEqual(fmw1.PrintShort(), (new FloatingMeasureWrapper(30 *2 / 3, km * km / h * fV)).PrintShort());
            Assert.IsTrue(fmw1 == new FloatingMeasureWrapper(30 * 2 / 3, km * km / h * fV));
            Assert.IsTrue(fmw2 == new FloatingMeasureWrapper(30, km));

        }
        [TestMethod]
        public void Division()
        {

            fmw1 = new FloatingMeasureWrapper(30, km);
            fmw2 = new FloatingMeasureWrapper(20, h);
            fmw3 = fmw1 / fmw2;

            // check result
            Assert.IsTrue(fmw3 == new FloatingMeasureWrapper((Double) 30  / 20, km / h));

            // check other variables stay unchanged
            fmw3 *= 2;
            Assert.IsTrue(fmw3 == new FloatingMeasureWrapper(2*30 / 20, km / h));
            Assert.IsTrue(fmw1 == new FloatingMeasureWrapper(30 , km ));
            Assert.IsTrue(fmw2 == new FloatingMeasureWrapper(20, h));

        }
        [TestMethod]
        public void Precision()
        {
            fmw1 = new FloatingMeasureWrapper(20, fV);

            // check: precision sets AND activates precision
            fmw1.Precision(new FloatingMeasureWrapper(1, fV));
            Assert.AreEqual(fmw1.PrintShort(), "20*fV");

            // deactivate precision
            fmw1.PrecisionActive(false);
            Assert.AreNotEqual(fmw1.PrintShort(), "20*fV");

            // check other precisions
            fmw1.Precision(new FloatingMeasureWrapper(0.1, fV));
            Assert.AreEqual(fmw1.PrintShort(), "20.0*fV");
            fmw1.Precision(new FloatingMeasureWrapper(0.01, fV));
            Assert.AreEqual(fmw1.PrintShort(), "20.00*fV");

        }
        [TestMethod]
        public void Simplify()
        {
            fmw1 = new FloatingMeasureWrapper(10, fV / GV);
            fmw1.Normalize();
            Assert.IsTrue(fmw1 == new FloatingMeasureWrapper(10 * 1e-15 / 1e+9, V / V));


            fmw1.Simplify();
            Assert.IsTrue(fmw1 == new FloatingMeasureWrapper(10 * 1e-15 / 1e+9, cmIdent));


        }
        [TestMethod]
        public void Compatible()
        {
            fmw1 = new FloatingMeasureWrapper(10, fV / GA);
            fmw2 = new FloatingMeasureWrapper(0.000234, GV / mA);

            // check compatibility with floating measure arg.
            Assert.IsTrue(fmw2.Compatible(fmw1));
            Assert.IsTrue(fmw1.Compatible(fmw2));

            // check compatibility with complex measure arg.
            Assert.IsTrue(fmw2.Compatible(fV/GA));
            Assert.IsTrue(fmw1.Compatible(GV/mA));

        }
        [TestMethod]
        public void Getter()
        {
            fmw1 = new FloatingMeasureWrapper(11.11, fV / GV);

            // check raw value
            Assert.IsTrue(fmw1.RawValue() == 11.11);
            Assert.IsTrue(fmw1.Measure() == (fV / GV));

            // check rounded value
            fmw1.Precision(new FloatingMeasureWrapper(10, fV / GV));
            Assert.IsTrue(fmw1.Value() == 10);
            fmw1.Precision(new FloatingMeasureWrapper(1, fV / GV));
            Assert.IsTrue(fmw1.Value() == 11);
            fmw1.Precision(new FloatingMeasureWrapper(5, fV / GV));
            Assert.IsTrue(fmw1.Value() == 11);
            fmw1.Precision(new FloatingMeasureWrapper(0.1, fV / GV));
            Assert.IsTrue(fmw1.Value() == 11.1);
            fmw1.Precision(new FloatingMeasureWrapper(0.5, fV / GV));
            Assert.IsTrue(fmw1.Value() == 11.1);
            fmw1.Precision(new FloatingMeasureWrapper(0.01, fV / GV));
            Assert.IsTrue(fmw1.Value() == 11.11);
            fmw1.Precision(new FloatingMeasureWrapper(0.05, fV / GV));
            Assert.IsTrue(fmw1.Value() == 11.11);

        }

        [TestMethod]
        public void Comparison()
        {
            // equality
            fmw1 = new FloatingMeasureWrapper(10, fV / GV);
            fmw2 = new FloatingMeasureWrapper(10, fV / GV);
            Assert.IsTrue(fmw1 == fmw2);
            Assert.IsTrue(fmw1 >= fmw2);
            Assert.IsTrue(fmw1 <= fmw2);
            Assert.IsFalse(fmw1 != fmw2);
            Assert.IsFalse(fmw1 > fmw2);
            Assert.IsFalse(fmw1 < fmw2);

            // equality with different units
            fmw1 = new FloatingMeasureWrapper(0.01, pV / GV);
            Assert.IsTrue(fmw1 == fmw2);
            Assert.IsTrue(fmw1 >= fmw2);
            Assert.IsTrue(fmw1 <= fmw2);
            Assert.IsFalse(fmw1 != fmw2);
            Assert.IsFalse(fmw1 > fmw2);
            Assert.IsFalse(fmw1 < fmw2);

            // if comparing partners are incompatible --> all false, except !=
            fmw2 = new FloatingMeasureWrapper(10, fV / GA);
            Assert.IsTrue(fmw1 != fmw2);
            Assert.IsFalse(fmw1 == fmw2);
            Assert.IsFalse(fmw1 >= fmw2);
            Assert.IsFalse(fmw1 <= fmw2);
            Assert.IsFalse(fmw1 > fmw2);
            Assert.IsFalse(fmw1 < fmw2);

            // unequal by value
            fmw2 = new FloatingMeasureWrapper(9.95, fV / GV);
            Assert.IsTrue(fmw1 != fmw2);
            Assert.IsFalse(fmw1 == fmw2);
            Assert.IsTrue(fmw1 >= fmw2);
            Assert.IsFalse(fmw1 <= fmw2);
            Assert.IsTrue(fmw1 > fmw2);
            Assert.IsFalse(fmw1 < fmw2);

            // setting precision --> equality:
            // set precision for right partner --> ruling precision
            fmw1.Precision(new FloatingMeasureWrapper(0.1, fV / GV));
            Assert.IsFalse(fmw1 != fmw2);
            Assert.IsTrue(fmw1 == fmw2);
            Assert.IsTrue(fmw1 >= fmw2);
            Assert.IsTrue(fmw1 <= fmw2);
            Assert.IsFalse(fmw1 > fmw2);
            Assert.IsFalse(fmw1 < fmw2);


        }
    }
}
