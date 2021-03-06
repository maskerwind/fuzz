Readme for the Sorted INTerface - 2018-11-15

# The challenge

Sinterklaas is almost here again! He asked Computer Piet to make a program to keep track of Piets that
arrived on the boat to make the journey here. Computer Piet made a set using a sorted binary tree and
called it the SINT, the Sorted INTerface.

But alas, Computer Piet made some mistakes and it is up to you to fix the problems!

# More formally

Included is a makefile. To use it to compile this code, run make.

The challenge is to make the code more robust and memory-leak free. More robust means the user cannot
tamper with the security of the application using a specific command. For example, the command "i 1"
might be hazardous, because no name is specified. Try to find such hazardous inputs to break the
application. If an input is not correct or incomplete, print ONLY the message "Invalid input\n" and
DO NOT handle the command any further.

The commands the program accepts are:

```
i <age:int> <name:string>
    For valid data, inserts an element into the tree with the specified data.
e <age:int> <name:string>
    For valid data, erases the element from the tree that has data equal to the specified data.
c <age:int> <name:string>
    For valid data, prints "y\n" iff an equal element to the specified data is in the
    container already, "n\n" otherwise.
p
    Prints the elements in the tree
x
    Exits the program
t
    Perform the tests in test.c
```

There are functions that you need to fill in completely and there are sections of existing code that
need to be improved. Use valgrind and cppcheck to make the program great again.

Use test.c to your advantage! Make sure all tests pass and add extra tests.

Add proper tests to make your life easier. Starting the program with valgrind and then firing
the tests with the 't' command is a good starting point to find bugs in your implementation.

Have a look at the manual of valgrind and look for good options to pass. For example '--track-origins=yes'
and '--leak-check=full' options are good. There might be more. Use valgrind to make sure your program
does not have any bugs like a conditional jump based on an uninitialized value.

In the directory "tests" are expect scripts that provide input and then listen for (expect) specific
output. You can run these tests using ./runtests in the assignment directory. Have a look at the
scripts to see how they work. Instead of manually testing your program with various input/erase
commands every time you make a small change, you can add expect scripts in this directory to test your
program.

# Requirements

* The container is implemented correctly
* The tests test4 and test5 are implemented
* The bugs in the rest of the program are tracked down and fixed
* Invalid input is handled properly and without error. Make sure to consider edge cases!
* Use valgrind to make sure there are no memory leaks or other memory bugs
* OPTIONAL: write expect scripts to test your code. While writing no tests has no negative impact on the grading, adding tests not only helps you, but could very well have a positive impact.

# What to submit

You do not need to submit anything, just commit your changes to this repository to the master branch. Do not change the project structure such as moving your files around or renaming them.
