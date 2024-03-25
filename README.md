**MINISHELL 🐢**

Minishell is a project in Hive Helsinki's curriculum: the goal is to create a simple shell based on bash.
This is a two-person project, which I've completed with [FinnShields](https://github.com/FinnShields)

***How to install***

1. Clone this repository

2. Install the readline library

3. Go to the repository, and open the Makefile. Change (if needed) the RL_PATH variable to point to the directory where the readline library was installed.

4. Run the command "make"

Now, you are able to launch the program with the command

  ./minishell

***About minishell 🐢***

Minishell is based on bash, but is smaller in scope. Its features include:

I. Handling special characters

- $ is used to signify an environmental variable. They are implemented the same way that they are in bash: expanded, when such an environmental variable exists, and ignored if it does not.
- '|' (pipe) character can be used to pipe commands after each other, where the input of the command after the pipe will be the input of the command preceeding the pipe. The 'or' ('||') operator is not implemented, and is treated as a syntax error
- Single quotes (') prevent all special characters from being interpreted
- Double quotes (") prevent special characters from being interpreted, except '$'
- '<' and '>' are used for in- and output redirection, see below
- The combination '$?' will cause the exit status of the last process to be printed

II. Launch executables

Executables can be launched using:

- relative path
- absolute path
- without path, if the executable's location is found within the PATH environmental variable

III. In- and output redirection

- '<' token followed by file name will set that file to be the standard input of the command
- '<<' token followed by a limiter name will give a prompt for the user to type the command's standard input into the terminal. The limiter is a string that is meant to signal the end of the input (not included in the input). Environment variables are expanded the same way that they are in bash's heredocs.
- '>' token followed by file name will redirect the output to that file. If the file already exists, its previous contents are truncated. Otherwise, the file is newly created.
- '>>' token followed by file name will redirect the output to that file. If the file already exists, the new information is appended to it. Otherwise, the file is newly created.

In bash, these tokens can be preceeded by numeric characters to specify which fd to use, but this is NOT implemented in minishell.

IV. Pipes

Pipes work the same way that they do in shell, except a pipe symbol must always be followed by a command. Otherwise, it is considered a syntax error. (Using the '&|' combination to also redirect the errors is NOT possible.)

V. Built-ins

A number of bash-builtins have been re-implemented from scratch. These are:

- echo with the option -n (which supresses newlines)
- cd with relative or absolute path
- pwd with no options
- export with no options
- unset with no options
- env with no options or arguments
- exit with no options

VI. Signals

- Ctrl + \ is suppressed, and will not exit minishell
- Ctrl + D exits minishell
- Ctrl + C displays a new prompt on a new line
