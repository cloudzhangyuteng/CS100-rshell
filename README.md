# CS 100 Programming Project
- Yuteng Zhang	SID: 862017519
- Dimtri Koltsov    SID: 862068461

# Introduction: 
For this project, we are going to develop a command shell called rshell in C++ which is capable of performing certain commands like &&, || and ;, We accomplished this by using a composite design pattern consisting of connector class (which acts as the composite class) and a command class (which acts as the leaf).There can be any number of commands separated by either ||, && or ; which are the only valid connectors.The [argumentList] can also be surrounded by quotation marks. For instance, the command echo “hello && goodbye” would have the “hello && goodbye” be the [argumentList] even though without the quotes the && would separate the goodbye into its own executable. Anything that appears after a # character in the line is considered as a comment.

We added the test command to the rshell we  have developed as well as its symbolic equivalent [ ]. The square brackets [ ] are actually interpreted as the test command in bash. This command returns 0 (TRUE) if the test succeeds and 1 (FALSE) if the test fails. This command is very useful for writing conditions that can be combined with the && and || connectors to write more complex bash command structures.

**We extend our rshell program so that it properly handles input redirection <, output redirection > and >>, and piping |. We used the Unix functions dup and pipe to realize it.**

To run the program:
```
$ git clone https://github.com/cloudzhangyuteng/CS100-rshell.git
$ git submodule add https://github.com/google/googletest.git
$ cmake .
$ make
$ ./rshell
```

To run test cases:
```
$ ./test
```

Note: Most bash commands are actually executables located in PATH directories such as /bin, /usr/bin/ (e.g. ls), but some commands are built-in to bash (e.g. cd). So while the ls command "just work" in our shell when using execvp, the cd command won't and isn't required to for the assignment. Only commands that can be executed through a PATH directory need to be accounted for in this assignment.

# UML Diagram:
![UML Diagram of Assignment1](https://github.com/cloudzhangyuteng/CS100-rshell/blob/master/images/Assignment1Diagram.png?raw=true)

# Classes:
#### We decided that we are going to use 4 classes to build our shell. 
- **Base Class:**
The Base class is mainly declairing the types and functions we need for the following classes. This is an abstract class and the Command and Connector class inherits from this class. The Base class has a boolean variable execvp_flag to check if the execvp() execute the command properly, also a vector<string> command_line for the commands. We updated a string variable result for the test cases and assign it different strings in different cases in the constructors of the Connector classes.

- **Command Class:**
Inherits from the Base class. The command class read the actual command and get actions of each seperate commands. The execute() function inside the Command class, uses fork() to created 2 process. In the child process, we call the execvp() function to execute the commands read from user input, and in the parent process, we call the waitpid() function to wait for the child to finish executing the program. If the command execute correctly, we assign it's exec_flag true, otherwise assign it to false.   

- **Connector Class:**
Inherits from the Base class. The Connector class has all the connectors we need for the assignment and how should they work. This class has several sub-classes. The And, Or and Semicolon class should inherit from this class. The connector is an optional way we can run multiple commands at once. If a command is followed by ;, then the next command is always executed; if a command is followed by &&, then the next command is executed only if the first one succeeds; if a command is followed by ||, then the next command is executed only if the first one fails. The constructor takes 2 Base pointer variables, left and right. We use the exec_flag to ensure whether the left command is executed correctly. **We create 4 new sub-classes inheriting from Connector class, My_In for input redirection, My_Out and My_Out_Append for output redirection and My_Pipe for piping.**

- **Shell Class:**
The Shell class build up the whole shell and we could call the run() function inside this class to start the shell in main. It associates with the Base class and form the shell together. With this Shell class, we are able to acess and exit our own shell through the terminal shell. The parse() function inside the Shell class is where we analysis user inputs. We updated a input_preparation() function, it checks for #, quotation marks, brackets for the test command and the parenthese So now the parse() function only seperate the commands and connectors and store them in seperate vectors. The run() function detects the connectors and create proper types of them for the execution. We also add a new function create_tree() to represent the list of commands and connectors.

# Prototypes/Research:
For this assignment, we did lots of research on fork(), execvp(), and waitpid().

The fork() function creates 2 process, the parent and the child. The child process was the one that was copied. The two process runs at the same time. The reason for using the fork() function is to avoid the errors generated by your program to crash the shell of the computer. 

The execvp() function is the one that actually execute the commands. We should call this function in the child process created by the fork() function.

The waitpid() function should be called in the parent process, where it waits for the child to finish and then finish and exit the parent process. Without using this function, the program wii just stuck after the execvp() and stay there forever.

We also did some test on the normal shell to test how these commands work, this is the result we get:

```
YutengdeMacBook-Pro:~ Yuteng$ echo a && echo b
a
b
YutengdeMacBook-Pro:~ Yuteng$ echo -l || echo a
-l
YutengdeMacBook-Pro:~ Yuteng$ echo-l || echo a
-bash: echo-l: command not found
a
YutengdeMacBook-Pro:~ Yuteng$ echo a ; echo b
a
b
```

# Development and Testing Roadmap:
Here are the tasks that we think that needs to be done:
- implement/test Command class
- implement/test Connector class
- implement/test And class
- implement/test Or class
- implement/test Semicolon class
- implement/test Shell class
- general testing and debug

[link to our GitHub issues](https://github.com/cs100/assignment-cs-100-yuteng-dmitri/issues)

# Unit and Integration Testing
For the test of this project, we did both unit testing and integration testing.

Inside unit testing, we used the GoogleTest framework to check if our functions are working properly. We think the main parts that needed to be tested are checks parsing commands, check parsing with quotation marks, and parsing connectors.We updated test cases for test command and the parsing for parenthese

For the integration tests, we use bash scripts as the testing files. We created seperate files for different conditions.
- single_command_tests.sh which tests primarily for command executions
- multiple_commands_tests.sh for command and connectors interaction
- commented_command_tests.sh for comments being respected
- exit_command_tests.sh for proper exit functionality.
- test_command_tests.sh tests primarily for the test commands execution
- test_symbolic_tests.sh tests primarily for the symbolic tests commands execution
- precedence_tests.sh tests primarily for the precedence being respected
- **input_redirection_tests.sh tests primarily for the test commands execution**
- **output_redirection_tests.sh tests primarily for the symbolic tests commands execution**
- **pipe_operator_tests.sh tests primarily for the precedence being respected**



