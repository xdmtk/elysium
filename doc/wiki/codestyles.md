### General Guidelines

* 4 spaces for indentation
* camelCase for variables/functions/constants
* PascalCase for class names/unions/structs
* Braces should start on the same line as the keyword
```
// CORRECT
if (condition) {
    // do something
}

// WRONG
if (condition) 
{
    // do something 
}
```

* Prefer verbosity over abbreviations when naming variables
* No using statements. Use scope operator

```
// WRONG
using std;
cout << "Hello World!;
// CORRECT
std::cout << "Hello World!;
```

Use `/* */` for multiline comments, and be generous with comments!

More information: https://wiki.qt.io/Qt_Coding_Style
