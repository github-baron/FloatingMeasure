## Synopsis

FloatingMeasure is a class API for calculations of floating point numbers with measures. 

The measures can be any complex combination of the given <a href="./FloatingMeasure/Measure/SimpleMeasure.h"> SimpleMeasures </a> and the mathematical operation "multiplication" and "division".

The <a href="./FloatingMeasure/Measure/SimpleMeasure.h"> SimpleMeasures </a> consists of a <a href="./FloatingMeasure/Measure/PreMeasure.h"> PreMeasure </a> and a <a href="./FloatingMeasure/Measure/BaseMeasure.h"> BaseMeasure </a>. Thus, this API is easily extendable by any kind of pre measure or base measure.

The "floating" part of this API considers errors due to the numerical floating point representation. As a consequence i.e. the <a href="FloatingMeasure/FloatingMeasure.cpp"> comparison operator </a> allows equality for a range of values given by the numerical error.  

Even the history (i.e. the different mathematical operations) of these errors is protocolled.


## Code Example

Show what the library does as concisely as possible, developers should be able to figure out **how** your project solves their problem by looking at the code example. Make sure the API you are showing off is obvious, and that your code is short and concise.

Simple example is the calculation of a velocity "v" from a distance of "s=100*m" and the the time "t=9.27*s". This API offers the calculation of "v" by writing code like "v=s/t".
<a href="./FloatingMeasure_Examples/FMEx_Velocity.cpp"> FMEx_Velocity.cpp</a>

## Motivation

A short description of the motivation behind the creation and maintenance of the project. This should explain **why** the project exists.

## Installation

Provide code examples and explanations of how to get the project.

## API Reference

Depending on the size of the project, if it is small and simple enough the reference docs can be added to the README. For medium size to larger projects it is important to at least provide a link to where the API reference docs live.

## Tests

Describe and show how to run the tests with code examples.

## Contributors

Let people know how they can dive into the project, include important links to things like issue trackers, irc, twitter accounts if applicable.

## License

A short snippet describing the license (MIT, Apache, etc.)

