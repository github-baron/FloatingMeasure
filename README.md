# FloatingMeasure – C++ Library for Physical Quantities and Units

## Synopsis

FloatingMeasure is a **C++ library for unit-aware numerical calculations with physical quantities**,
designed for use in **measurement, calibration, and engineering software**.

It provides a class-based API for working with floating point values that explicitly carry
**physical units and numerical uncertainties**, helping to prevent unit-related and semantic
calculation errors in technical software systems.

Instead of operating on plain floating point numbers, physical values are represented explicitly
together with their associated measures.
For example, a velocity can be expressed in code as:

```c++
CFloatingMeasure velocity = 150 * km / h;
```

Measures can be defined as arbitrary combinations of
[simple measures](./FloatingMeasure/Measure/SimpleMeasure.h)
using the mathematical operations **multiplication** and **division**.

In the example above:

```c++
CComplexMeasure velocity_measure = km / h;   // consisting of
CSimpleMeasure  distance_measure = km;       // combined with
CSimpleMeasure  time_measure     = h;        // by the "/" operator
```

A [simple measure](./FloatingMeasure/Measure/SimpleMeasure.h) consists of a
[pre-measure](./FloatingMeasure/Measure/PreMeasure.h) and a
[base measure](./FloatingMeasure/Measure/BaseMeasure.h).

This design allows the API to be easily extended with additional pre-measures or base measures.
In the example above, the distance measure consists of the pre-measure **"k"** (kilo)
and the base measure **"m"** (meter).

---

## What FloatingMeasure Is

* A C++ library for handling **physical quantities and units**
* Designed for **unit-aware numerical calculations**
* Focused on correctness, clarity, and robustness
* Intended for long-lived **measurement and engineering software**

## What FloatingMeasure Is Not

* Not a template-heavy compile-time unit system
* Not a general-purpose mathematics library
* Not optimized for performance-critical HPC workloads

---

## Numerical Precision and Error Propagation

The *floating* aspect of the API explicitly considers numerical errors caused by floating point
representation.

As a consequence, comparison operators (see
[comparison operator implementation](FloatingMeasure/FloatingMeasure.cpp))
allow equality within a tolerance range defined by the accumulated numerical error,
instead of requiring exact equality, which is often undesirable in numerical software.

FloatingMeasure also tracks the **history of numerical operations**.
Numerical uncertainties propagate depending on the mathematical operations performed and on the
error history of the operands involved.

---

## Code Examples

[FMEx_Velocity.cpp](./FloatingMeasure_Examples/FMEx_Velocity.cpp)
Example demonstrating the calculation of velocities for Usain Bolt, a snail,
and the resulting *snail factor*.

[FMEx_CheckMeasValue.cpp](./FloatingMeasure_Examples/FMEx_CheckMeasValue.cpp)
Example showing how to check a measurement value against a given tolerance,
both with and without explicitly considering a defined numerical precision.

---

## Typical Use Cases

FloatingMeasure is suitable for:

* Measurement and test software
* Calibration systems
* Engineering tools with physical units
* Scientific and numerical software
* Unit conversion and validation tasks

---

## Motivation

In metrological and engineering software, unit-related errors are a common and often
hard-to-detect problem. Mixing incompatible units or relying on implicit conversions
can easily lead to incorrect results.

FloatingMeasure addresses this by making physical quantities explicit and by handling
unit conversions in a controlled and transparent way.

Additionally, the API supports **user-defined precision**, which is often required to
represent *reasonably precise* values in real-world measurement setups.
See [FMEx_CheckMeasValue.cpp](./FloatingMeasure_Examples/FMEx_CheckMeasValue.cpp)
for an illustration.

---

## Installation

The project can be compiled on:

* **Linux** using CMake
* **Windows** using Visual Studio 2017

Build results are located in:

* [build/CMake](build/CMake) (CMake)
* [build/VS](build/VS) (Visual Studio)

Distribute the generated `include` and `lib` directories to your preferred installation location.

---

## API Reference

Refer to the Doxygen-generated API documentation
[here](Doc/html/index.html).

---

## Tests

Testing is performed using **CppUnit**, available on
[GitHub](https://github.com/Ultimaker/CppUnit).

On Linux (e.g. Debian-based systems), CppUnit can be installed via `apt`.

For CMake builds, the file
[CMakeLists.txt](FloatingMeasure_Test/CMakeLists.txt)
must be adapted accordingly.

See
[FloatingMeasure_Test.cpp](FloatingMeasure_Test/FloatingMeasure_Test.cpp)
for details on the test implementation.

---

## Contributors

Contributions are welcome.
Feel free to share ideas on how you intend to use the API or how it could be adapted
to additional use cases.

---

## Future Development

* Support for *aliases*, e.g.
  `1 * V * A = 1 * W` or
  `1 * kg * m * m / s / s = 1 * J`
* Extension of available pre-measures and base measures (e.g. missing `kg`)
* Handling of offsets (notably temperature units), including:

  * conversion to SI units
  * simplification of complex measures

---

## License

See the [LICENSE](LICENSE) file (MIT).


