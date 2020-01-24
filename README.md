# Elysium - Chat Application

### Code Styles
* Use 4 spaces for indentation
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
* No `using` statements. Use scope operator 
```
// WRONG
using std;
cout << "Hello World!;
```
```
// CORRECT
std::cout << "Hello World!;
```
* Use /* */ for multiline comments, and be generous with comments!


More information: https://wiki.qt.io/Qt_Coding_Style
 

### General Guidelines
* Before using anything from the standard library for the client application, check to see whether Qt has an implementation. For example, avoid using `std::string` and work with the Qt class `QString` instead. 
* For the server application, because of the deployment constraints (limited EC2 server memory), no Qt code will be involved. 
* Try to avoid using platform specific code, even if they are wrapped in `#define` directives for that specific platform. 9 times out of 10 Qt will have an implementation that can accomplish what you may be trying to do.
* Use header guards! For every header file you write, make sure you wrap it in a header guard to prevent circular dependencies during compile time. More information: https://www.learncpp.com/cpp-tutorial/header-guards/
* Avoid including header files in other header files, if at all possible, use a forward declaration of the class you are referencing in the header.

### Building
* It's still up in the air whether we want to make the client application multi-platform(some of us use Mac, Windows, Linux, etc..), however the server application is going to be deployed on Ubuntu 18.04. So if you want to write server code, you should have a (virtual) machine running Ubuntu 18.04 to test locally on.


### Git Workflow
* In order to effectively collaborate, we will be utilizing 'feature' branches and 'pull-requests'
* The idea is that, our GitLab board will have numbered 'issues' with tasks outlined in them.
* Members of the group will be assigned to work on those tickets
* To work on a feature in isolation, you will need to branch off the master branch, and name your branch `feat/#{issue_number}-some-description-of-the-issue`
* Commit and push all work for that feature to that branch
* When you are ready to have the code reviewed and merged back into the master branch, you will open a pull request and tag the team as code reviewers

More information: https://www.atlassian.com/git/tutorials/comparing-workflows/feature-branch-workflow
