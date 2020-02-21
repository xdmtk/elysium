### General Guidelines

##### Qt vs `std`

* Before using anything from the standard library for the client application, check to see whether Qt has an implementation. For example, avoid using std::string and work with the Qt class `QString` instead.
For the server application, because of the deployment constraints (limited EC2 server memory), no Qt code will be involved.

* More information: https://www.learncpp.com/cpp-tutorial/header-guards/

##### Header Files

* Use header guards! For every header file you write, make sure you wrap it in a header guard to prevent circular dependencies during compile time.

* Avoid including header files in other header files, if at all possible, use a forward declaration of the class you are referencing in the header.


##### Multi-platform Code
* Try to avoid using platform specific code, even if they are wrapped in `#define` directives for that specific platform. 9 times out of 10 Qt will have an implementation that can accomplish what you may be trying to do.
 
