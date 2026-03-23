# **MINISHELL**

## **DEMO**

![Minishell Demo](assets/demo.gif)

## **ABOUT**

MINISHELL is a minimal UNIX SHELL written in C as part of the 42 curriculum.
The goal of this project is to understand PROCESS CREATION, FILE DESCRIPTORS, and SIGNAL HANDLING.

This project recreates core behavior of BASH with strict FUNCTION LIMITATIONS and MEMORY MANAGEMENT constraints.
The implementation follows the official SUBJECT and respects THE NORM coding standard.

## **REFERENCES**

The project follows the official SUBJECT and respects THE NORM coding standard.

SUBJECT: [subject.pdf](./subject.pdf)
NORMINETTE: [norm.pdf](./norm.pdf)

## **FEATURES**

MINISHELL provides a functional interactive SHELL environment.
It supports COMMAND EXECUTION, BUILTINS, PIPES, and REDIRECTIONS.

It handles ENVIRONMENT VARIABLES, EXIT STATUS, and SIGNALS like CTRL-C and CTRL-D.

## **INSTALLATION & USAGE**

Clone the repository and build the project using MAKE.

```
git clone <your-repo-link>
cd MINISHELL/MINISHELL
make
```

Run the program using:

```
./minishell
```

## **PROJECT REQUIREMENTS**
The only requirements are:

    GNU MAKE (>= 4.3)
    GCC (>= 11.4.0)
    UNIX-BASED SYSTEM (LINUX OR MACOS)

Those versions are the ones used during development.
## **ALLOWED FUNCTIONS AND LIMITATIONS**

The project restricts you to specific SYSTEM CALLS and LIBRARY FUNCTIONS.
This limitation forces understanding of OS-level behavior like FORK, EXECVE, and PIPE.

Examples of allowed functions include:

```
fork();
execve(path, args, env);
pipe(fd);
dup2(oldfd, newfd);
```

You cannot use high-level abstractions.
Everything must be built using LOW-LEVEL UNIX MECHANISMS as required by the SUBJECT.


## **SIGNAL HANDLING**

The shell handles SIGNALS similar to BASH behavior.
It uses SIGNAL and SIGACTION for proper control.

CTRL-C prints a new PROMPT.
CTRL-D exits the shell.
CTRL-\ does nothing.

Example:

```
signal(SIGINT, handler);
```

Only ONE GLOBAL VARIABLE is used to store SIGNAL STATE as required by the SUBJECT.

## **GARBAGE COLLECTOR**

The project includes a custom MEMORY MANAGEMENT system to avoid MEMORY LEAKS.
It is based on a LINKED LIST that tracks all allocated memory.

FT_MALLOC stores allocated addresses in the list.
FT_FREE removes them and frees memory safely.

Example:

```
void *ptr = ft_malloc(sizeof(int));
ft_free(ptr);
```

This system ensures safe cleanup and helps handle MALLOC FAILURE cases.


## **NOTES**

The project must not have MEMORY LEAKS.
READLINE leaks are acceptable, but your own code must be CLEAN.

All behavior should follow the SUBJECT and use BASH as the REFERENCE IMPLEMENTATION when needed.
