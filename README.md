# Hello! I am planning to use this project to follow the steps of the collosal task of building a custom-made Programming Language that can compile into C code, which can then be compiled into machine code.

I am taking CS352: Compilers: Practice and Principles at Purdue University this fall and this project should give me some ideas to start with. I plan to revisit or complete this project after taking the course during the Winter Break.

<b>The project as planned will follow these steps:</b>

- Building a Numerical Parser that can convert mathematical expressions into integers.

- Building a Function Token Parser that can read function tokens and parameters to execute functions.
	- Interesting Note: This project should produce something Turing complete at this stage. Recursion is turing complete.

- Implementing Control Flow (Conditionals, Loops).

- Adding Additonal Functionality (Custom Objects/Extensibility). 
	- Building an Object Oriented Programming Language would be incredibly difficult, so an interesting place to start would be with variables that can have multiple parameters to them (Similar to JavaScript Objects).

# Completed

I have completed the Numerical Parser that handles Order of Operations. I have not implemented parentheses yet, but something like `1 + 1 * 2` will correctly output 3, not 4 like a left-to-right Numerical Parser would do.

# In Progress

Currently, I am working on creating a Function Token Parser that will take the form of `function(arg1, arg2, ...)` and can accept 0 or more arguments passed to it. I will need to create function pointers and execute those functions based off of the input to the file. This is very difficult, since there is not a direct way to convert the <b>string</b> `print(1 + 2)` into the <b> function </b> `printf("%d", 1 + 2)`.

# Technologies Used

- Flex - Lexical Analysis
- Bison - Parser and Context-Free Grammar
- C/C++ - Execution and Custom Libraries
- Makefile - Automated Commits and Compiling
- https://regex101.com/ - Testing Regexes
 
