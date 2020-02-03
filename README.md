## Synopsis

FloatingMeasure is a class API for calculations of floating point numbers with measures. 

The measures can be any complex combination of <a href="./FloatingMeasure/Measure/SimpleMeasure.h"> simple measures </a> and the mathematical operation "multiplication" and "division".

A <a href="./FloatingMeasure/Measure/SimpleMeasure.h"> simple measure </a> consists of a <a href="./FloatingMeasure/Measure/PreMeasure.h"> pre measure </a> and a <a href="./FloatingMeasure/Measure/BaseMeasure.h"> base measure </a>. Thus, this API is easily extendable by any kind of pre measure or base measure.

The "floating" part of this API considers errors due to the numerical floating point representation. As a consequence e.g. the <a href="FloatingMeasure/FloatingMeasure.cpp"> comparison operator </a> allows equality for a range of values given by the numerical error instead of comparing to exact one value (which often fails .... unwanted).  

Even the history (i.e. the sequence of mathematical operations) of these errors is protocolled.


## Code Example

<a href="./FloatingMeasure_Examples/FMEx_Velocity.cpp"> FMEx_Velocity.cpp</a> :</br>
An example for calculation of a velocity "v" of Usain Bolt, a snail, and the corresponding "snail factor".

<a href="./FloatingMeasure_Examples/FMEx_CheckMeasValue.cpp"> FMEx_CheckMeasValue.cpp</a> :</br>
An example for checking a measurement value against a given tolerance: with and without considering a given precision.


## Motivation

The FloatingMeasure API can be used in any metrological project. It helps avoiding those classical errors like "off by a factor of thousand" or any other potency of ten: the Recalculation from one measure to another is made easy.

Additionally, it supports configurable precision which is oftenly needed for "reasonable precise" numbers of a given metrological setup: see <a href="./FloatingMeasure_Examples/FMEx_CheckMeasValue.cpp"> FMEx_CheckMeasValue.cpp</a> for illustration.

## Installation

The project can be compiled under Linux (CMake) and Windows (Visual Studio 2017). The corresponding build result can be found in the project directory <a href="build/CMake"> build/CMake </a> (for CMake) and <a href="build/VS"> build/VS </a> (for Visual Studio).  Distribute the corresponding "include" and "lib" directories to your favorite installation directory.

## API Reference

Refere to the doxygen generated documentation <a href="Doc/html/index.html"> here. </a>

## Tests

Testing is done via cppunit which can be found on <a href="https://github.com/Ultimaker/CppUnit"> github </a> for usage under Windows (install and distribute with CMake). Under Linux (at least for Debian) it can be installed via apt.

For building with CMake the <a href="FloatingMeasure_Test/CMakeLists.txt"> CMakeLists.txt </a> file must be adapted for that. There must be a more elegant way ...

See how the testing is implemented <a href="FloatingMeasure_Test/FloatingMeasure_Test.cpp"> FloatingMeasure_Test.cpp </a>.

## Contributors

Contributers are very welcome. Please, share your ideas of how want to use this API and adpat it to your needs.

## Future Development

- idea of "aliases" like : "1\*V\*A = 1\*W" or "1\*kg\*m\*m/s/s = 1\*J"... just an idea
- any extension of pre and base measures (see above example: "kg" is missing)
- handling offsets (i.e. especially temperatures are not supported at the moment)
    - recalculation to SI-measures 
    - simplification of complex measures


## License

See my <a href="LICENSE"> LICENSE </a> (MIT).

