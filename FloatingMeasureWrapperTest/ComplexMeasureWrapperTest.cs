
using Microsoft.VisualStudio.TestTools.UnitTesting;
using ComplexMeasureCLI;
using static SimpleMeasureCLI.ePreMeasureManaged;
using static SimpleMeasureCLI.eBaseMeasureManaged;
using static ComplexMeasureWrapperMacros.ComplexMeasureWrapperMacros;

namespace FloatingMeasureWrapperTest
{



    [TestClass]
    public class ComplexMeasureWrapperTest
    {

        private static ComplexMeasureWrapper cmwMeas1, cmwMeas2, cmwMeas3;
        [ClassInitialize]
        public static void InitFloatingMeasureWrapperTest(TestContext context)
        {
            cmwMeas1 = new ComplexMeasureWrapper();
            cmwMeas2 = new ComplexMeasureWrapper();
            cmwMeas3 = new ComplexMeasureWrapper();
        }
        
        [TestMethod]
        public void A_DefaultConstructorComplexMeasure()
        {

            cmwMeas1 = new ComplexMeasureWrapper();
            cmwMeas2 = new ComplexMeasureWrapper();
            cmwMeas3 = new ComplexMeasureWrapper();

            Assert.IsFalse(cmwMeas1.Valid());
            Assert.IsFalse(cmwMeas2.Valid());
            Assert.IsFalse(cmwMeas3.Valid());
        }

        [TestMethod]
        public void B_ConstructorByIDComplexMeasure()
        {
            cmwMeas2 = new ComplexMeasureWrapper(pmMilli, bmVolt);

            Assert.AreEqual(cmwMeas2.Short(), "mV");
        }

        [TestMethod]
        public void B1_CheckComplexMeasureDefines()
        {
            Assert.AreEqual( fV.Short(), "fV");
        }

        [TestMethod]
        public void C_SetByIDComplexMeasure()
        {
            cmwMeas3 = new ComplexMeasureWrapper(pmMilli, bmVolt);

            cmwMeas3.SetByID(pmCenti, bmAmpere);

            Assert.AreEqual(cmwMeas3.Short(), "cA");
        }
        
        [TestMethod]
        public void D_ConstructorComplexMeasure_Copy()
        {
            cmwMeas3 = new ComplexMeasureWrapper(pmMilli, bmVolt);
            cmwMeas3.SetByID(pmCenti, bmAmpere);
            cmwMeas1 = new ComplexMeasureWrapper(cmwMeas3);

            // set cmwMeas2 to another complex measure to check if cmwMeas1 is independent ... it is not
            cmwMeas3.SetByID(pmKilo, bmAmpere);

            Assert.AreEqual(cmwMeas1.Short(), "cA");
            Assert.AreEqual(cmwMeas3.Short(), "kA");
        }

        [TestInitialize]
        public void TestInit()
        {
            cmwMeas3 = cA;
            cmwMeas1 = kA;
            cmwMeas2 = cmIdent;
        }
        [TestMethod]
        public void E_OperationsComplexMeasure_Multiply()
        {
            cmwMeas2 = cmwMeas1 * cmwMeas3;
            Assert.IsTrue(cmwMeas2 == kA*cA);
            Assert.IsTrue(cmwMeas1 == kA);
            Assert.IsTrue(cmwMeas3 == cA);

        }
        
        [TestMethod]
        public void G_OperationsComplexMeasure_Division()
        {
            cmwMeas1 /=cmwMeas3;
            Assert.IsTrue(cmwMeas1 == kA / cA);
            Assert.IsTrue(cmwMeas3 == cA);

        }
 
    }

}
